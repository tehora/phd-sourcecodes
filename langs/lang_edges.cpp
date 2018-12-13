#include <ghutils.h>
#include <map>
#include <vector>

map< string, vector <pair<string, int> > > userlangs;
map< pair <string, string>, double > edges;
map <string, int> freq;
map <string, int> freq2;

int main(int argc, char **argv) {

    {csvparser in1(argv[1], ';');

    while(in1.next()) {
        if (in1[1]!="") {
            int ile = tonum(in1[2]);
            if(in1[1] == "logos") continue;
            userlangs[in1[0]].push_back(make_pair(in1[1], ile));
            freq[in1[1]]++;
            freq2[in1[1]] += ile;
        }
    }}

    ofstream of("dziwni2");

    for (auto& user: userlangs) {
        double tsum=0, squaresum=0;
        for (auto& lang: user.second) {
          tsum += lang.second;
          squaresum += lang.second * 1.0 * lang.second;
          }
        if(tsum >= 10000) continue;
        tsum = tsum * tsum - squaresum;
        // if(user.first == "gitter-badger") continue;
        
        double lowd = 100;
        
        for (auto& lang: user.second) {
            for (auto& lang2: user.second) {
                if (&lang == &lang2 ) break;
                auto edge = make_pair(lang.first, lang2.first);
                double d = 1.0 * lang.second * lang2.second / tsum;
                edges[edge] += d;
                if(d < lowd) lowd = d;
                  
            }
        }

        if(lowd < 1e-6) {
          of << "CO TO ZA DZIAD ?! " << user.first << "\n";
          for (auto& langx: user.second) 
            of << langx.first << ";" << langx.second << "\n";
          of << "\n";
          }
    
    }

    cout <<"zwalniam user_langs" << "\n";
    userlangs.clear();

    cout <<"zapisuje do lang_edges.csv" << "\n";
    ofstream of1(argv[2]);

    of1 <<"lang;lang2;waga" << "\n";
    
    for(auto edge: edges ) {
        of1 << edge.first.first << ";" << edge.first.second <<";" <<edge.second  << "\n"; 
    }

    cout <<"zapisuje do lang_freq.csv" << "\n";
    ofstream of2(argv[3]);

    of2 <<"lang;freq" << "\n";
    
    for(auto lang: freq ) {
        of2 << lang.first << ";" << lang.second << freq2[lang.first] << "\n"; 
    }
    
}    
