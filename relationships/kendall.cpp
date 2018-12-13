#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef long double ld;

/*
ld data[65][4] = {

  {8175956234582,7170258,4374921,423464,},
{8175955811120,7593720,4798383,2,},
{8175955811124,7593716,4798379,6,},
{8175955811122,7593718,4798381,4,},
{8175955811128,7593712,4798375,10,},
{8175955811128,7593712,4798375,10,},
{8175955811124,7593716,4798379,6,},
{8175955811118,7593722,4798385,0,},
{8175955811124,7593716,4798379,6,},
{8175955811122,7593718,4798381,4,},
{8175955811124,7593716,4798379,6,},
{8175955811118,7593722,4798385,0,},
{8175955811128,7593712,4798375,10,},
{8175955811120,7593720,4798383,2,},
{8175955811118,7593722,4798385,0,},
{8175955811122,7593718,4798381,4,},
{8175955811120,7593720,4798383,2,},
{8175955811120,7593720,4798383,2,},
{8175955811122,7593718,4798381,4,},
{8175955811118,7593722,4798385,0,},
{8175955811118,7593722,4798385,0,},
{8175955811120,7593720,4798383,2,},
{8175955811124,7593716,4798379,6,},
{8175955811118,7593722,4798385,0,},
{8175955811120,7593720,4798383,2,},
{8175955811120,7593720,4798383,2,},
{8175955811122,7593718,4798381,4,},
{8175955811124,7593716,4798379,6,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811120,7593720,4798383,2,},
{8175955811122,7593718,4798381,4,},
{8175955811118,7593722,4798385,0,},
{8175955811122,7593718,4798381,4,},
{8175955811128,7593712,4798375,10,},
{8175955811128,7593712,4798375,10,},
{8175955811122,7593718,4798381,4,},
{8175955811120,7593720,4798383,2,},
{8175955811120,7593720,4798383,2,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811124,7593716,4798379,6,},
{8175955811124,7593716,4798379,6,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811120,7593720,4798383,2,},
{8175955811118,7593722,4798385,0,},
{8175955811122,7593718,4798381,4,},
{8175955811120,7593720,4798383,2,},
{8175955811124,7593716,4798379,6,},
{8175955811128,7593712,4798375,10,},
{8175955811120,7593720,4798383,2,},
{8175955811126,7593714,4798377,8,},
{8175955811126,7593714,4798377,8,},
{8175955811122,7593718,4798381,4,},
{8175955811118,7593722,4798385,0,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811122,7593718,4798381,4,},
{8175955811118,7593722,4798385,0,},
{8175955811122,7593718,4798381,4,},
{8175955811118,7593722,4798385,0,},
{8175955811118,7593722,4798385,0,},
*/

/*  {10,0,0,10},
  {0,10,10,0},
  {1,0,0,1},
  {0,1,1,0} 
  }; */

ld data3[2][9] = { {10,0,0,0,10,0,0,0,10}, {0,0,10,0,10,0,10,0,0},};

