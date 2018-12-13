#include <ghutils.h>
#include <vector>


vector<struct wsk*> grupy;

struct wsk {
  wsk *rep;
  const string *jakis_login;
  int ilog, igrav, iid;
  bool jest;
  wsk() { rep = this; ilog = igrav = iid = 0; jest = false; }
  void oznacz() { if(!jest) { jest = true; grupy.push_back(this); } }
  };

struct grupa {
  wsk* w;
  grupa() { w = new wsk; }
  };

map<string, grupa> loginy;
map<string, grupa> gravatary;
map<int, grupa> idki;

wsk *ufind(wsk* a) {
  if(a->rep == a) return a;
  else return a->rep = ufind(a->rep);
  }

wsk *ufind(grupa& a) { return ufind(a.w); }

void funion(wsk* a, wsk* b) { 
  a = ufind(a);
  b = ufind(b);
  a->rep = b;
  }

void funion(grupa& a, grupa& b) { funion(a.w, b.w); }

template<class T> wsk *ufind(pair<T, grupa>& a) { return ufind(a.second); }

int main() {
  {
  csvparser in1("../../agregaty/gha/nodes_gharchive.csv");
  in1.next();
  while(in1.next()) {
    if(in1.fields != 4) {
      fprintf(stderr, "zle pola\n");
      continue;
      }
    if(in1[2] == "") {
      if(in1[1] != "" && in1[3] != "" && in1[3] != "d41d8cd98f00b204e9800998ecf8427e") 
        funion(loginy[in1[1]], gravatary[in1[3]]);
      // fprintf(stderr, "brawo piesku! nie ma id\n");
      continue;
      }
    int id = tonum(in1[2]);
    if(in1[1] != "") funion(loginy[in1[1]], idki[id]);
    if(in1[3] != "" && in1[3] != "d41d8cd98f00b204e9800998ecf8427e") funion(gravatary[in1[3]], idki[id]);
    }
  }

  {
  csvparser in1("../../id_eryx.csv", ',');
  while(in1.next()) {
    if(in1.fields != 3) {
      fprintf(stderr, "zle pola\n");
      continue;
      }
    int id = tonum(in1[0]);
    if(in1[1] != "") funion(loginy[in1[2]], idki[id]);
  }
  }

  for(auto& p: gravatary) {
    auto x = ufind(p.second);
    x->oznacz();
    ufind(p.second)->jakis_login = &p.first, 
    ufind(p.second)->igrav++;
    }
  for(auto& p: idki) 
    ufind(p.second)->oznacz(), 
    ufind(p.second)->iid++;
  for(auto& p: loginy) 
    ufind(p.second)->oznacz(), 
    ufind(p.second)->jakis_login = &p.first, 
    ufind(p.second)->ilog++;
  
  {
  FILE *f = fopen("../../agregaty/statystyki.csv", "wt");
  for(auto g: grupy) fprintf(f, "%d;%d;%d;%s\n", ufind(g)->ilog, ufind(g)->igrav, ufind(g)->iid, ufind(g)->jakis_login->c_str());
  fclose(f);
  }

  {
  FILE *f = fopen("../../agregaty/ktoto.csv", "wt");
  for(auto& p: gravatary) fprintf(f, "g;%s;%s\n", ufind(p)->jakis_login->c_str(), p.first.c_str());
  for(auto& p: loginy) fprintf(f, "l;%s;%s\n", ufind(p)->jakis_login->c_str(), p.first.c_str());
  for(auto& p: idki) fprintf(f, "i;%s;%d\n", ufind(p)->jakis_login->c_str(), p.first);
  fclose(f);
  }

  return 0;
  }
