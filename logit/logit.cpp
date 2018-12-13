#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <ghutils.h>

typedef long double ld;

#define QROW 4000000
#define QPAR 36

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
  // 36
  "intercept"
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

  {csvparser in("../../agregaty/logit/tabela_pr.txt");
  while(in.next()) {
    if(in.fields != 31) printf("zle fieldsy\n");
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
    for(int y=20; y<35; y++) r[y] = tonum(in[14+y-20]);
    r[35] = tonum(in[30]);
    r[36] = 1;
    // for(int i=1; i<=36; i++) if(r[i] > 1000) r[i] = 1000;
    // if(r[10] < 0) printf("CO TO ZA DZIAD?! %s\n", in[1].c_str());
    qrow++;
    }}
  
  // cstats();

  for(int z=0; z<qrow; z++) {
    int u = rand() % (z+1);
    swap(dep[z], dep[u]);
    for(int i=0; i<QPAR; i++) swap(ind[z][i], ind[u][i]);
    }
    
  printf("qrow = %d zle = %d ones = %d\n", qrow, ilezle, ones);

  for(int j=0; j<QPAR; j++) cres[j] = 0;
  for(int i=0; i<qrow; i++) sum[i] = 0;

  for(int i=0; i<qrow; i++) alp[i] = dep[i] ? -1 : 1;

  printf("loglik = %Lf\n\n", loglik());
  
  for(int it=0; it<1000; it++) {
    
    int qrow2 = it<10 ? qrow/1000 : it<20 ? qrow/100 : it < 30 ? qrow / 10 : qrow;

    printf("ITERATION %d, qrow2 = %d\n", it, qrow2);

    for(int j=0; j<QPAR; j++) {
      ld lld = 0, lldd = 0;
      for(int i=0; i<qrow2; i++) {
        ld D = alp[i] * ind[i][j];
        ld T = alp[i] * sum[i];
        ld expT = exp(T);
        lld += D * expT / (1 + expT);
        lldd += D * D * expT / (1+expT) / (1+expT);
        if(isnan(lld)) {
          printf("NAN on %d (%d, %Lf)\n", i, ind[i][j], sum[i]);
          for(int j2=0; j2<QPAR; j2++) printf("%d;", ind[i][j2]); 
          printf("\n");
          exit(1);
          }
        }
      printf("lld = %20.10Lf ", lld);
      printf("lldd = %20.10Lf ", lldd);
      ld bonus = -lld/lldd;
      cres[j] += bonus;
      for(int i=0; i<qrow; i++) sum[i] += bonus * ind[i][j];    
      printf("cres[%d '%s'] = %40.30Lf\n", j, kolumny[j].c_str(), cres[j]); // loglik());
      }
    
    printf("loglik = %Lf\n\n", loglik());

    printf("logit"); for(int i=0; i<QPAR; i++) printf(";%Lf", cres[i]); 
    printf("\n");

    fflush(stdout);
    
    if(it == 9 || it == 19 || it == 29 || it == 49 || it == 99 || it == 199 || it == 499 || it == 999) {

    ld m1[QPAR][QPAR];
    for(int a=0; a<QPAR; a++) for(int b=0; b<QPAR; b++) {
      m1[a][b] = 0;
      for(int i=0; i<qrow2; i++) {
        ld Da = alp[i] * ind[i][a];
        ld Db = alp[i] * ind[i][b];
        ld T = alp[i] * sum[i];
        ld expT = exp(T);
        m1[a][b] += Da * Db * expT / (1+expT) / (1+expT);
        }
      }
    
    // printf("%10.4Lf", m1[a][b]); if(b==QPAR-1) printf("\n");
    //  } printf("\n");
    
    ld m2[QPAR][QPAR];
    for(int i=0; i<QPAR; i++)
    for(int j=0; j<QPAR; j++) m2[i][j] = i==j ? 1 : 0;
    
    for(int a=0; a<QPAR; a++) {
      ld z = m1[a][a];
      for(int b=0; b<QPAR; b++) m1[a][b] /= z, m2[a][b] /= z;
      for(int c=a+1; c<QPAR; c++) {
        ld z2 = m1[c][a];
        for(int b=0; b<QPAR; b++) m1[c][b] -= m1[a][b] * z2;
        for(int b=0; b<QPAR; b++) m2[c][b] -= m2[a][b] * z2;
        }
      }
    
    for(int a=QPAR-1; a>=0; a--) {
      for(int c=0; c<a; c++) {
        ld z2 = m1[c][a];
        for(int b=0; b<QPAR; b++) m1[c][b] -= m1[a][b] * z2;
        for(int b=0; b<QPAR; b++) m2[c][b] -= m2[a][b] * z2;
        }
      }
    
    if(0) { for(int a=0; a<QPAR; a++) for(int b=0; b<QPAR; b++) {
      printf("%10.4Lf", m1[a][b]); if(b==QPAR-1) printf("\n");
      } printf("\n"); }
  
    if(0) { for(int a=0; a<QPAR; a++) for(int b=0; b<QPAR; b++) {
      printf("%10.4Lf", m2[a][b]); if(b==QPAR-1) printf("\n");
      } printf("\n"); }
  
    ld errs[QPAR];
    for(int i=0; i<QPAR; i++) errs[i] = sqrt(m2[i][i]);
    
    for(int i=0; i<QPAR; i++) {
      printf("%3d) %-20s", i, kolumny[i].c_str());
      ld coef = cres[i], serr = errs[i];
      ld zval = coef/serr;
      printf("est=%40.30Lf", coef);
      printf(" err=%40.30Lf", serr);
      
      if(zval < 0) zval = -zval;
      ld pval = ptoz(zval);
      
      printf(" p-value=%20.17Lf", pval);
      
      printf(" [%s]\n", kolumny[i].c_str());
      }
    
    fflush(stdout);

    } }
  
  return 0;
  }
