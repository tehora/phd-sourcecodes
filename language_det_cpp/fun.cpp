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
    regex wzorzec("(\\benjoy|\\bpleas[aiu]|\\bfun\\b)|(\\bfunn)|(\\bentertain)|(\\bplaying)|(\\bplay\\b)|(\\bamus)|(\\binterest)|(\\brelax)|(experiment)|(fool(ing)? around)|(joke)|(\\bjoy)|(\\bexcit)|(\\brecreation)|(\\bprocrastinat)|(\\bplayful)", regex_constants::icase);

    ofstream of("funfunfun");
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
