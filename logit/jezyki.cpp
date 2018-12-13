#include <stdio.h>
#include <ghutils.h>
#include <vector>
#include <map>

// FILE *fmyids = fopen("myids.txt", "wt");
// FILE *fstats = fopen("stats.txt", "wt");

#define MAXLINE 1000000000

typedef unsigned char uchr;

set<string> alllang;

#define IJ 360

struct osoba {
    string xlogin;
    uchr rozmiar;
    uchr padding;
    uchr org1, org2, usr1, usr2;
    uchr goodtime;
    uchr badtime;
    short reg;
    uchr ineryx, padding2;
    int forked; //user_forked
    int forked_pr;
    int forked_number;
    int followers; //user_follow_laczne[]
    int stars_obtained; //user_stars_laczne[1]
    int following; //user_follow_laczne[]
    int stars_given; //user_stars_laczne[2]
    int forking_others; //user_forking_others[2]
    int email; //user_information[2]
    int site; //user_information[1]
    int repos; //owner_number_repo
    int comments_self; //user_comments[2]
    int comments_others; //user_comments[1]
    int issues_self; //user_issues_opened[2]
    int issues_others; //user_issues_opened[1]
    double evc_following; //evc_following[1]
    //double evc_issues; //evc_issues[1]
    int commits_self_base;
    int commits_self_fork;
    int commits_others;	
    int ilejez;
    bool bug;
    vector<bool> mylang;
    int ilejeztyp[4];
  osoba() {
    rozmiar = org1 = org2 = usr1 = usr2 = goodtime = badtime = padding = 0;
    ineryx = padding2 = 0;
    reg = 32767;
    repos = -1;
    forked = 0;
    forked_pr = 0;
    forked_number = 0;
    followers = 0;
    stars_obtained = 0;
    following = 0;
    stars_given = 0;
    forking_others = 0;
    email = 0;
    site = 0;
    comments_self = 0;
    comments_others = 0;
    issues_self = 0;
    issues_others = 0;
    evc_following = 0;
    //evc_issues = 0;
    commits_self_base = 0;
    commits_self_fork = 0;
    commits_others = 0;
    ilejez = 0;
    for(int a=0; a<4; a++) ilejeztyp[a] = 0;
    mylang.resize(IJ);
    bug = false;
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

map<string, int> langids;
vector<string> langbyid;

int langid(string s) {
  if(langids.count(s)) return langids[s];
  langids[s] = langbyid.size();
  if(langbyid.size() >= IJ) return IJ-1;
  langbyid.push_back(s);
  return langids[s];
  }

int getmyid(const string& login) {
  string l = tolower(login);
  if(nomore && !grouptomyid.count(l)) return -1;
  int& gtm(grouptomyid[l]);
  if(gtm == 0 && !nomore) {
    gtm = nextid();
    osoby[gtm].xlogin = login;
//    fprintf(fmyids, "%d;%s\n", gtm, login.c_str());
    }
  return gtm;
  }

#define kol(val, nazwa) \
  {if(nr) of << ";"; if(i==0) of << (nazwa); else of << (val); nr++; }

#define kol2(val, nazwa) \
  kol((val), nazwa) kol((val)*(val), nazwa "2")
  
#define kolP(val, nazwa, cutoff) \
  kol(min((val),(cutoff)), nazwa) kol((val) < (cutoff) ? 0 : (val)-(cutoff), nazwa " over " #cutoff)

#define MAXLINE2 1000
  
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
  // fclose(fmyids);
  {csvparser in("../../id_eryx.csv", ',');
  in.next();
  while(in.next() && in.fields == 3) {
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[2]);
    int aid = tonum(in[0]);
    auto& o(osoby[id]);
    if(in[1] == "user") o.usr1++;
    else if(in[1] == "organization") o.org1++;
//    else fprintf(fstats, "unknown type %s in crawl\n", in[1].c_str());
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
    if(in.fields != 12) ; // fprintf(fstats, "bad fieldcount (%d) in users\n", in.fields);
    else {
      int id = getmyid(in[1]);
      auto& o(osoby[id]);

      if(in[5] == "1") in[4] = "ORG";
      if(in[6] == "1") in[4] = "ORG";

      if(in[4] == "USR") o.usr2++;
      else if(in[4] == "ORG") o.org2++;
      // else fprintf(fstats, "unknown type %s in users\n", in[4].c_str());

      string srok = in[3].substr(0, 4);
      string smon = in[3].substr(5, 2);
      int rok = atoi(srok.c_str());
      int mon = atoi(smon.c_str());
      int reg = rok * 16 + mon;
      if(reg < o.reg || ((o.reg&15) == 13)) o.reg = reg;
      if(rok >= 2000 && rok <= 2017) o.goodtime++;
      else if(rok >= 2017) o.badtime++;
      // else fprintf(fstats, "unknown date %s in users\n", in[3].c_str());
      }
    }
  }

  // fprintf(fstats, "qosoby = %d\n", qosoby);
  // fflush(fstats);

  {csvparser in("../../agregaty/users_char/user_forked.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].forked |= tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/user_forked_pulls.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].forked_pr |= tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/user_number_forks.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].forked_number += tonum(in[1]);
    }
  }
  

  {csvparser in("../../agregaty/users_char/user_follow_laczne.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].followers += tonum(in[2]);
    osoby[id].following += tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/user_stars_laczne.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].stars_obtained += tonum(in[1]);
    osoby[id].stars_given += tonum(in[2]);
    }
  }

