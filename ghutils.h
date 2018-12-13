#include <fstream>
#include <iostream>

using namespace std;


#include <map>
#include <set>
#include <algorithm>

#define MAXF 528

struct csvline {
  int fields;
  string row[MAXF];
  char sep;
  bool inquote;
  bool inescape;
  bool escquote;
    
  virtual int location()  { return 0; }
  
  string& operator [] (int i) { return row[i]; }

  csvline(char _sep = ';') : sep(_sep) { inquote = false; fields = 0; escquote = false; inescape = false; }
  
  bool nonempty() { return fields > 1 || row[0] != ""; }

  string getline() {
    bool quote = false;
    string answer;
    for(int i=0; i<fields; i++) {
      for(char c: row[i]) if(c == sep) quote = true;
      if(i) answer += sep;
      if(quote) answer += "\"";
      answer += row[i];
      if(quote) answer += "\"";
      }
    return answer;
    }

  void eatinit() { fields = 0; row[fields].clear(); }
  
  void eatchar(char c) {
    if(c == 13) ;
    else if(escquote && inescape && c == '"') inescape = false, inquote = false;
    else if(inescape) inescape = false;
    else if(c == '"') inquote = !inquote;
    else if(c =='\\' && inquote) inescape = true;
    else if(c == sep && !inquote) { 
      fields++; 
      if(fields == MAXF) { 
        fprintf(stderr, "error: too many fields in line %d\n", location()); 
        for(int i=0; i<MAXF; i++) fprintf(stderr, "%s;", row[i].c_str());
        exit(1); 
        }
      row[fields].clear(); 
      }
    else row[fields] += c;
    }
  
  void eateof() { fields++; }
  
  bool eatline(const string& s) {
    eatinit();
    for(char c: s) eatchar(c);
    eateof(); return nonempty();
    }
  };

struct csvparser : csvline {
  string fname;
  FILE *in;
  int linenumber;
  long long fsize, fpos;
  bool doprogressbar;

  int location() { return linenumber; }
  
  csvparser(const string& _fname, char _sep = ';') : csvline(_sep), fname(_fname) { 
    in = fopen(fname.c_str(), "rt"); linenumber = -1; 
    if(!in) {
      fprintf(stderr, "ERROR: file missing: %s\n", _fname.c_str());
      exit(1);
      }
    fseek(in, 0, SEEK_END); fsize = ftell(in); rewind(in);
    fpos = 0;
    doprogressbar = true;
    }
  
  int opbpos = -1;
  
  void progressbar() {
    int pbpos = 64 * fpos / fsize;
    if(pbpos != opbpos) {
      opbpos = pbpos;
      fprintf(stderr, "[");
      for(int k=0; k<pbpos; k++) fprintf(stderr, "#");
      for(int k=pbpos; k<64; k++) fprintf(stderr, "-");
      fprintf(stderr, "] %s\r", fname.c_str());
      fflush(stderr);
      }
    }
  
  ~csvparser() {
    if(doprogressbar) fprintf(stderr, "\n"); 
    }

  bool next() {
    if(feof(in)) return false;
    linenumber++;
    eatinit();
    while(!feof(in)) {
      int c = fgetc(in); 
      if(c == -1) break;
      fpos++;      
      if(c == 10 && !inquote) { 
        eateof(); 
        if(doprogressbar) progressbar();
        return nonempty(); 
        }
      else eatchar(c);
      }
    eateof(); return nonempty();
    }  
  };

void closeprogressbar() { fprintf(stderr, "\n"); } // fprintf(stderr, "\x1b[K"); }

int tonum(const string& s) { return atoi(s.c_str()); }

