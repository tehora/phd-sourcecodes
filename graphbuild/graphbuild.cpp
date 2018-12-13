// execute twice to produce 2015.txt first

#include <stdio.h>
#include <ghutils.h>

FILE *fmyids = fopen("myids.txt", "wt");
FILE *fstats = fopen("stats.txt", "wt");

#define MAXLINE 1000000000

#include "data.cpp"

map<string, int> grouptomyid;

vector<osoba> osoby;
vector<int> fixids;
vector<edge> edges;
vector<int> lowid;
vector<int> idsort;
vector<int> numedges;
int qosoby = 1, qfixid = 0;

int alledges = 0;

int nextid() {
  int v = qosoby++;
  osoby.resize(qosoby);
  return v;
  }

bool nomore = false;

int getmyid(const string& login) {
  int& gtm(grouptomyid[tolower(login)]);
  if(gtm == 0 && !nomore) {
    gtm = nextid();
    fprintf(fmyids, "%d;%s\n", gtm, login.c_str());
    }
  return gtm;
  }

template<class T> void saveraw(const char *fname, vector<T>& v) {
  FILE *f = fopen(fname, "wb");
  T* t = &v[0];
  int q = v.size();
  fwrite(t, sizeof(T), q, f);
  fclose(f);
  }

bool operator == (edge e1, edge e2) {
  return e1.efrom == e2.efrom && e1.eto == e2.eto && e1.eflags == e2.eflags;
  }

bool operator < (edge e1, edge e2) {
  if(e1.efrom != e2.efrom) return e1.efrom < e2.efrom;
  if(e1.eto != e2.eto) return e1.eto < e2.eto;
  return e1.eflags < e2.eflags;
  }

void compactedges() { 
  int i = 1;
  int N = edges.size();
  for(int j=1; j<N; j++)
    if(edges[j].efrom == edges[i-1].efrom && edges[j].eto == edges[i-1].eto)
      edges[i-1].eflags |= edges[j].eflags;
    else
      edges[i++] = edges[j];
  edges.resize(i);
  }

const char *badtype[6] = { "Ok", "Unknown", "Late", "Org", "??", "Edgeless" };
  
void savegraph(const char *csv, int fields, int f1, int f2, int typ) {
  csvparser in(csv);
  int numloops = 0, numgood = 0;
  int numbad[5][5];
  for(int i=0; i<5; i++) for(int j=0; j<5; j++)  numbad[i][j] = 0;
  char bbugs[128]; sprintf(bbugs, "bugs/%s", csv);
  FILE *fbugs = fopen(bbugs, "wt");
  while(in.next()) {
    if(in.fields != fields) fprintf(fstats, "bad fieldcount (%d) in %s\n", in.fields, csv);
    if(in.linenumber > MAXLINE) break;
    int id1 = fixids[getmyid(in[f1])];
    int id2 = fixids[getmyid(in[f2])];
    if(id1 < 0 || id2 < 0) { 
      if(id1 > 0) id1 = 0;
      if(id2 > 0) id2 = 0;
      numbad[-id1][-id2]++;
      if(id1 == -1 || id2 == -1) 
        in.dump(fbugs);
      continue;
      }
    if(id1 == id2) { numloops++; continue; }
    numedges[id1]++;
    numedges[id2]++;
    edge ed;
    ed.efrom = id1; ed.eto = id2; ed.eflags = typ;
    edges.push_back(ed);
    ed.efrom = id2; ed.eto = id1; ed.eflags = typ<<1;
    edges.push_back(ed);
    numgood++;
    }
  sort(edges.begin(), edges.end());
  
  compactedges();
  
  int ntotal = edges.size();
  fprintf(fstats, "%s:\n", csv);
  for(int i=0; i<5; i++)
  for(int j=0; j<5; j++) if(numbad[i][j])
    fprintf(fstats, "  bad%s%s = %d\n", badtype[i], badtype[j], numbad[i][j]);
  fprintf(fstats, "  loops = %d, good = %d\n", numloops, numgood);
  fprintf(fstats, "  total = %d\n", ntotal);
  fflush(fstats);
  fclose(fbugs);
  }

/*
template<class T> void loadraw_push(const char *fname, vector<T>& v) {
  FILE *f = fopen(fname, "rb");
  fseek(f, 0, SEEK_END); int t = ftell(f) / v.size();
  int q = v.size();
  v.resize(q + t);
  T* t = &v[0];
  fseek(f, 0, SEEK_SET);
  fread(t, sizeof(T), q, f);
  fclose(f);
  }
*/

bool idcomp(int a, int b) {
  return lowid[a] < lowid[b];
  }

