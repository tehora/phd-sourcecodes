#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <ghutils.h>

using namespace std;

int main(int argc, char **argv) {
  char buf[64];
  
  putenv((char*) "TZ=UTC");
  
  searcher2 pull("pull");
  map<string, string> p0;

  ofstream wsp(argv[4]);

  {
  fixer kto_otworzyl_pr_ght("kto_otworzyl_pr_ght");
  {
  csvparser in1(argv[1], ';');
  while (in1.next()) {
      if(in1[4] == "opened") kto_otworzyl_pr_ght.add(tonum(in1[5]), in1[1]);
      }
  }

  csvparser in1(argv[1], ';');
  while (in1.next()) {
      if(in1[4] == "merged" || in1[4] == "closed") kto_otworzyl_pr_ght.fix(tonum(in1[5]), in1[1]);
      string z = in1[0]+";"+tolower(in1[1])+";"+tolower(in1[2])+";"+tolower(in1[3])+";"+tolower(in1[4]);
      /* if(pull.count(z)) {
        powtorki << z << ";" << in1[5] << "||" << p0[z] << "\n";
        powtorki.flush();
        } */
      pull.insert(z, tonum(in1[5]));
      wsp << z << ";t" << in1[5] << "\n";
  }
  }
  
  fixer kto_otworzyl_pr("kto_otworzyl_pr"); 
  
  {csvparser in3(argv[2], ';');
  while (in3.next()) {
      if(in3[9] == "opened")
        kto_otworzyl_pr.add(tonum(in3[10]), in3[1]);
  }}
  
  map<int, int> rekody;
  set<int> zgubione;
  int ile_zgubionych;
  
  {
  csvparser inzgub(argv[3], ';');
  while(inzgub.next()) {
    if(inzgub.fields == 2) 
      rekody[tonum(inzgub[0].substr(1))] = tonum(inzgub[1].substr(1));
    }
  }
  
  ofstream fzgubione(argv[3], ios_base::app);

  {
  csvparser in2(argv[2], ';');
  while (in2.next()){

      if(in2[9] == "closed" || in2[9] == "merged") 
        kto_otworzyl_pr.fix(tonum(in2[10]), in2[1]);

      time_t t = dajczas(in2[0]);
      string z = ";"+tolower(in2[1])+";"+tolower(in2[4])+";"+tolower(in2[5])+";"+tolower(in2[9]);
      int kod = pull.kod(t, z);

      int klucz = tonum(in2[10]);
      
      if(kod != -1) {
        if(zgubione.count(klucz)) {
          fzgubione << "g" << klucz << ";t" << kod << "\n";
          ile_zgubionych++;
          }
        rekody[klucz] = kod;
        }
      else {
        if(rekody.count(klucz))
          wsp << formatuj(t,0)+z << ";t" << rekody[klucz] << "\n";
        else {
          wsp << formatuj(t,0)+z << ";g" << klucz << "\n";
          zgubione.insert(klucz);
          }
  }
  }}

  printf("Dodano do zgubionych: %d\n", ile_zgubionych);
  return 0;
  }

