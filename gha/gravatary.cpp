#include <fstream>
#include <iostream>

using namespace std;

#include <map>
#include <set>
#include <algorithm>

#include "csv2.h"

map<string, pair<set<int>, set< string > > > m;

int main() {

  FILE *bledy = fopen("bledy-w-nodes2.txt", "wt");
  
  csvparser in1("nodes_gharchive.csv");
  while (in1.next()) {
    in1.progressbar(); 
    if(in1.linenumber < 2) continue;
    
    string login = in1.row[1];
    string gravatar = in1.row[3];
    int id = atoi(in1.row[2].c_str());

    if(login == "") fprintf(bledy, "%s\n", in1.getline().c_str()), fflush(bledy);
    if(gravatar == "") continue;

    if(login != "") m[gravatar].second.insert(login);
    if(id != 0) m[gravatar].first.insert(id);
    }
  closeprogressbar(); 

  fclose(bledy);

  int zle_gravatary = 0;
  
  FILE *f = fopen("loginy_wg_gravatarow.txt", "wt");

  FILE *g = fopen("grupy_na_gravatarze.txt", "wt");

  for(auto& S: m) {
    printf("%s;", S.first.c_str());

    int ileid = 0, ilelog = 0;
    int jakiid;
    
    int ile = 0;
    for(int i: S.second.first) { if(ile) printf(","); printf("%d", i); ile++; ileid++; jakiid = i; }
    
    printf(";");
    ile = 0;
    for(string i: S.second.second) { if(ile) printf(","); printf("%s", i.c_str()); ile++; ilelog++; }
    
    printf("\n");
    if(ileid > 1) zle_gravatary++;
    
    if(ileid == 1) for(string s: S.second.second)
      fprintf(f, "%s;%d\n", s.c_str(), jakiid);
    
    if(ileid >= 4 && ile >= 4)
      fprintf(g, "%s;%d;%d\n", S.first.c_str(), ileid, ile);
    }
  
  fprintf(stderr, "zle gravatary: %d\n", zle_gravatary);
  fclose(f);
  fclose(g);
  return 0;
  }
