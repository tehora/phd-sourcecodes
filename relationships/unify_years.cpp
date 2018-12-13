#include <stdio.h>
#include <ghutils.h>
#include <vector>
#include <map>

FILE *fmyids = fopen("myids.txt", "wt");
FILE *fstats = fopen("stats.txt", "wt");

#define MAXLINE 1000000000

typedef unsigned char uchr;

map <pair<int, int>, int > graf;

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

int main(int argc, char **argv) {
//  printf("ed = %d\n", (int) sizeof(edge)); return 0; 
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

  {csvparser in(argv[1]);
  in.next();
  while(in.next()) {
    if(in.fields < 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id_source = getmyid(in[1]);
    int id_target = getmyid(in[2]);
    cout <<id_source <<";" <<id_target <<endl;
    if (graf.count(make_pair(id_source,id_target))==0) {
        graf[make_pair(id_source, id_target)]=tonum(in[0]); 
    } else {
        if (graf[make_pair(id_source, id_target)] > tonum(in[0])) {
            graf[make_pair(id_source, id_target)] = tonum(in[0]);
        }    
    }    
  }}
  
  {csvparser in("../../agregaty/ktoto2.csv");
  FILE *f = fopen("../../agregaty/my-ktoto.csv", "wt");
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[1]);
    if(id >= 0) fprintf(f, "%d;%s\n", id, in[2].c_str());
    }
  fclose(f);
  }

  fclose(fstats);

  ofstream of1(argv[2]);
  for ( auto& edge: graf) {  
      of1 <<edge.second <<";" <<edge.first.first <<";" <<edge.first.second << "\n";
  }    
  
  return 0;
  }
