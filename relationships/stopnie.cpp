#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

int N, M;

vector<int> ids;

struct edge {int a, b, t; bool invalid; };

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

  int qty[16];

int main() {
  scanerr=scanf("%d%d", &N, &M);
  ids.resize(N);
  for(int i=0; i<N; i++) scanerr=scanf("%d", &ids[i]);
  edges.resize(M);
  for(int i=0; i<M; i++) scanerr=scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].t);
  
  // for(int i=0; i<M; i++) if(edges[i].t == FOLLOWER) swap(edges[i].a, edges[i].b);
  
  printf("invalid\n");
  
  FILE *fnarc = fopen("wyniki/narcissist.txt", "wt");

 for(int i=0; i<M; i++) {
   edges[i].invalid = edges[i].a == edges[i].b;
   if(edges[i].invalid) {
     fprintf(fnarc, "narcissist %s found at %d!!\n", nameof(edges[i].t), ids[edges[i].a]);
     continue;
     }
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
 
  fclose(fnarc);
   
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

  FILE *f = fopen("wyniki/deg.txt", "wt");
  fprintf(f, "id,in-members,out-members,in-followers,out-followers\n");
  for(int i=0; i<N; i++) fprintf(f, "%d,%d,%d,%d,%d\n", 
    ids[i], indeg[0][i], outdeg[0][i], indeg[1][i], outdeg[1][i]);
  fclose(f);
  
  printf("ile\n");
 
  f = fopen("wyniki/liczby.txt", "wt");
  int ile[2], ilek[2][2];
  
  for(int t=0; t<2; t++) {
    ile[t] = 0;
    for(int i=0; i<N; i++) if(indeg[t][i] || outdeg[t][i]) ile[t]++;
    fprintf(f, "ile[%s] = %d\n", nameof(t), ile[t]);
    for(int l=0; l<2; l++) {
      ilek[t][l] = 0;
      for(int i=0; i<M; i++) 
        if(l == 0 ? edges[i].invalid : !edges[i].invalid)
          if(edges[i].t == t) 
            ilek[t][l]++;
      fprintf(f, "ilek[%s][%s] = %d\n", nameof(t), l?"valid":"invalid", ilek[t][l]);
      }
    }
  fclose(f);
  
  for(auto p: edata) {
    int g = 0;
    g += p.second.ingraph[0];
    g += p.second.revgraph[0] *2;
    g += p.second.ingraph[1] *4;
    g += p.second.revgraph[1] *8;
    qty[g]++;
    }
  
  printf("kraw\n");
  f = fopen("wyniki/kraw.txt", "wt");
  for(int a=0; a<16; a++) {
    if(a == 0) fprintf(f, "FOLLOWER     ");
    if(a == 4) fprintf(f, "FOLLOWER --> ");
    if(a == 8) fprintf(f, "FOLLOWER <-- ");
    if(a == 12) fprintf(f, "FOLLOWER <-> ");
    fprintf(f, "%8d", qty[a]);
    if(a%4 == 3) fprintf(f, "\n");
    }
  fprintf(f, "\n");
  fclose(f);
  
  vector<int> notnarc;
  for(int i=0; i<N; i++) 
    if(indeg[0][i] || outdeg[0][i] || indeg[1][i] || outdeg[1][i]) 
      notnarc.push_back(i);
  int NN = notnarc.size();
  
  printf("symulacje\n");
  f = fopen("wyniki/symulacje.txt", "wt");
  for(int iter=0; iter<10003; iter++) {
    int nid[N];
    for(int i=0; i<N; i++) nid[i] = i;
    if(iter) for(int i=0; i<NN; i++) swap(nid[notnarc[i]], nid[notnarc[rand() % (i+1)]]);
    map<pair<int, int>, int> edata2;
    for(int i=0; i<M; i++) if(!edges[i].invalid) {
      int a = edges[i].a;
      int b = edges[i].b;
      int t = edges[i].t;
      if(t) a = nid[a], b = nid[b];
      edata2[make_pair(a,b)] |= (t?1:2);
      }
    long long eqty[4];
    for(int k=0; k<4; k++) eqty[k] = 0;
    for(auto z: edata2) eqty[z.second]++;
    eqty[0] = NN * (long long) (NN-1);
    for(int u=1; u<4; u++) eqty[0] -= eqty[u];
    fprintf(f, "%5d %20Ld %10Ld %10Ld %10Ld\n", iter, eqty[0], eqty[1], eqty[2], eqty[3]);
    fflush(f);
    }
  fclose(f);
  
  return 0;
  }
