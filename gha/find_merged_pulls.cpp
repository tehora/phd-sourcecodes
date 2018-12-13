#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <ghutils.h>

using namespace std;

int main() {

  ofstream out("../../agregaty/gha/pullevent/pull_merge.csv");
  csvparser in1("../../agregaty/gha/pullevent/pull_graf2.csv", ';'); 

  while (in1.next()) {
      in1.progressbar();
      if (in1[15] != "") {
         out << in1[15] << ";" << 
         in1[1] <<";" << in1[2] <<";" <<in1[3] <<";" <<in1[4] <<";" 
         <<in1[5] <<";" << in1[6] << ";" << in1[7] <<";" <<in1[8] <<
         ";merged;" <<in1[10] <<";" << in1[11] <<";" <<in1[12] <<
         ";" <<in1[13] <<";" <<in1[14] <<";" <<in1[15] << endl;
      }
  }
  closeprogressbar();
  
  return 0;
}