time_t dajczas(string data) {
  struct tm wynik;
  wynik.tm_isdst = 0;
  int fmt = 1;
  char *x1 = strptime(data.c_str(), "%Y-%m-%dT%H:%M:%S", &wynik);
  if(!x1)
    fmt = 2, x1 = strptime(data.c_str(), "%Y/%m/%d %H:%M:%S", &wynik);
  if(!x1)
    fmt = 3, x1 = strptime(data.c_str(), "%Y-%m-%dT%H:%M:%SZ", &wynik);
  if(!x1) return 0;
  
  char sign;
  int hr, minute;
  
  if(fmt == 1) {
    sscanf(data.c_str()+19, "%c%d:%d", &sign, &hr, &minute);
    }
  else if(fmt == 2) {
    sscanf(data.c_str()+20, "%c%d", &sign, &hr);
    minute = hr % 100; hr /= 100;
    }
  else { hr=0; minute=0; }
  
  time_t res = mktime(&wynik);
  if(sign == '+') res -= (hr *3600 + minute * 60);
  if(sign == '-') res += (hr *3600 + minute * 60);
  
  return res;
  }

string formatuj(time_t data, int typ) {
  
  struct tm wynik;
#ifndef TASAMASTREFA
  data -= typ * 3600; 
#endif
  
  gmtime_r(&data, &wynik);
  // printf("i = %d\n", i);
  
  char buf[64];
  strftime(buf, 64, "%Y-%m-%d %H:%M:%S", &wynik);
  
  return buf;
  }

string tolower(string t) {
   for(char& c: t) c = tolower(c);
   return t;
}    

template<class A, class B> struct fixerof {
  map<A, B> fixy;
  int brak, poprawki, bylodobrze;
  string nazwa;
  FILE *f;

  fixerof (string _nazwa = "fixer") {  nazwa = _nazwa; f = stdout; }
  
  void add(const A& id, const B& f) { fixy[id] = f; }
  
  void fix(const A& id, B& f) {
    if(!fixy.count(id)) brak++;
    else if(fixy[id] == f) bylodobrze++;
    else f = fixy[id], poprawki++;
    }
  
  ~fixerof() {
    if(f) fprintf(f, "%s: brak %d, poprawki %d, bylo dobrze %d\n",
      nazwa.c_str(), brak, poprawki, bylodobrze);
    }
  };

typedef fixerof<int, string> fixer;

struct searcher {
  string nazwa;
  map<string, int> data;
  FILE *f;
  void insert(const string& z) { data[z]++; }
  
  int bylo, niebylo;
  searcher (string _nazwa = "searcher") { 
    nazwa = _nazwa; bylo=0; niebylo=0; f = stdout; 
    }
  
  bool niema(int t, const string& z) {
    auto niema = [&] (int i, int j) {
      const string &str = formatuj(t+j, i)+z;
      if(!data.count(str)) return true;
      int &ile = data[str];
      if(!ile) return true;
      ile--;
      return false;
      };
    bool nima = true;
    for(int hr: {0,1,2}) for(int sek:{0,-1,1})
      nima = nima && niema(hr, sek);
    if(nima) niebylo++;
    else bylo++;
    return nima;
    }
  
  ~searcher() {
    if(f) fprintf(f, "%s: wczytano %d, znaleziono powtorzen %d, nowe %d\n", nazwa.c_str(), int(data.size()), bylo, niebylo);
    }
  };

struct searcher2 {
  string nazwa;
  map<string, pair<int, int>> data;
  FILE *f;
  void insert(const string& z, int key) { auto &d = data[z]; d.first++; d.second = key; }
  
  int bylo, niebylo;
  searcher2 (string _nazwa = "searcher") { 
    nazwa = _nazwa; bylo=0; niebylo=0; f = stdout; 
    }
  
  int kod(int t, const string& z) {
    int jakikod;
    auto jest = [&] (int i, int j) {
      const string &str = formatuj(t+j, i)+z;
      if(!data.count(str)) return false;
      auto& d = data[str];
      int &ile = d.first;
      if(!ile) return false;
      ile--; jakikod = d.second; bylo++;
      return true;
      };
    for(int hr: {0,1,2}) for(int sek:{0,-1,1})
      if(jest(hr, sek)) return jakikod;
    niebylo++;
    return -1;
    }
  
  ~searcher2() {
    if(f) fprintf(f, "%s: wczytano %d, znaleziono powtorzen %d, nowe %d\n", nazwa.c_str(), int(data.size()), bylo, niebylo);
    }
  };

