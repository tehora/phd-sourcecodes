#include <stdio.h>
#include <ghutils.h>
#include <vector>
#include <map>

FILE *fmyids = fopen("myids.txt", "wt");
FILE *fstats = fopen("stats.txt", "wt");

#define MAXLINE 1000000000

typedef unsigned char uchr;

set <pair<int, int> > graf;

struct osoba {
    string xlogin;
    uchr rozmiar;
    uchr padding;
    uchr org1, org2, usr1, usr2;
    uchr goodtime;
    uchr badtime;
    short reg;
    uchr ineryx, padding2;
  osoba() {
    rozmiar = org1 = org2 = usr1 = usr2 = goodtime = badtime = padding = 0;
    ineryx = padding2 = 0;
    reg = 32767;
    }
  };

map<string, int> grouptomyid;

vector<osoba> osoby;
int qosoby = 1;

int alledges = 0;

int nextid() {
  int v = qosoby++;
  osoby.resize(qosoby);
  return v;
  }

bool nomore = false;

int getmyid(const string& login) {
  string l = tolower(login);
  if(nomore && !grouptomyid.count(l)) return -1;
  int& gtm(grouptomyid[l]);
  if(gtm == 0 && !nomore) {
    gtm = nextid();
    osoby[gtm].xlogin = login;
    fprintf(fmyids, "%d;%s\n", gtm, login.c_str());
    }
  return gtm;
  }

void laczenie_cale() {
  osoby.resize(1);

  {csvparser in("../../agregaty/ktoto2.csv");
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[1]);
    grouptomyid[tolower(in[2])] = id;
    osoby[id].rozmiar++;
    }
  }
  fclose(fmyids);
  {csvparser in("../../id_eryx.csv", ',');
  in.next();
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[2]);
    int aid = tonum(in[0]);
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
    else if(aid <=10361315) o.reg = 2014*16+13;
    else o.reg = 2015*16+13;
    o.ineryx++;
    }
  }
  
  {csvparser in("../../rawdata/ght/users.csv", ',');
  in.next();
  while(in.next()) {
    if(in.linenumber > MAXLINE) break;
    if(in.fields != 12) fprintf(fstats, "bad fieldcount (%d) in users\n", in.fields);
    else {
      int id = getmyid(in[1]);
      auto& o(osoby[id]);

      if(in[5] == "1") in[4] = "ORG";
      if(in[6] == "1") in[4] = "ORG";

      if(in[4] == "USR") o.usr2++;
      else if(in[4] == "ORG") o.org2++;
      else fprintf(fstats, "unknown type %s in users\n", in[4].c_str());

      string srok = in[3].substr(0, 4);
      string smon = in[3].substr(5, 2);
      int rok = atoi(srok.c_str());
      int mon = atoi(smon.c_str());
      int reg = rok * 16 + mon;
      if(reg < o.reg || ((o.reg&15) == 13)) o.reg = reg;
      if(rok >= 2000 && rok <= 2017) o.goodtime++;
      else if(rok >= 2017) o.badtime++;
      else fprintf(fstats, "unknown date %s in users\n", in[3].c_str());
      }
    }
  }

  fprintf(fstats, "qosoby = %d\n", qosoby);
  fflush(fstats);
  }

struct event {
  int a, b;
  char type;
  int date;
  };

bool operator < (const event& e1, const event &e2) {
  if(e1.a != e2.a) return e1.a < e2.a;
  if(e1.b != e2.b) return e1.b < e2.b;
  if(e1.date != e2.date) return e1.date < e2.date;
  return e1.type < e2.type;
  }

vector<event> events;

int tid = 0;
inline bool testing() { 
  return false;
  // tid++; if(tid % 2000 == 0) return true;
  // return false;
  }

const int ZLA_DATA = 0;

void addEvent(event e) {
  if(e.date != ZLA_DATA && e.a != e.b)
    events.push_back(e);
  }

void addEvent2(event e) {
  addEvent(e);
  swap(e.a, e.b); e.type -= 32;
  addEvent(e);
  }

