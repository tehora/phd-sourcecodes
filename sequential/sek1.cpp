#include <stdio.h>
#include <zlib.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

gzFile f;

int readnum() {
  int res = 0;
  while(true) { 
    char c = gzgetc(f);
    if(c == ',' || c == '\n') break;
    if(c < '0' || c > '9') { 
      fprintf(stderr, "ZLE DUPI %c", c); 
      for(int k=0; k<50; k++) fprintf(stderr, "%c", gzgetc(f));
      fprintf(stderr, "\n");
      exit(1); 
      }
    res *= 10; res += c - '0'; 
    }
  return res;
  }

int readnumOrNul() {
  int res = 0;
  while(true) { 
    char c = gzgetc(f);
    if(c == ',') break;
    if(c < '0' || c > '9') {
      while(gzgetc(f) != ',') ;
      return -1;
      }
    res *= 10; res += c - '0'; 
    }
  return res;
  }

void toeol() {
  while(true) {
    char c = gzgetc(f);
    if(c == '\n') break;
    if(c == '\\') gzgetc(f);
    }
  }

int bufpos;
char buf[16000];

void readstr() {
  bool inquote = false;
  bufpos = 0;
  while(true) {
    char c = gzgetc(f);
    if(c == '\"') inquote = !inquote;
    else if(c == ',' && !inquote) break;
    else if(c == '\n') break;
    else buf[bufpos++] = c;
    }
  }

int readdate() {
  readstr();
  int year, month, day, hour, minute, sec;
  sscanf(buf, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &sec);
  int kod = year;
  kod *= 12; kod += month;
  kod *= 32; kod += day;
  }

void getprojects() {
  f = gzopen("projects.csv.gz", "rb");
  toeol();
  while(!gzeof(f)) {
    int repoid = readnum();
    bool inquote = false;
    while(true) {
      char c = gzgetc(f);
      if(c == ',' && !inquote) break;
      if(c == '\"') inquote = !inquote;
      }
    int userid = readnum();
    printf("%d %d\n", repoid, userid);
    toeol();
    }
  gzclose(f);
  }

#define NUMREPO 38000000
int owners[NUMREPO];

void readowners() {
  FILE *f = fopen("proj-to-user", "rb");
  while(!feof(f)) {
    int repo, user;
    fscanf(f, "%d%d", &repo, &user);
    owners[repo] = user;
    }
  };

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


void addEvent(event e) {
  if(e.date < ...)
    events.push_back(e);
  }

void readFollowers() {
  csvparser c("...");
  while(c.next()) {
    addEvent(event { nr1, nr2, typ, data });
    }
    
  f = gzopen("followers.csv.gz", "rb");
  while(!gzeof(f)) {
    event ev;
    ev.a = readnum(); // follower
    ev.b = readnum(); // followed
    ev.date = readdate();
    ev.type = 'f';
    if(ev.a <= ev.b) events.push_back(ev);
    ev.type = 'F'; swap(ev.a, ev.b);
    if(ev.a <= ev.b) events.push_back(ev);
    // toeol();
    if(testing()) break;
    }
  gzclose(f);
  }

void readWatchers() {
  f = gzopen("watchers.csv.gz", "rb");
  while(!gzeof(f)) {
    event ev;
    ev.a = owners[readnum()]; // owner of the repo
    ev.b = readnum(); // watcher
    ev.date = readdate();
    ev.type = 'w';
    if(ev.a <= ev.b) events.push_back(ev);
    ev.type = 'W'; swap(ev.a, ev.b);
    if(ev.a <= ev.b) events.push_back(ev);
    // toeol();
    if(testing()) break;
    }
  gzclose(f);
  }

void readMembers() {
  f = gzopen("project_members.csv.gz", "rb");
  while(!gzeof(f)) {
    event ev;
    ev.a = owners[readnum()]; // owner of the repo
    ev.b = readnum(); // member
    ev.date = readdate();
    ev.type = 'm';
    if(ev.a <= ev.b) events.push_back(ev);
    ev.type = 'M'; swap(ev.a, ev.b);
    if(ev.a <= ev.b) events.push_back(ev);
    toeol();
    if(testing()) break;
    }
  gzclose(f);
  }

void readIssues() {
  f = gzopen("issues.csv.gz", "rb");
  while(!gzeof(f)) {
    event ev;
    readstr();
    ev.a = owners[readnum()]; // owner of the repo
    ev.b = readnumOrNul(); // reporter
    if(ev.b == -1) { toeol(); continue; }
    readnumOrNul(); // assignee
    int pullreq = readnum();
    readnumOrNul();
    ev.date = readdate();
    ev.type = pullreq ? 'p' : 'i';
    if(ev.a <= ev.b) events.push_back(ev);
    ev.type = pullreq ? 'P' : 'I'; swap(ev.a, ev.b);
    if(ev.a <= ev.b) events.push_back(ev);
    toeol();
    if(testing()) break;
    }
  gzclose(f);
  }

int main() {
  fprintf(stderr, "reading owners\n");
  readowners();
  fprintf(stderr, "reading issues\n");
  readIssues();
  fprintf(stderr, "reading followers\n");
  readFollowers();
  fprintf(stderr, "reading watchers\n");
  readWatchers();
  fprintf(stderr, "reading members\n");
  readMembers();
  sort(events.begin(), events.end());
  int S = events.size();
  for(int i=0; i<S; i++) {
    event &e(events[i]);
    if(i == 0 || e.a != events[i-1].a || e.b != events[i-1].b) {
      printf("\n%8d %8d %c%c", e.a, e.b, e.a == e.b ? '*' : ' ', e.type);
      }
    else {
      if(e.date != events[i-1].date) printf(":");
      printf("%c", e.type);
      }
    }
  printf("\n");
  return 0;
  }
