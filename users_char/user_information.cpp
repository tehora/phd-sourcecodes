#include <ghutils.h>

map <string, pair< int, int >> users;

void extract(const char* plik, int typ) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (typ) {
        case 1:
            while (in1.next()) {
                if (in1[5]!="") {
                    users[tolower(in1[2])].first=1;
                }
                if (in1[9]!="") {
                    users[tolower(in1[2])].second=1;
                }
            }    
            break;
        case 2:    
            while (in1.next()) {
                if (in1[4]!="") {
                    users[tolower(in1[1])].first=1;
                }
                if (in1[8]!="") {
                    users[tolower(in1[1])].second=1;
                }
            }    
            break;
        case 3:
            while (in1.next()) {
                if (in1[4]!="") {
                    users[tolower(in1[0])].first=1;
                }
                if (in1[8]!="") {
                    users[tolower(in1[0])].second=1;
                }
            }
            break;
        case 4:
            while (in1.next()) {
                if (in1[3]!="") {
                    users[tolower(in1[0])].first=1;
                }
                if (in1[7]!="") {
                    users[tolower(in1[0])].second=1;
                }
            }    
            break;
    }
}  

int main(int argc, char **argv) {
    extract("../../rawdata/crawl/users/github_1009.csv",1);
    extract("../../rawdata/crawl/users/github_1309.csv",1);
    extract("../../rawdata/crawl/users/github2_1403.csv",1);
    extract("../../rawdata/crawl/users/github2_2706.csv",1);
    extract("../../rawdata/crawl/users/github_all.csv",2);
    extract("../../rawdata/crawl/users/github2_0302.csv",2);
    extract("../../rawdata/crawl/users/github2_0603.csv",2);
    extract("../../rawdata/crawl/users/github2_2002.csv",2);
    extract("../../rawdata/crawl/users/github2_2807.csv",1);
    extract("../../rawdata/crawl/users/polaczone0904.csv",3);
    extract("../../rawdata/crawl/users/github_ujednoliceni.csv",4);

    ofstream of1(argv[1]);

    of1 <<"user;site;email" << endl;
    
    for (auto user: users) {
        of1 << user.first <<";" <<user.second.first << ";" << user.second.second <<  endl;
    }    
}    
