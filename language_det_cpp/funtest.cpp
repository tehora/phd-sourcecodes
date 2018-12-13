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
    regex wzorzec("(\\benjoy|\\bpleas[aiu]|\\bfun\\b|\\bfunn|\\bentertain|\\bplaying|\\bplay\\b|\\bamus|\\binterest|\\brelax|experiment|fool(ing)? around|joke|\\bjoy|\\bexcit|\\brecreation|\\bprocrastinat|\\bplayful)", regex_constants::icase);

    while(true) {
        string s;
        getline(cin, s);
        smatch wynik;
        if(regex_search(s, wynik, wzorzec)) { 
           printf("ok\n");
           cout << string(wynik[0]) << std::endl;
}
        }
  return 0;
  }
