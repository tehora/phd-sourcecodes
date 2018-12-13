#include "ghutils.h"
#include <map>
#include <vector>

using namespace std;
map<string, int> ile;
set<string> stopwords;
std::vector<pair<int, string>> dosort;

#include <string>
#include <cstdio>

int main() {
  csvparser s("stopwords", ';');
  while(s.next()) {
      string sw = s[0];
      stopwords.insert(sw);
  }    
 
  csvparser c("dziadowskie_opisy", ';');
  while(c.next()) {
    string s = c[1];
    string t = "";
    for(char c: s) {
      if(c >= 'a' && c <= 'z') t += c;
      else if(c >= 'A' && c <= 'Z') t += (c|32);
      else {
        if(t != "") {ile[t]++; t = "";}
        }
      }
    if(t!="") ile[t]++;    
    }
  for(auto& p: ile) dosort.emplace_back(-p.second, p.first);
  sort(dosort.begin(), dosort.end());
  for(auto& v: dosort) { if (!stopwords.count(v.second)) {printf("%d;%s\n", -v.first, v.second.c_str());}};
  return 0;
  }