int readdate(string s) {
  if(s == "") return ZLA_DATA;

  int year, month, day, hour, minute, sec;
  sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &sec);
  if(year >= 2014) 
    return ZLA_DATA;
  
  struct tm wynik;
  wynik.tm_isdst = 0;
  char *x1 = strptime(s.c_str(), "%Y-%m-%d %H:%M:%S", &wynik);

  if(!x1) return 0;
  
  time_t res = mktime(&wynik);
  
  return res;
  }

void czytaj_eventy() {
  {csvparser in("/mnt/agregaty/laczenie_grafow/following_graf_laczny_crawl.csv");
  while(in.next()) {
    if(in.fields < 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[2]);
    int data = readdate(in[0]);
    addEvent2(event { id_source, id_target, 'f', data });
    }}
  {csvparser in("/mnt/agregaty/laczenie_grafow/forking_graf_laczny_crawl.csv");
  while(in.next()) {
    if(in.fields < 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[3]);
    int data = readdate(in[0]);
    addEvent2(event { id_source, id_target, 'm', data });
    }}
  {csvparser in("/mnt/agregaty/laczenie_grafow/starring_graf_laczny.csv");
  while(in.next()) {
    if(in.fields < 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[3]);
    int data = readdate(in[0]);
    addEvent2(event { id_source, id_target, 's', data });
    }}
  {csvparser in("/mnt/agregaty/laczenie_grafow/issues_graf_laczny.csv");
  while(in.next()) {
    if(in.fields < 5) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[3]);
    int data = readdate(in[0]);
    char type = '0';
    if (in[4] == "opened") {
        type ='i';
    } else {
        //if (in[4] == "closed") {
            type = 'd';
            //} else {
            //type = 'z';
            //}   
    }    
    addEvent2(event { id_source, id_target, type, data });
  }}
  {csvparser in("/mnt/agregaty/laczenie_grafow/pull_graf_laczny.csv");
  in.next();
  while(in.next()) {
    if(in.fields < 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[3]);
    int data = readdate(in[0]);
    char type = '0';
    if (in[4] == "synchronize") {
        continue;
    }   
    if (in[4] == "opened") {
        type ='p';
    } else {
        // if (in[4] == "closed") {
            type = 'g';
            //} else {
            //if (in[4] == "reopened") {
            //   type = 'y';
            //} else {
            //    type = 'x';
            //}    
            // }    
    }    
    addEvent2(event { id_source, id_target, type, data });
    }}
  {csvparser in("/mnt/agregaty/laczenie_grafow/comments_graf_laczny.csv");
  while(in.next()) {
    if(in.fields < 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[3]);
    int data = readdate(in[0]);
    addEvent2(event { id_source, id_target, 'c', data });
    }}
  }

void zliczaj_sekwencje() {
  FILE *f = fopen("wszystkie-pary.txt", "wt");
  sort(events.begin(), events.end());
  int S = events.size();
  string obecny_ciag = "";
  // string ociag;
  map<string, int> liczenie;
  for(int i=0; i<S; i++) {
    event &e(events[i]);
    
    if(i) {
      event &el(events[i-1]);
      
      if(e.a != el.a || e.b != el.b) {
        // fprintf(f,"%7d %7d %s\n", e.a, e.b, obecny_ciag.c_str());
        // if(ociag.size() < 80 && ociag.size() >= 15)
        //   fprintf(f, "%7d %7d %s\n", e.a, e.b, ociag.c_str());
        liczenie[obecny_ciag]++, obecny_ciag = "";
        // ociag = "";
        }
    
      else if(i && e.date > el.date + 3600*4) obecny_ciag += ':';
      }

    obecny_ciag += e.type;
    /* ociag += e.type;
    char data[16];
    sprintf(data, "%4d.%2d.%2d", e.date / 32/16, (e.date/32)%16, e.date%32);
    ociag += data; */
    }
  liczenie[obecny_ciag]++;
  fclose(f);
  
  f = fopen("sekwencje.txt", "wt");
  for(auto& p: liczenie)
    fprintf(f, "%9d %s\n", p.second, p.first.c_str());
  fclose(f);
  }

int main(int argc, char **argv) {
//  printf("ed = %d\n", (int) sizeof(edge)); return 0; 

  laczenie_cale();
  
  czytaj_eventy();
  
  zliczaj_sekwencje();

  return 0;
  }