int doKendall(ld *tab, int q) {
  ld txy[8][8];
  int i = 0;
  for(int x=0; x<q; x++) for(int y=0; y<q; y++)
    txy[x][y] = tab[i++];

  for(int x=0; x<q; x++) for(int y=0; y<q; y++)
    printf("[%d,%d] %Lf\n", x,y, txy[x][y]);

  /* for(int x=0; x<q; x++) for(int y=0; y<q; y++)
    total += txy[x][y]; */
    
  // printf("total = %Lf\n", total);
  
  ld 
    total2 = 0,
    concordant2 = 0, 
    discordant2 = 0,
    equalx2 = 0,
    equaly2 = 0;
  
  ld groupx[8], groupy[8], n = 0;
  
  for(int i=0; i<q; i++) groupx[i] = groupy[i] = 0;

  for(int x1=0; x1<q; x1++) for(int y1=0; y1<q; y1++)
    groupx[x1] += txy[x1][y1],
    groupy[y1] += txy[x1][y1],
    n += txy[x1][y1];
  
  for(int x1=0; x1<q; x1++) for(int y1=0; y1<q; y1++)
  for(int x2=0; x2<q; x2++) for(int y2=0; y2<q; y2++) {
    ld qty1 = txy[x1][y1];
    ld qty2 = txy[x2][y2];
    ld qty = (x1==x2 && y1==y2) ? qty1*(qty1-1) : qty1*qty2;
    
    total2 += qty;

    if(x1<x2 && y1<y2)
      concordant2 += qty;

    if(x1>x2 && y1>y2)
      concordant2 += qty;

    if(x1<x2 && y1>y2)
      discordant2 += qty;

    if(x1>x2 && y1<y2)
      discordant2 += qty;
    
    if(x1 == x2)
      equalx2 += qty;
    
    if(y1 == y2)
      equaly2 += qty;
    
    }
  
  printf("n           = %Lf\n", n);
  printf("2total      = %Lf\n", total2);
  printf("2concordant = %Lf\n", concordant2);
  printf("2discordant = %Lf\n", discordant2);
  printf("2equalx     = %Lf\n", equalx2);
  printf("2equaly     = %Lf\n", equaly2);
  
  printf("\n");
  
  ld tau_a = (concordant2 - discordant2) / total2;
  ld tau_b = (concordant2 - discordant2) / sqrt((total2-equalx2) * (total2-equaly2));
  
  printf("tau_a = %Le\n", tau_a);
  printf("tau_b = %Le\n", tau_b);

  printf("\n");
  
  ld concordant = concordant2 / 2;
  ld discordant = discordant2 / 2;
  ld total      = total2 / 2;
  
  ld za = 3 * (concordant - discordant) / sqrt(n * (n-1) * (2*n+5) / 2);
  
  printf("z_a = %Lf\n", za);
  
  ld requalx = 0, requaly = 0;
  for(int i=0; i<q; i++) requalx += groupx[i] * (groupx[i]-1) / 2;
  for(int i=0; i<q; i++) requaly += groupy[i] * (groupy[i]-1) / 2;
  
  printf("requalx = %Lf\n", requalx);
  printf("requaly = %Lf\n", requaly);
  
  ld vt = 0, vu = 0;
  for(int i=0; i<q; i++) 
    vt += groupx[i] * (groupx[i]-1) * (2*groupx[i] - 5);
  for(int i=0; i<q; i++) 
    vu += groupy[i] * (groupy[i]-1) * (2*groupy[i] - 5);

  ld st = 0, su = 0;
  for(int i=0; i<q; i++) 
    st += groupx[i] * (groupx[i]-1) * (groupx[i]-2);
  for(int i=0; i<q; i++) 
    su += groupy[i] * (groupy[i]-1) * (groupy[i]-2);
  
  ld v0 = n * (n-1) * (2*n-5);
  ld v1 = equalx2 * equaly2 * 4 / total;
  ld v2 = st * su / (9 * n * (n-1) * (n-2));
  ld v  = (v0 - vt - vu) / 18 + v1 + v2;
  
  ld zb = (concordant - discordant) / sqrt(v);
  
  printf("vt = %Lf\n", vt);
  printf("vu = %Lf\n", vu);
  printf("st = %Lf\n", st);
  printf("su = %Lf\n", su);
  printf("v0 = %Lf\n", v0);
  printf("v1 = %Lf\n", v1);
  printf("v2 = %Lf\n", v2);
  printf("zb = %Lf\n", zb);  
  
  printf("summary %20.13Lf %20.12Lf %20.12Lf %20.12Lf\n",
    tau_a, tau_b, za, zb);
  }

int main() {
  for(int i=0; i<15; i++) {
    char fn1[100], fn2[100];
    scanf("%s%s", fn1, fn2);
    int graf1, graf2, NN, common;
    scanf("%d%d%d%d", &graf1, &graf2, &NN, &common);
    ld Nd = NN;
    ld data[4];
    data[0] = Nd * (Nd-1) - graf1 - graf2 + common;
    data[1] = graf1 - common;
    data[2] = graf2 - common;
    data[3] = common;
    // for(int i=0; i<4; i++) scanf("%Lf\n", data+i);
    printf("%s vs %s:\n", fn1, fn2);
    doKendall(data, 2);
    }
  // for(int i=0; i<65; i++) doKendall(data[i], 2);
  /*
  for(int i=0; i<2; i++) doKendall(data3[i], 3);
  
  printf("zb testing\n");
  int shuf1[30], shuf2[30];
  for(int i=0; i<30; i++) shuf1[i] = i%3;

  for(int i=0; i<10; i++) {
    for(int i=0; i<30; i++) shuf2[i] = shuf1[i];
    for(int i=0; i<30; i++) swap(shuf2[i], shuf2[rand() % (1+i)]);
    ld dat[9];
    for(int i=0; i<9; i++) dat[i] = 0;
    for(int i=0; i<30; i++) dat[shuf1[i]*3+shuf2[i]]++;
    doKendall(dat, 3);
    }*/
    
  return 0;
  }

