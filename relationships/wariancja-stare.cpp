#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

int N, M;

vector<int> ids;

struct edge {int a, b, t; bool invalid; 
  edge(int _a, int _b, int _t) { a = _a; b = _b; t = _t; invalid = false; }
  edge() { invalid = false; }
  };

vector<edge> edges;

map<pair<int, int>, int> dane;

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

map<pair<int, int>, edgedata> edata;

long long qty[16];

bool STARE = false;

int main(int argc, char ** argv) {

  if(argc >= 2 && strcmp(argv[1], "-s") == 0) STARE = true;

  if(STARE) {
    scanerr=scanf("%d%d", &N, &M);
    ids.resize(N);
    for(int i=0; i<N; i++) scanerr=scanf("%d", &ids[i]);
    edges.resize(M);
    for(int i=0; i<M; i++) scanerr=scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].t);
    }
  
  else {
    N = 15000000;
    while(!feof(stdin)) {
      char xbuf[5000];
      int a, b;
      scanf("%d%d%s", &a, &b, xbuf);
      if(strchr(xbuf ,'f')) // follower -> followed
        edges.emplace_back(a, b, FOLLOWER);
      if(strchr(xbuf ,'F')) // followed -> follower
        edges.emplace_back(b, a, FOLLOWER);
      if(strchr(xbuf ,'m')) // owner -> member
        edges.emplace_back(b, a, MEMBER);
      if(strchr(xbuf ,'M')) // member -> owner
        edges.emplace_back(a, b, MEMBER);
      }
    M = edges.size();
    printf("M = %d\n", M);
    }
  
  // for(int i=0; i<M; i++) if(edges[i].t == FOLLOWER) swap(edges[i].a, edges[i].b);
  
  printf("invalid\n");
  
  for(int i=0; i<M; i++) {
    edges[i].invalid = edges[i].a == edges[i].b;
    if(edges[i].a >= N || edges[i].b >= N || edges[i].a < 0 || edges[i].b < 0) {
      printf("invalid %d-%d\n", edges[i].a, edges[i].b);
      edges[i].invalid = true;
      }
    if(edges[i].invalid) 
      continue;
    {
    edgedata& ed(edata[make_pair(edges[i].a, edges[i].b)]);
    if(ed.ingraph[edges[i].t]) edges[i].invalid = true;
    else ed.ingraph[edges[i].t]++;
    }
    if(edges[i].invalid) continue;
    {
    edgedata& ed(edata[make_pair(edges[i].b, edges[i].a)]);
    ed.revgraph[edges[i].t]++;
    }
    }
 
  printf("in/outdeg\n");

  for(int t=0; t<2; t++) {
    dane.clear();
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
    bool rev = edata[make_pair(ed.a, ed.b)].revgraph[t] == 1;
    if(rev) stat[t][1]++;
    stat[t][2] += outdeg[t][ed.b] - (rev?1:0);
    stat[t][3] += indeg[t][ed.a] - (rev?1:0);
    stat[t][4] += stat[t][0] - (rev?2:1) - outdeg[t][ed.b] - indeg[t][ed.a];
    }

  for(int t=0; t<2; t++) for(int l=0; l<5; l++)
    printf("%d,%d: %Ld\n", t,l, stat[t][l]);
  
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
  for(auto it: edata) if(it.second.ingraph[MEMBER] && it.second.ingraph[FOLLOWER]) valat++;
  
  printf("common edges = %d\n", (int) valat);
  
  long double expected = stat[0][0] * (stat[1][0] * N2);
  
  long double expected2 = 
    stat[0][0] * (stat[1][0] * N2) +
    stat[0][1] * (stat[1][1] * N2) +
    stat[0][2] * (stat[1][2] * N3) +
    stat[0][3] * (stat[1][3] * N3) +
    stat[0][4] * (stat[1][4] * N4);
  
  long double variance = expected2 - expected * expected;
  
  printf("N1 = %Lf\n", N1);
  printf("N2 = %Lf\n", N2);
  printf("N3 = %Lf\n", N3);
  printf("N4 = %Lf\n", N4);
  
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
    if(it.second.ingraph[MEMBER]) cod += 1;
    if(it.second.revgraph[MEMBER]) cod += 2;
    if(it.second.ingraph[FOLLOWER]) cod += 4;
    if(it.second.revgraph[FOLLOWER]) cod += 8;
    qty[cod]++;
    }
  
  const char* names[4] = {"MEMBER", "MEMBER'", "FOLLOWER", "FOLLOWER'"};

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
