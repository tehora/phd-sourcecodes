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
  
  searcher comments("searcher comments");

  ofstream wsp(argv[3]);
  
  {
  csvparser in1(argv[1], ';');  
  while (in1.next()) {
      string z = in1[0]+";"+tolower(in1[1])+";"+tolower(in1[2])+";"+tolower(in1[3]);
      comments.insert(z); 
      wsp << z << ";" << in1[4] << "\n";
  }
  }

  {csvparser in2(argv[2], ';');
  while (in2.next()){
      time_t t = dajczas(in2[0]);
      string z = ";"+tolower(in2[1])+";"+tolower(in2[4])+";"+tolower(in2[5]);
      if(comments.niema(t, z))
          wsp << formatuj(t,0)+z << ";" << in2[8] << "\n";
  }}

  return 0;
  }

