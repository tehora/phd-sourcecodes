#include "ghutils.h"
#include <map>
#include <vector>

using namespace std;
map<string, int> ile;

std::vector<pair<int, string>> dosort;

map<string, array<string, 20>> samples;

#include <string>
#include <cstdio>
#include "cld2/public/compact_lang_det.h"

pair<string, double> detect(string s) {
  using namespace CLD2;
  bool reliable;
  int valid_prefix_bytes;

  Language language3[3];
  int percent3[3];
  double normalized_score3[3];
  int text_bytes;
  
  int flags = 
    kCLDFlagQuiet | kCLDFlagBestEffort;
    
  ExtDetectLanguageSummaryCheckUTF8(
    s.c_str(),
    s.length(),
    true,
    NULL,
    flags,
    language3,
    percent3,
    normalized_score3,
    NULL,
    &text_bytes,
    &reliable,
    &valid_prefix_bytes
    );
  
  if(!reliable || normalized_score3[0] == 0) return make_pair("UNKNOWN", 0);
  
  return make_pair((string) LanguageName(language3[0]), normalized_score3[0]);
  }

ofstream of("rozpoznane.csv");

int main() {
  csvparser c("/mnt/agregaty/language_det/unk/user_unknown", ';');
  while(c.next()) {
    string s = c[1];
    auto p = detect(s);
    of << c[0] <<";" <<c[1] <<";" <<p.first <<"\n";
    /*int& i = ile[p.first];
    string s1 = s + " (" + to_string(p.second) + ")";
    if(i<20) 
      samples[p.first][i] = s1;
    else {
      int j = rand() % (i+1);
      if(j < 20) samples[p.first][j] = s1;
      }
      i++;*/
    }
  /*for(auto& p: ile) {
    printf("%s: %d\n", p.first.c_str(), p.second);
    for(int i=0; i<20; i++) if(samples[p.first][i] != "") 
      printf("  %s\n", samples[p.first][i].c_str());
      }*/
  return 0;
  }
