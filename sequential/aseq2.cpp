// Sequence analyzer
//   aseq <data>

// data format: each line is of form
//   qty <list-of-events>
// where events are from the 'events' string below, separated by colons if they are long time apart

// findall finds all the sequences with support >= 1000
// analyze performs the analysis based on the supports
// it is also possible to do the two steps separately:
//   aseq -i <data> -f > seq-supports
//   aseq -i seq-supports -a

// simply count supports interactively:
// ./aseq -i <data> -in

bool dofindall = true, doanalyse = true, dointeract = false;

#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <string.h>
#include <string_view>

using namespace std;

map<vector<int>, int> ss, supports;

bool supported(const vector<int>& subseq, const vector<int>& supseq) {
  int pos = 0;
  for(int elem: supseq) {
    if(pos == subseq.size()) return true;
    else if((elem & subseq[pos]) == subseq[pos]) pos++;
    }

  return pos == subseq.size();
  }

int numtimes[256];
char buf[700000];

map<int, pair<int, int> > numtimes_code;

using namespace std::literals;

//constexpr string_view events = "fFmMsScCiIdDzZpPgGyYxX"sv;
constexpr string_view events = "fFmMsScCiIdDpPgG"sv;
constexpr int etypes = events.size();


vector<int> encode(char *b) {
  int cc = 0;
  vector<int> res;
  for(char *p = b; *p; p++) 
    if(*p == ':') { res.push_back(cc); cc=0; }
    else for(int t=0; t<etypes; t++) if(*p == events[t]) { cc |= (1<<t); }
  res.push_back(cc);
  return res;
  }

#define LOW 10

vector<int> seq;

int total;

FILE *results;

int countocc() {
  int qty = 0;
  for(auto p: ss) if(supported(seq, p.first)) qty += p.second;
  return qty;
  }

int countoccApprox() {
  int qty = 0;
  for(auto p: ss) if(p.second <= LOW || supported(seq, p.first)) qty += p.second;
  return qty;
  }

char *prval(int i) {
  int pos = 0;
  for(int t=0; t<etypes; t++) if((i>>t)&1)
    buf[pos++] = events[t];
  buf[pos] = 0;
  return buf;
  }

char *prseq() {
  int pos = 0;
  for(int i: seq) {
    for(int t=0; t<etypes; t++) if((i>>t)&1)
      buf[pos++] = events[t];
    buf[pos++] = ':';
    }
  pos--; buf[pos] = 0;
  return buf;
  }

void findall();

void pamore(int z);

void findall_more(int z) {
  int S = seq.size();
  for(; z<etypes; z++) {
    seq[S-1] |= (1<<z);
    pamore(z);
    seq[S-1] &= ~(1<<z);
    }
  findall();
  }

void findall() {
  for(int z=0; z<etypes; z++) {
    int S = seq.size();
    seq.push_back(1<<z);
    pamore(z);
    seq.pop_back();
    }
  }

void pamore(int z) {
  int coa = countoccApprox();
  if(coa < 1000000) return;
  int co = countocc();
  if(co > 0) supports[seq] = co;
  if(co >= 1) {
    char *buf = prseq();
    printf("%10d %10d %s\n", co, coa, buf);
    fflush(stdout);
    findall_more(z+1);
    }
  }

struct triev {
  array<triev*, etypes> next;
  int last;
  list<triev*> children;
  int qty = 0;
  triev() { for(int i=0; i<etypes; i++) next[i] = NULL; }
  };

triev *root;

typedef vector<pair<int, triev*>> leafvec;
leafvec leaves;

#define THRESHOLD 1000

FILE *supf;

void try_appending(leafvec& where, int total) {
  int N = where.size();
  leafvec cut;
  cut.reserve(N);
  for(int i=0; i<etypes; i++) {
    int left = total, incut = 0;
    cut.clear();
    for(auto w: where) {
      auto t = w.second->next[i];
      if(!t) { left -= w.first; if(left < THRESHOLD) break; }
      else { incut += w.first; cut.emplace_back(w.first, t); }
      }
    if(incut < THRESHOLD) continue;
    seq.push_back(1<<i);
    supports[seq] = incut;
    int cutsiz = cut.size();
    for(auto p: cut) p.second->qty += p.first;
    int cutsiz2 = 0;
    for(auto p: cut) if(p.second->qty) {
      cut[cutsiz2++] = {p.second->qty, p.second};
      p.second->qty = 0;
      }
    cut.resize(cutsiz2);
    printf("%s:%d (%d/%d)\n", prseq(), incut, cutsiz, cutsiz2);
    fprintf(supf, "%7d %s\n", incut, prseq()); fflush(supf);
    if(size(seq) < 3)
      try_appending(cut, incut);
    seq.pop_back();
    }
  }