  {csvparser in("../../agregaty/users_char/owner_number_repo.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    if(osoby[id].repos == -1) osoby[id].repos = 0;
    osoby[id].repos += tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/owner_number_forkedrepos.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].forking_others += tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/user_information.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].email |= tonum(in[2]);
    osoby[id].site |= tonum(in[1]);
    }
  }

  {csvparser in("../../agregaty/users_char/user_issues_opened.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].issues_self += tonum(in[2]);
    osoby[id].issues_others += tonum(in[1]);
    }
  }
  
  {csvparser in("../../agregaty/users_char/evc_following1.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].evc_following += tonum(in[1]);
    }
  }

  /*{csvparser in("../../agregaty/users_char/evc_issues.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 2) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].evc_issues += tonum(in[1]);
    }
    }*/

  {csvparser in("../../agregaty/users_char/user_comments.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].comments_others += tonum(in[1]);
    osoby[id].comments_self += tonum(in[2]);
    }
  }
  
  {csvparser in("../../agregaty/users_char/owner_number_lang.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 3) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    alllang.insert(in[1]);
    osoby[id].mylang[langid(in[1])] = 1;
    }
  }

  {csvparser in("/home/tehora/doktoratowe/user_commits.csv");
  in.next();
  while(in.next()) {
    if(in.fields != 4) continue;
    if(in.linenumber > MAXLINE) break;
    int id = getmyid(in[0]);
    osoby[id].commits_self_base+= tonum(in[1]);
    osoby[id].commits_self_fork+= tonum(in[2]);
    osoby[id].commits_others += tonum(in[3]);
    }
  }


  /* write_table(1,"../../agregaty/logit/tabela.csv");
  write_table(2,"../../agregaty/logit/tabela_pr.csv");
  write_table(3,"../../agregaty/logit/tabela_tobit.csv"); */

  map<string, int> ogolnie[3];

  for(int i=1; i<qosoby; i++) {
    osoba& o(osoby[i]);

          if(i > 0) {
            if(o.badtime && !o.goodtime) continue;
            if(o.org1 || o.org2) continue;
          int year = o.reg / 16;
            if(year > 2014) continue;
            if(o.repos <= 0) continue;
            if(o.bug && !o.forked) continue;
            
            if(o.repos > 80) continue;
            if(o.followers > 35) continue;
            if(o.stars_obtained > 140) continue;
            if(o.following > 40) continue;
            if(o.stars_given > 358) continue;
            //if(o.forking_others > ) continue;            

            if(o.comments_self > 130) continue;
            if(o.comments_others > 800) continue;
            if(o.issues_self > 110) continue;
            if(o.issues_others > 200) continue;

            if(o.evc_following > 2000) continue;
            //if(o.evc_issues > 4300) continue;
	    if(o.commits_self_base > 2200) continue;	           
	    if(o.commits_self_fork > 750) continue;
            if(o.commits_others > 4440) continue;	    
            }
    
    for(int k=0; k<3; k++) {
      if(k==0 || (k==1 && o.forked) || (k==2 && o.forked_pr)) {
        ogolnie[k]["ALL"]++;
         for(int i=0; i<IJ; i++) if(o.mylang[i]) ogolnie[k][langbyid[i]]++;
        }
      }
    }
   
  for(const string& s: alllang) {
    printf("{");
    for(int i=0; i<3; i++) printf("%.4lf, ", double(ogolnie[i][s] * 100. / (ogolnie[i]["ALL"])));
    printf("0x%06x, ", rand() & 0xFFFFFF);
    printf("\"%s\"},\n", s.c_str());
    }

  // fclose(fstats);
  return 0;
  }