int main() {
//  printf("ed = %d\n", (int) sizeof(edge)); return 0;
  osoby.resize(1);
  {csvparser in("ktoto2.csv");
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[1]);
    grouptomyid[tolower(in[2])] = id;
    osoby[id].rozmiar++;
    }
  }
  {
  FILE *f2015 = fopen("2015.txt", "r");
  char buf[256];
  while(!feof(f2015)) { if(!fscanf(f2015, "%s", buf)) continue; osoby[getmyid(buf)].padding++; }
  fclose(f2015);
  }
  nomore = true;
  fclose(fmyids);
  {csvparser in("id_eryx.csv", ',');
  in.next();
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[2]);
    int aid = tonum(in[1]);
    auto& o(osoby[id]);
    if(in[1] == "user") o.usr1++;
    else if(in[1] == "organization") o.org1++;
    else fprintf(fstats, "unknown type %s in crawl\n", in[1].c_str());
    if(aid <= 2) o.reg = 2007*16+13;
    else if(aid <= 43569) o.reg = 2008*16+13;
    else if(aid <= 174849) o.reg = 2009*16+13;
    else if(aid <= 543015) o.reg = 2010*16+13;
    else if(aid <= 1296987) o.reg = 2011*16+13;
    else if(aid <= 3161234) o.reg = 2012*16+13;
    else if(aid <= 6295257) o.reg = 2013*16+13;
    o.ineryx++;
    }
  }
  lowid.resize(qosoby);
  const int INF = 20000000;
  for(int i=0; i<qosoby; i++) lowid[i] = INF;
  FILE *f2015 = fopen("2015.txt", "wt");
  {csvparser in("users.csv", ',');
  in.next();
  while(in.next()) {
    if(in.linenumber > MAXLINE) break;
    if(in.fields != 12) fprintf(fstats, "bad fieldcount (%d) in users\n", in.fields);
    else {
      int id = getmyid(in[1]);
      auto& o(osoby[id]);
      
      lowid[id] = min(lowid[id], tonum(in[0]));

      if(in[4] == "USR") o.usr2++;
      else if(in[4] == "ORG") o.org2++;
      else fprintf(fstats, "unknown type %s in users\n", in[4].c_str());
      
      string srok = in[3].substr(0, 4);
      string smon = in[3].substr(5, 2);
      int rok = atoi(srok.c_str());
      int mon = atoi(smon.c_str());
      int reg = rok * 16 + mon;
      if(reg < o.reg || ((o.reg&15) == 13)) o.reg = reg;
      if(rok >= 2015) fprintf(f2015, "%s\n", tolower(in[1]).c_str());
      if(rok >= 2000 && rok <= 2015) o.goodtime++;
      else if(rok >= 2016) o.badtime++;
      else fprintf(fstats, "unknown date %s in users\n", in[3].c_str());
      }
    }
  }
  fclose(f2015);
  
  {
    osoba& o(osoby[0]);
    fprintf(fstats, "[0] %d/%d %d/%d %d/%d\n",
      o.org1, o.usr1,
      o.org2, o.usr2,
      o.goodtime, o.badtime);
    fflush(fstats);
    }

  fixids.resize(qosoby);
  fixids[0] = -1;
  for(int i=1; i<qosoby; i++) {
    osoba& o(osoby[i]);
    fixids[i] = -4;
    if(o.badtime && !o.goodtime)
      fixids[i] = -2;
    else if(o.org1 || o.org2)
      fixids[i] = -3;
    else
      idsort.push_back(i);
    }
  sort(idsort.begin(), idsort.end(), idcomp);
  for(int i=0; i< (int) idsort.size(); i++)
    fixids[idsort[i]] = i;
  qfixid = idsort.size();
  fprintf(fstats, "qosoby = %d, OK = %d\n",
    qosoby, qfixid);
  fflush(fstats);
  
  vector<osoba> o2;
  o2.resize(qfixid);
  for(int i=0; i<qosoby; i++) if(fixids[i] >= 0)
    o2[fixids[i]] = osoby[i];
  swap(osoby, o2);
  
  numedges.resize(qfixid);
  for(int i=0; i<qfixid; i++) numedges[i] = 0;
  
  savegraph("following_graf_laczny_crawl.csv", 3, 1, 2, 1);
  savegraph("forking_graf_laczny_crawl.csv", 4, 1, 3, 4);
  savegraph("pull_graf_laczny.csv", 6, 1, 3, 16);
  savegraph("starring_graf_laczny.csv", 4, 1, 3, 64);
  savegraph("issues_graf_laczny.csv", 6, 1, 3, 256);

  int qfix2 = 0;
  for(int i=0; i<qfixid; i++)
    if(numedges[i] != 0)
      numedges[i] = qfix2++;
    else
      numedges[i] = -5;
  
  fprintf(fstats, "%d -> %d have edges\n", qfixid, qfix2);
  for(int i=0; i<qosoby; i++) if(fixids[i] >= 0) fixids[i] = numedges[fixids[i]];
  for(int i=0; i<qfixid; i++) if(numedges[i] >= 0) osoby[numedges[i]] = osoby[i];
  osoby.resize(qfix2);
  for(auto& e: edges) {
    e.efrom = numedges[e.efrom];
    e.eto = numedges[e.eto];
    }
  
  saveraw("raw/osoby.data", osoby);
  saveraw("raw/fixid.data", fixids);
  
  saveraw("raw/graph.data", edges);

  {
  FILE *f2015 = fopen("2015.txt", "r");
  char buf[256];
  while(!feof(f2015)) { 
    if(!fscanf(f2015, "%s", buf)) continue;
    int id = fixids[getmyid(buf)];
    if(id >= 0) fprintf(f2015, "%d;%s\n", id, buf);
    }
  fclose(f2015);
  }

  {csvparser in("ktoto2.csv");
  FILE *f = fopen("my-ktoto.csv", "wt");
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = fixids[getmyid(in[1])];
    if(id >= 0) fprintf(f, "%d;%s\n", id, in[2].c_str());
    }
  fclose(f);
  }
  
  fclose(fstats);
  return 0;
  }