void findall_new() {
  supf = fopen("support-data.txt", "wt");
  root = new triev;
  for(auto p: ss) {
    triev* at = root;
    for(int i=p.first.size()-1; i>=0; i--) {
      int val = p.first[i];
      triev* ths = NULL;
      for(auto tv: at->children) if(tv->last == val) { ths = tv; break; }
      if(!ths) { 
        ths = new triev; 
        ths->last = val;
        for(int i=0; i<etypes; i++)
          if(val & (1<<i))
            ths->next[i] = at;
          else
            ths->next[i] = at->next[i];
        at->children.push_back(ths);
        }
      at = ths;
      }
    leaves.emplace_back(p.second, at);
    }
  sort(leaves.begin(), leaves.end(), [] (auto a, auto b) { return a.first > b.first; });
  int allqty = 0;
  for(auto p: leaves) allqty += p.first;
  try_appending(leaves, allqty);
  fclose(supf);
  }
    
int minrule = 0;
char tryb = 'i';

const char *infile = "sekwencje2";

bool norep = false;

int main(int argc, char ** argv) { 
  for(int i=1; i<argc; i++) {
    if(strcmp(argv[i], "-i") == 0)
      i++, infile = argv[i];
    if(strcmp(argv[i], "-m") == 0)
      i++, minrule = atoi(argv[i]);
    if(strcmp(argv[i], "-a") == 0) dofindall = false;
    if(strcmp(argv[i], "-f") == 0) doanalyse = false;
    if(strcmp(argv[i], "-in") == 0) dointeract = true;
    if(strcmp(argv[i], "-nr") == 0) norep = true;
    }
  
  FILE *f = fopen(infile, "rt");
  int qty;
  while(!feof(f)) {
    fscanf(f, "%d%s", &qty, buf);
    if(qty < minrule) continue;
    if(buf[0] == '*') continue;
    for(char *p=buf; *p; p++) numtimes[(unsigned char) *p] += qty;
    seq = encode(buf);
    if(norep) {
      bool haverep = false;
      for(const int& u: seq) for(const int& v: seq) 
        if((&u) != (&v) && (u&v)) haverep = true;
      if(haverep) continue;
      }
    ss[seq] += qty;
    }
  fclose(f);
  
  for(auto& s: ss)
    for(int c: s.first)
      numtimes_code[c].first++,
      numtimes_code[c].second += s.second;
    
  for(auto& c: numtimes_code) 
    fprintf(stderr, "%-15s: %d (%d)\n", prval(c.first), c.second.first, c.second.second);
  
  for(int z=0; z<256; z++) if(numtimes[z]) fprintf(stderr, "%c: %d\n", z, numtimes[z]);
  
  total = 0;
  int ones = 0;
  int lines = 0;
  for(auto p: ss) {
    total += p.second;
    if(p.second <= LOW) ones++;
    lines++;
    }
  
  fprintf(stderr, "total = %d, low = %d, lines = %d\n", total, ones, lines);

  if(dointeract) {
    while(true) {
      scanf("%s", buf);
      if(buf[0] == '0') break;
      seq = encode(buf);
      printf("%d\n", countocc());
      }
    }
  
  if(dofindall) {
    seq.clear();
    results = fopen("seq-results.txt", "w");
    findall_new();
    }
    
  if(doanalyse) {
    if(!dofindall) swap(supports, ss);

    vector<pair<double, vector<int> > > csorted;

    for(auto p: supports) {
      bool okay = true;
//    for(auto q: ss) 
//      if(p.first != q.first && supported(p.first, q.first)) 
//        okay = false;
      if(okay) {
        seq = p.first;
        printf("%10d %s", p.second, prseq());
        if(p.first.size() > 1) {
          seq = p.first;
          seq.pop_back();
          double conf = p.second * 1./ supports[seq];
          printf(" (conf=%.3f)", conf);
          csorted.push_back(make_pair(conf, p.first));
          printf(" (lift=%.13f)", conf*total/supports[{p.first.back()}]);
          printf(" (conv=%.13f)", (1- supports[{p.first.back()}]/total)/(1 - conf));
          }
        printf(" (supp=%.13f)", p.second * 1. / total);
        printf("\n");
        }
      }

    sort(csorted.begin(), csorted.end());
    for(auto p: csorted) seq=p.second, printf("%.3f %8d %s \n", p.first, supports[p.second], prseq());
    }
  
  return 0;
  }
 
