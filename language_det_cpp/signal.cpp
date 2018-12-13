#include "ghutils.h"
#include <map>
#include <vector>

using namespace std;
map<string, int> ile;
set<string> stopwords;
std::vector<pair<int, string>> dosort;

#include <string>
#include <cstdio>

#include <regex> 

int main() {
  csvparser s("stopwords", ';');
  while(s.next()) {
      string sw = s[0];
      stopwords.insert(sw);
      } 
    regex wzorzec("(\\bwork\\b)|\\bportfolio|(\\bprofession)|(\\bcareer)|(\\bcurriculum)|(\\boccupation\\b)|(\\bjob\\b)|(\\bbusiness)|(\\bgig\\b)|\\bcv\\b|\\bteam\\b|\\benterprise\\b|\\bcompany\\b|\\corporation\\b", regex_constants::icase);

    ofstream of("singalling");
    csvparser c("dziadowskie_opisy", ';');
    while(c.next()) {
        string s = c[1];
        smatch wynik;
        if (regex_search(s, wynik, wzorzec)) {
            of <<c[0] <<";" <<c[1] <<";" <<c[2] <<"\n";
      }
      }

    /*while(true) {
        string s;
        getline(cin, s);
        smatch wynik;
        if(regex_search(s, wynik, wzorzec)) printf("ok\n");
        }*/
  return 0;
  }
