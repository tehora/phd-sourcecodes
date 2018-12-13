#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <ghutils.h>

typedef long double ld;

#define QROW 4000000
#define QPAR 41

string kolumny[QPAR] = {
  // 1..4
  "repos", "repos2", "followers", "followers2", 
  // 5..6
  "stars_obtained", "stars_obtained2",
  // 7..8
  "following", "following2",
  // 9..10
  "stars_given", "stars_given2",
  // 11.13
  "forking_others", "email", "site",
  // 14..19
  "year2009", "year2010", "year2011", "year2012", "year2013", "year2014",  
  // 20..34
  "javascript", "java", "ruby", "python", "php", "css", "html", "c++", "c","objectivec", "c#", "shell", "go", "r", "swift",
  // 35
  "langcount",
  // 36..39
  "comments_self", "comments_others", "issues_self", "issues_others", 
  // 40
  "intercept",
  };

int ind[QROW][QPAR];
ld sum[QROW];
int dep[QROW];
int alp[QROW];

ld gres[QPAR];

ld cres[QPAR];

ld rrand() {
  return rand() / (RAND_MAX + .1);
  }

ld rrandg() {
  return rrand() + rrand() - rrand() - rrand();
  }

ld logf(ld x) {
  return 1 / (1 + exp(-x));
  }

ld loglik() {
  ld ll = 0;
  for(int i=0; i<QROW; i++)
    ll -= log(1+exp(sum[i]*alp[i]));
  return ll;
  }

ld ptoz(ld z) {
  return (1 - erf(z / sqrt(2)));
  }

int qrow = 0;  

void cstats() {
  int *stats = new int[QROW];
  for(int i=0; i<QPAR; i++) {
    for(int k=0; k<qrow; k++) stats[k] = ind[k][i];
    sort(stats, stats+qrow);
    printf("00%%: %5d 50%%: %5d 75%%: %5d 90%%: %5d 99%%: %5d -> %s [%d]\n", 
      stats[0], stats[qrow/2], stats[qrow*3/4], stats[qrow*9/10], stats[qrow*99/100],
      kolumny[i].c_str(), i);
    }
  delete[] stats;
  }
  
int main(int argc, char ** argv) {
  srand(time(NULL));
  
  int ilezle = 0;
  
  bool cut = argc > 1;
  
  int ones = 0;

  {csvparser in(argv[1]);
  while(in.next()) {
    if(in.fields != 35) printf("zle fieldsy\n");
    if(qrow > QROW) { printf("za duzo rzedow!\n"); exit(1); }
    int * r0 = ind[qrow];
    int * r = ind[qrow]-1;
    dep[qrow] = tonum(in[6]);
    if(dep[qrow]) ones++;
    r[1] = tonum(in[5]); if(r[1] > 70 && cut) r[1] = 70;
    r[2] = r[1] * r[1];
    r[3] = tonum(in[7]); if(r[3] > 30 && cut) r[3] = 30;
    r[4] = r[3] * r[3];
    r[5] = tonum(in[8]); if(r[5] > 147 && cut) r[5] = 147;
    r[6] = r[5] * r[5];
    r[7] = tonum(in[9]); if(r[7] > 32 && cut) r[7] = 32;
    r[8] = r[7] * r[7];
    r[9] = tonum(in[10]); if(r[9] > 358 && cut) r[9] = 358;
    r[10] = r[9] * r[9];
    if(r0[0] > 70 || r0[2] > 30 || r0[4] > 147 || r0[6] > 32 || r0[8] > 358) {
      ilezle++;
      continue;
      }
    r[11] = tonum(in[11]);
    r[12] = tonum(in[12]);
    r[13] = tonum(in[13]);
    int yr = tonum(in[4]); for(int y=14; y<20; y++) r[y] = yr == (y - 14 + 2009);
    for(int y=20; y<35; y++) r[y] = tonum(in[18+y-20]);
    r[35] = tonum(in[34]);
    r[36] = tonum(in[14]);
    r[37] = tonum(in[15]);
    r[38] = tonum(in[16]);
    r[39] = tonum(in[17]);
    r[40] = 1;
    // for(int i=1; i<=36; i++) if(r[i] > 1000) r[i] = 1000;
    // if(r[10] < 0) printf("CO TO ZA DZIAD?! %s\n", in[1].c_str());
    qrow++;
    }}
  
  printf("dep");
  for(int x=0; x<QPAR; x++) printf(";%s", kolumny[x].c_str()); 
  printf("\n");
  
  for(int z=0; z<qrow; z++) {
    printf("%d", dep[z]);
    for(int i=0; i<QPAR; i++) printf(";%d", ind[z][i]);
    printf("\n");
    }
  
  return 0;
  }
