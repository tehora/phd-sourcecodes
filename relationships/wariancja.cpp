#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
#include <set>
#include <unordered_map>

using namespace std;

#include "czytgraf.cpp"

vector<int> indeg[2], outdeg[2];

int scanerr;

#define MEMBER 0
#define FOLLOWER 1

const char *nameof(int t) { return t?"FOLLOWER":"MEMBER"; }

struct edgedata {
  int ingraph[2];
  int revgraph[2];
  edgedata() { ingraph[0] = ingraph[1] = revgraph[0] = revgraph[1] = 0; }
  };

// wersja 1

long long vpair(int x, int y) { return (((long long)x)<<32) | y; }
unordered_map<long long, edgedata> edata;

// wersja 2

/* 
auto vpair(int i, int j) { return make_pair(i,j); }

map<pair<int, int>, edgedata> edata;
*/

//

long long qty[16];

bool STARE = false;

int main(int argc, char ** argv) {

  printf("czytgraf0...\n");
  czytgraf(argv[1], 0);
  printf("czytgraf1...\n");
  czytgraf(argv[2], 1);
  printf("renumer...\n");
  renumer();
  
  // for(int i=0; i<M; i++) if(edges[i].t == FOLLOWER) swap(edges[i].a, edges[i].b);
  
  printf("invalid\n");
  
  array<int, 2> narcyzy = {0, 0};
  array<int, 2> repeated = {0, 0};
  
  for(int i=0; i<M; i++) {
    edges[i].invalid = edges[i].a == edges[i].b;
    if(edges[i].invalid) narcyzy[edges[i].t]++;
    if(edges[i].a >= N || edges[i].b >= N || edges[i].a < 0 || edges[i].b < 0) {
      printf("invalid %d-%d t=%d\n", edges[i].a, edges[i].b, edges[i].t);
      edges[i].invalid = true;
      }
    if(edges[i].invalid) 
      continue;
    {
    edgedata& ed(edata[vpair(edges[i].a, edges[i].b)]);
    if(ed.ingraph[edges[i].t]) {
      edges[i].invalid = true;
      repeated[edges[i].t]++;
      }
    else ed.ingraph[edges[i].t]++;
    }
    if(edges[i].invalid) continue;
    {
    edgedata& ed(edata[vpair(edges[i].b, edges[i].a)]);
    ed.revgraph[edges[i].t]++;
    }
    }
  
  for(int t=0; t<2; t++) printf("narcyzy = %d repeated = %d\n", narcyzy[t], repeated[t]);
 
  printf("in/outdeg\n");

  for(int t=0; t<2; t++) {
    indeg[t].resize(N);
    outdeg[t].resize(N);
    for(int i=0; i<N; i++) indeg[t][i] = outdeg[t][i] = 0;
    }
  
  for(int i=0; i<M; i++) 
    if(!edges[i].invalid)
      outdeg[edges[i].t][edges[i].a]++, indeg[edges[i].t][edges[i].b]++;

  printf("stat\n");
 
  long long stat[2][5];
  
  for(int t=0; t<2; t++) for(int l=0; l<5; l++) stat[t][l] = 0;

  for(int i=0; i<M; i++) {
    edge& ed(edges[i]);
    if(ed.invalid) continue;
    int t = ed.t;
    stat[t][0]++;
    }
    
  for(int i=0; i<M; i++) {
    edge& ed(edges[i]);
    if(ed.invalid) continue;
    int t = ed.t;
    bool rev = edata[vpair(ed.a, ed.b)].revgraph[t] == 1;
    if(rev) stat[t][1]++;
    stat[t][2] += outdeg[t][ed.b] - (rev?1:0);
    stat[t][3] += indeg[t][ed.a] - (rev?1:0);
    stat[t][4] += stat[t][0] - (rev?2:1) - outdeg[t][ed.b] - indeg[t][ed.a];
    }
  
  const char *nazwy[5] = {
    "krawedzie poprawne",
    "krawedzie poprawne mutual",
    "dziwne dziadostwo sumujace stopnie wyjsciowe",
    "dziwne dziadostwo sumujace stopnie wejsciowe",
    "dziwne dziadostwo sumujace co sie da"
    };

  for(int t=0; t<2; t++) for(int l=0; l<5; l++)
    printf("%d,%d: %Ld (%s)\n", t,l, stat[t][l], nazwy[l]);
  
  vector<int> notnarc;
  for(int i=0; i<N; i++) 
    if(indeg[0][i] || outdeg[0][i] || indeg[1][i] || outdeg[1][i]) 
      notnarc.push_back(i);
  int NN = notnarc.size();
  
  long double N1 = 1.0 / NN;
  long double N2 = N1 / (NN-1);
  long double N3 = N2 / (NN-2);
  long double N4 = N3 / (NN-3);
  
  printf("NN = %d\n", NN);
  
  double valat = 0;
  for(auto it: edata) if(it.second.ingraph[0] && it.second.ingraph[1]) valat++;
  
  printf("common edges = %d\n", (int) valat);
  
  long double expected = stat[0][0] * (stat[1][0] * N2);
  
  long double expected2 = 
    stat[0][0] * (stat[1][0] * N2) +
    stat[0][1] * (stat[1][1] * N2) +
    stat[0][2] * (stat[1][2] * N3) +
    stat[0][3] * (stat[1][3] * N3) +
    stat[0][4] * (stat[1][4] * N4);
  
  long double variance = expected2 - expected * expected;
  
  printf("N1 = %Lg\n", N1);
  printf("N2 = %Lg\n", N2);
  printf("N3 = %Lg\n", N3);
  printf("N4 = %Lg\n", N4);
  
  printf("expected = %Lf\n", expected);
  printf("expected2 = %Lf\n", expected2);
  printf("variance = %Lf\n", variance);
  
  printf("Markov = %Lf\n", expected / valat);
  printf("Czebyszew = %.20Lf\n", variance / (valat - expected) / (valat - expected));
  
  long long NN2 = NN * (long long) NN;

  qty[0] = NN2 - NN;
  
  for(auto it: edata) {
    qty[0]--;
    int cod = 0;
    if(it.second.ingraph[0]) cod += 1;
    if(it.second.revgraph[0]) cod += 2;
    if(it.second.ingraph[1]) cod += 4;
    if(it.second.revgraph[1]) cod += 8;
    qty[cod]++;
    }
  
  const char* names[4] = {"G0", "G0'", "G1", "G1'"};

  for(int u=0; u<16; u++) for(int v=0; v<16; v++) if((u|v) == u) {
    long long total = 0;
    for(int k=0; k<16; k++)
      if((k&v) == v && (k|u) == u)
        total += qty[k];
    printf("%20Ld ", total);

    for(int c=0; c<4; c++) {
      if(((u^v)>>c) & 1) printf("?");
      else if((u>>c) & 1) printf("1");
      else printf("0");
      }

    for(int c=0; c<4; c++) {
      printf(" %s", names[c]);
      if(((u^v)>>c) & 1) printf("?");
      else if((u>>c) & 1) printf("=1");
      else printf("=0");
      }
    printf("\n");
    }
  
  fflush(stdout);
  
  return 0;
  }
