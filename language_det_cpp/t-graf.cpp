#include "ghutils.h"
#include <map>
#include <vector>

using namespace std;
map<string, int> ile;
set<string> stopwords;
std::vector<pair<int, string>> dosort;

#include <string>
#include <cstdio>

set<string> wazne;

map<string, double> krawedzie;

int main() {
  {
  csvparser s("stopwords", ';');
  while(s.next()) {
      string sw = s[0];
      stopwords.insert(sw);
      }
  }    

  {
  csvparser s("wazne2", ';');
  while(s.next()) {
      wazne.insert(s[1]);
      }
  }    
 
  {
  csvparser c("funfunfun", ';');
  while(c.next()) {
    string s = c[1];
    string t = "";
    set<string> ws;
    for(char c: s) {
      if(c >= 'a' && c <= 'z') t += c;
      else if(c >= 'A' && c <= 'Z') t += (c|32);
      else {
        if(t != "" && wazne.count(t)) { ws.insert(t); t = "";}
        }
      }
    if(t!="" && wazne.count(t)) ws.insert(t);
    if(ws.size() >= 2)
      for(const string& a: ws) for(const string& b: ws) {
        if(&a == &b) break;
        krawedzie[a+";"+b] += 2.0 / (ws.size() * (ws.size()-1));
        }
    }
  }
  
  for(auto p: krawedzie) if(p.second >= 1) printf("%s;%lf\n", p.first.c_str(), p.second);
  return 0;
  }
