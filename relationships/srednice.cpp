#include <stdio.h>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> indeg[2], outdeg[2];

int scanerr;

#define MEMBER 0
#define FOLLOWER 1

const char *nameof(int t) { return t?"FOLLOWER":"MEMBER"; }

map<pair<int, int>, int> edata;

  int qty[16];

vector<vector<int>> ebv;

#define MAXN 15000000

int qu[MAXN];
int lv[MAXN];
int fr[MAXN];  
int gd[MAXN];
int maxdiam[MAXN];

#include "czytgraf.cpp"

  int ile = 0;

void dod(vector<int>&v, int u) {
  for(int i: v) if(i == u) return;
  v.push_back(u);
  ile++;
  }
  
int main(int argc, char **argv) {  
  int t = 0;
  czytgraf(argv[1], 0);
  printf("renumer\n"); fflush(stdout);
  renumer();
  
  printf("N = %d M = %d\n", N, M); fflush(stdout);
  
  int twoside = 0;

#if 1
  ebv.resize(N);
  for(int i=0; i<M; i++) if(edges[i].a != edges[i].b) {
    dod(ebv[edges[i].a], edges[i].b);
    dod(ebv[edges[i].b], edges[i].a);
    }
#else
  
 for(int i=0; i<M; i++) {
   edges[i].invalid = edges[i].t != t || edges[i].a == edges[i].b;
   if(edges[i].invalid) continue;
   int& ed(edata[make_pair(edges[i].a, edges[i].b)]);
   if(ed) { edges[i].invalid = true; twoside++; }
   ed++;

   if(edges[i].invalid) continue;
   {
   int& ed(edata[make_pair(edges[i].b, edges[i].a)]);
   ed++;
   }
   }
 
  printf("build ebv\n"); fflush(stdout);
  ebv.resize(N);
  
  for(int i=0; i<M; i++) if(!edges[i].invalid) {
    ile++;
    ebv[edges[i].a].push_back(edges[i].b);
    ebv[edges[i].b].push_back(edges[i].a);
    }
#endif

  time_t lastt = 0;  
  
  printf("ile = %d twoside = %d\n", ile, twoside); fflush(stdout);

  for(int i=0; i<N; i++) lv[i] = -1;

  int diammin = 0, diammax = N;

  for(int i=0; i<N; i++) maxdiam[i] = N;
  
  map<int, int> compsizes;
  
  for(int i=0; i<N; i++) {
    if(diammin < maxdiam[i]) {
      bool newc = lv[i] == -1;
      int qb=0, qe = 1;
      qu[0] = i; lv[i] = i; gd[i] = 0;
      while(qb < qe) {
        int j = qu[qb++], gdj = gd[j]+1;
        for(int k: ebv[j]) if(lv[k] != i)
          qu[qe++] = k, lv[k] = i, fr[k] = j, gd[k] = gdj;
        }
      int diam = 0, at = qu[qe-1];
      while(at != i) { at = fr[at]; diam++; }

      if(diam > diammin) {
        diammin = diam;
        lastt = 0;
        }
      
      if(newc) compsizes[qe]++;
      
      int md = maxdiam[i];

      for(int j=0; j<qe; j++) 
        maxdiam[qu[j]] = min(maxdiam[qu[j]], gd[qu[j]] + diam);

      /* diammax = min(diammax, diam + diam - diammin); */
      // printf("%9d %2d [%2d]\n", i, diam, md);

      if(time(NULL) > lastt && qe >= 10) {
              time_t t = time(NULL); lastt = t;
              struct tm *tmp = localtime(&t);
              char buf[100]; 
              strftime(buf, 100, " %y/%m/%d %H:%M:%S", tmp);
  
        printf("%7.3f%% %7d %2d [%2d/%2d] %s\n", (100.*i)/N, i, diammin, diam, md, buf);
        fflush(stdout);
        }
      }
    
    
    }
  
  for(auto p: compsizes) printf("%d x %d\n", p.first, p.second);
  
  return 0;
  }
