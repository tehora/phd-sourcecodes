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
  
  set<string> fork;

  csvparser in1(argv[1], ';');

  ofstream wsp(argv[3]);

  while (in1.next()) {
      string z = tolower(in1[1])+";"+tolower(in1[2])+";"+tolower(in1[3]);
      fork.insert(z);
      wsp <<in1[0] <<";" << z << "\n";
  }
  
  int jest=0, nima=0;
  csvparser in2(argv[2], ';');
  while (in2.next()){
      string z = tolower(in2[0])+";"+tolower(in2[1])+";"+tolower(in2[2]);
      if(fork.count(z)==0)
          wsp << ";" <<z <<"\n", nima++;

      else jest++;
  }

  printf("nowe obserwacje %d, powtorzone %d, obserwacje ght %d\n", nima, jest, (int) fork.size());
  
  return 0;
  }

