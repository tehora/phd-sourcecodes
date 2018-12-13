#include <ghutils.h>
#include <map>

map < pair <string, string>, int > user_repos;
map < string, int > user_watchers; 

void extract(const char* plik, int fala) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (fala) {
        case 1:    
            while (in1.next()) {
                if (in1.fields > 2) {
                    auto user_repo= make_pair(tolower(in1[6]), tolower(in1[4]));
                    if (user_repos[user_repo] <  tonum(in1[7])) {
                        user_repos[user_repo] = tonum(in1[7]);
                     }
                }     
            }
            break;
        case 2:
            while (in1.next()) {
                if  (in1.fields > 2) {
                    auto user_repo= make_pair(tolower(in1[0]), tolower(in1[5]));
                    if (user_repos[user_repo] <  tonum(in1[7])) {
                        user_repos[user_repo] = tonum(in1[7]);
                     }
                }     
            }
            break;
    }
}  

int main() {
    
    extract("crawl/source/repozytoria/repo2_0402.csv",1);
    extract("crawl/source/repozytoria/repo2_0601.csv",1);
    extract("crawl/source/repozytoria/repo2_0604.csv",1);
    extract("crawl/source/repozytoria/repo2_0904.csv",1);
    extract("crawl/source/repozytoria/repo2_1004.csv",1);
    extract("crawl/source/repozytoria/repo2_1604.csv",1);
    extract("crawl/source/repozytoria/repo2_2304.csv",1);
    extract("crawl/source/repozytoria/repo2_fala.csv",1);
    extract("crawl/source/repozytoria/repozytoria2404b.csv",1);
    extract("crawl/source/repozytoria/repozytoria2404a.csv",2);
    extract("crawl/source/repozytoria/repozytoria2404c.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_1409.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_1808.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_1809.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_1909.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2008.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2108.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2208.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2308.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2408.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_2608.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo2.csv",1);
    extract("crawl/source/repozytoria/pierwsza_fala/repo_amsterdam.csv",1);

    for (auto& user: user_repos) {
        user_watchers[user.first.first]+=user.second;
    }    
    
    ofstream of1("user_watchers.csv");
    
    of1 <<"user;watchers" << endl;
    
    for ( auto& user: user_watchers) {
        of1 << user.first << ";" << user.second << endl;
    }    
}    
