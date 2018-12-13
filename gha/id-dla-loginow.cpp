#include "csv2.h"

map<string, set< int > > m;

int main() {
  string wiersz;
  FILE *bledy = fopen("bledy-w-nodes.txt", "wt");
  
  csvparser in1("nodes_gharchive.csv");
  while (in1.next()) {
    in1.progressbar(); 
    if(in1.linenumber < 2) continue;
    if(in1.fields != 4) continue;
    
    string login = in1.row[1];
    int id = atoi(in1.row[2].c_str());
    m[login].insert(id);

    if(login == "") fprintf(bledy, "%s\n", in1.getline().c_str()), fflush(bledy);
    }

  /* csvparser in2("nodes_wyniki.txt");
  while (getline(in2, wiersz)) {
    int pos = 0;
    while(wiersz[pos] != ';') pos++;
    string login = wiersz.substr(0, pos);
    for(char& c: login) c = tolower(c);
    int id = 0; pos++;
    for(; pos < wiersz.size(); pos++) 
      if(wiersz[pos] == ',') printf("%s:%d\n", login.c_str(), id), m[login].insert(id), id = 0;
      else id = 10 * id + wiersz[pos] - '0';
    printf("%s:%d\n", login.c_str(), id), m[login].insert(id);
    } */
  
  csvparser in3("/home/tehora/doktoratowe/id_eryx.csv", ',');
  while (in3.next()) {
    in3.progressbar();
    string& login = in3.row[3];
    int id = atoi(in3.row[0].c_str());
    m[login].insert(id);
    }
  
  closeprogressbar();
  
  int ile_jednozn = 0;
  int ile_brak = 0;
  int ile_niejednozn = 0;

  for(auto& S: m) {
    printf("%s;", S.first.c_str());
    int ile = 0;
    int ileid = 0;
    for(int i: S.second) { if(ile) printf(","); printf("%d", i); 
      if(i != 0) ileid++;
      ile++; }
    if(ileid == 0) ile_brak++;
    if(ileid == 1) ile_jednozn++;
    if(ileid >= 2) ile_niejednozn++;
    printf("\n");
    }
  
  fprintf(stderr, "brak: %d jz: %d njz: %d\n", ile_brak, ile_jednozn, ile_niejednozn);
  return 0;
  }
