#include <ghutils.h>
#include <map>

map <string, int > forked;

void compare(const char* plik, int fala) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (fala) {
        case 1:    
            while (in1.next()) {
                if (in1.fields > 2) {
                    if (tonum(in1[1])==0 && tonum(in1[9]) > 0) {
                        forked[tolower(in1[6])] = 1;
                     }
                }     
            }
            break;
        case 2:
            while (in1.next()) {
                if (in1.fields > 2) {
                    if (tonum(in1[0]) == 0 && tonum(in1[10]) > 0) {
                            forked[tolower(in1[6])] = 1;
                     }
                }    
            }
            break;
        case 3:
            while (in1.next()) {
                if  (in1.fields > 2) {
                    if (tonum(in1[1]) == 0 && tonum(in1[10]) > 0 ) {
                        forked[tolower(in1[0])] = 1;
                     }
                }     
            }
            break;
         case 4:
            while (in1.next()) {
                if  (in1.fields > 2) {
                    if (tonum(in1[0]) == 0 && tonum(in1[5]) > 0 ) {
                        forked[tolower(in1[4])] = 1;
                     }
                }     
            }
            break;
         
    }
}  

int main(int argc, char **argv) {
    
    csvparser in2(argv[1],';');
    
    while (in2.next()) {
        forked[tolower(in2[3])] = 1;
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
    
    ofstream of1(argv[2]);
    
    of1 <<"user;forked" << endl;
    
    for ( auto& user: forked) {
        of1 << user.first << ";" << user.second << "\n";
    }    
}    
