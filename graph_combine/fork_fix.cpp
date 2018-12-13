#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <ghutils.h>

using namespace std;

set <string> existing_forks;

int main() {
  char buf[64];

  csvparser in1("grafy_laczne/forking_graf_laczny_crawl.csv", ';');

  ofstream wsp("grafy_laczne/forking_graf_laczny_fixed.csv");

  while (in1.next()) {
      string z = in1[1]+";"+in1[2]+";"+in1[3];
      if (existing_forks.count(z)==0) {;
          wsp <<in1[0] <<";" <<z << "\n";
          existing_forks.insert(z);
      }     
  }
  
  return 0;
  }

