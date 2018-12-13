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

  ofstream wsp("pull_graf_laczny.csv");

  {
  fixer kto_otworzyl_pr_ght("kto_otworzyl_pr_ght");
  {
  csvparser in1("../../ght/pull_graf_ght.csv", ';');
  while (in1.next()) {
      if(in1[4] == "opened") kto_otworzyl_pr_ght.add(tonum(in1[5]), in1[1]);
      }
  }

  csvparser in1("../../ght/pull_graf_ght.csv", ';');
  while (in1.next()) {
      if(in1[4] == "merged" || in1[4] == "closed") kto_otworzyl_pr_ght.fix(tonum(in1[5]), in1[1]);
      string z = in1[0]+";"+tolower(in1[1])+";"+tolower(in1[2])+";"+tolower(in1[3])+";"+tolower(in1[4]);
      /* if(pull.count(z)) {
        powtorki << z << ";" << in1[5] << "||" << p0[z] << endl;
        powtorki.flush();
        } */
      pull.insert(z, tonum(in1[5]));
      wsp << z << ";t" << in1[5] << endl;
  }
  }
  
  fixer kto_otworzyl_pr("kto_otworzyl_pr"); 
  
  {csvparser in3("../pullevent/pull_graf.csv", ';');
  while (in3.next()) {
      if(in3[9] == "opened")
        kto_otworzyl_pr.add(tonum(in3[10]), in3[1]);
  }}
  
  map<int, int> rekody;
  set<int> zgubione;
  int ile_zgubionych;
  
  {
  csvparser inzgub("zgubione.txt", ';');
  while(inzgub.next()) {
    if(inzgub.fields == 2) 
      rekody[tonum(inzgub[0].substr(1))] = tonum(inzgub[1].substr(1));
    }
  }
  
  ofstream fzgubione("zgubione.txt", ios_base::app);

  {
  csvparser in2("../pullevent/pull_graf.csv", ';');
  while (in2.next()){

      if(in2[9] == "closed" || in2[9] == "merged") 
        kto_otworzyl_pr.fix(tonum(in2[10]), in2[1]);

      time_t t = dajczas(in2[0]);
      string z = ";"+tolower(in2[1])+";"+tolower(in2[4])+";"+tolower(in2[5])+";"+tolower(in2[9]);
      int kod = pull.kod(t, z);

      int klucz = tonum(in2[10]);
      
      if(kod != -1) {
        if(zgubione.count(klucz)) {
          fzgubione << "g" << klucz << ";t" << kod << endl;
          ile_zgubionych++;
          }
        rekody[klucz] = kod;
        }
      else {
        if(rekody.count(klucz))
          wsp << formatuj(t,0)+z << ";t" << rekody[klucz] << endl;
        else {
          wsp << formatuj(t,0)+z << ";g" << klucz << endl;
          zgubione.insert(klucz);
          }
  }
  }}

  printf("Dodano do zgubionych: %d\n", ile_zgubionych);
  return 0;
  }

