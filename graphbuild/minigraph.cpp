// execute twice to produce 2015.txt first

#include <stdio.h>
#include <ghutils.h>

#include "data.cpp"

vector<edge> edges;
vector<osoba> osoby;

template<class T> void loadraw(const char *fname, vector<T>& v) {
  FILE *f = fopen(fname, "rb");
  fseek(f, 0, SEEK_END);
  long long s = ftell(f);
  fseek(f, 0, SEEK_SET);
  int q = s / sizeof(T);
  v.resize(q);
  if(fread(&(v[0]), sizeof(T), q, f) != q) fprintf(stderr, "bad read\n");
  fclose(f);
  }

int vcount = 0, ecount = 0;
  
void markos(int id) {
  if(!osoby[id].padding2)
    osoby[id].padding2 = true, vcount++;
  }
  
int main() {
  loadraw("raw/osoby.data", osoby);
  loadraw("raw/graph.data", edges);
  
  fprintf(stderr, "edges = %d osoby = %d\n", (int) edges.size(), (int) osoby.size());
  for(auto e: edges)
    if(e.eflags & 64)
    if(osoby[e.efrom].reg < (2011+1) * 16)
    if(osoby[e.eto].reg < (2011+1) * 16) {
      printf("%d %d\n", e.efrom, e.eto);
      ecount++;
      markos(e.efrom);
      markos(e.eto);
      }
    
  fprintf(stderr, "-> edges = %d osoby = %d\n", ecount, vcount);
  return 0;
  }
