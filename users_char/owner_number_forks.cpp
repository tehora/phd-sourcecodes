#include <ghutils.h>
#include <map>

map <pair<string, string>, int > user_forks;
map <string, int> forks;

void compare(const char* plik, int fala) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (fala) {
        case 1:    
            while (in1.next()) {
                if (in1.fields > 2) {
                    if (tonum(in1[1])==0) {
                        if (user_forks[make_pair(tolower(in1[6]), tolower(in1[4]))] < tonum(in1[9])) {
                            user_forks[make_pair(tolower(in1[6]), tolower(in1[4]))] = tonum(in1[9]);
                        }
                     }
                }     
            }
            break;
        case 2:
            while (in1.next()) {
                if (in1.fields > 2) {
                    if (tonum(in1[0]) == 0) {
                        if (user_forks[make_pair(tolower(in1[6]), tolower(in1[4]))] < tonum(in1[10])) {
                            user_forks[make_pair(tolower(in1[6]), tolower(in1[4]))] = tonum(in1[10]);
                       } 
                    }
                }    
            }
            break;
        case 3:
            while (in1.next()) {
                if  (in1.fields > 2) {
                    if (tonum(in1[1]) == 0) {
                       if (user_forks[make_pair(tolower(in1[0]), tolower(in1[5]))] < tonum(in1[10])) {
                            user_forks[make_pair(tolower(in1[0]), tolower(in1[5]))] = tonum(in1[10]);
                       } 
                     }
                }     
            }
            break;
         case 4:
            while (in1.next()) {
                if  (in1.fields > 2) {
                    if (tonum(in1[0]) == 0) {
                       if (user_forks[make_pair(tolower(in1[4]), tolower(in1[3]))] < tonum(in1[5])) {
                            user_forks[make_pair(tolower(in1[4]), tolower(in1[3]))] = tonum(in1[5]);
                       }
                     }
                }     
            }
            break;
         
    }
}  

int main(int argc, char **argv) {
    
    csvparser in2(argv[1],';');
    
    while (in2.next()) {
        string repo = "/" + tolower(in2[3]) + "/" + tolower(in2[2]);
        user_forks[make_pair(tolower(in2[3]), repo)]++;
    }

    compare("../../rawdata/crawl/repozytoria/repo2_0402.csv",2);
    compare("../../rawdata/crawl/repozytoria/repo2_0601.csv",2);
    compare("../../rawdata/crawl/repozytoria/repo2_0604.csv",2);
    compare("../../rawdata/crawl/repozytoria/repo2_0904.csv",2);
    compare("../../rawdata/crawl/repozytoria/repo2_1004.csv",1);
    compare("../../rawdata/crawl/repozytoria/repo2_1604.csv",1);
    compare("../../rawdata/crawl/repozytoria/repo2_2304.csv",1);
    compare("../../rawdata/crawl/repozytoria/repo2_fala.csv",2);
    compare("../../rawdata/crawl/repozytoria/repozytoria2404b.csv",2);
    compare("../../rawdata/crawl/repozytoria/repozytoria2404a.csv",3);
    compare("../../rawdata/crawl/repozytoria/repozytoria2404c.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_1409.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_1808.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_1809.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_1909.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2008.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2108.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2208.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2308.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2408.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_2608.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo2.csv",1);
    compare("../../rawdata/crawl/repozytoria/pierwsza_fala/repo_amsterdam.csv",1);
    compare("../../rawdata/crawl/repozytoria/repo3_0801.csv",4);

    for (auto& user_repo: user_forks) {
        forks[user_repo.first.first]+=user_repo.second;
    } 
    
    ofstream of1(argv[2]);
    
    of1 <<"user;number_forks" << "\n";
    
    for ( auto& user: forks) {
        of1 << user.first << ";" << user.second << endl;
    }    
}    
