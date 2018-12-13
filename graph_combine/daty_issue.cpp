#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <ghutils.h>

using namespace std;

bool interesting(const string& s) {
  return s == "opened" || s == "closed" || s == "reopened";
  }

int main(int argc, char **argv) {
  char buf[64];
  
  putenv((char*) "TZ=UTC");
  
  searcher issues("searcher issues");

  fixer czyj_issue_ght("czyj_issue_ght");
  {
  csvparser in1(argv[1], ';');
  while (in1.next()) {
    if(in1[4] == "opened") czyj_issue_ght.add(tonum(in1[5]), in1[1]);
    }
  }

  fixerof<string, string> czyj_issue_gha("czyj_issue_gha");
  {
  csvparser in1(argv[2], ';');
  while (in1.next()) {
    if(in1[7] == "opened") czyj_issue_gha.add(in1[4] + "/" + in1[8], in1[1]);
    }
  }

  ofstream wsp(argv[3]);
  
  {
  csvparser in1(argv[1], ';');  
  while (in1.next()) {
      if(!interesting(in1[4])) continue;
      if(in1[4] == "closed") czyj_issue_ght.fix(tonum(in1[5]), in1[1]);
      string z = in1[0]+";"+tolower(in1[1])+";"+tolower(in1[2])+";"+tolower(in1[3])+";"+tolower(in1[4]);
      issues.insert(z); 
      wsp << z << ";" << in1[5] << "\n";
  }
  }

  {csvparser in2(argv[2], ';');
  while (in2.next()){
      if(!interesting(in2[7])) continue;
      if(in2[7] == "closed") czyj_issue_gha.fix(in2[4] + "/" + in2[8], in2[1]);
      time_t t = dajczas(in2[0]);
      string z = ";"+tolower(in2[1])+";"+tolower(in2[4])+";"+tolower(in2[5])+";"+tolower(in2[7]);
      if(issues.niema(t, z))
          wsp << formatuj(t,0)+z << ";" << in2[8] << "\n";
  }}

  return 0;
  }

