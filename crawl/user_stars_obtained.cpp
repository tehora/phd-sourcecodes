#include <ghutils.h>
#include <map>

map <pair<string, string>, int > repo_stars;
map <string, int> stars_obtained;

void extract(const char* plik, int fala) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (fala) {
        case 1:
            while (in1.next()) {
                if (in1.fields > 2) {
                    auto login = make_pair(tolower(in1[6]),tolower(in1[4]));
                    if (repo_stars[login]<tonum(in1[3])) {
                        repo_stars[login]=tonum(in1[3]);
                    }    
                }     
            }
            break;
        case 2:    
            while (in1.next()) {
                if (in1.fields > 2) {
                    auto login = make_pair(tolower(in1[6]),tolower(in1[4]));
                    if (repo_stars[login]<tonum(in1[12])) {
                        repo_stars[login]=tonum(in1[12]);
                    }    
                }     
            }
            break;
        case 3:
            while (in1.next()) {
                if (in1.fields > 2) {
                    auto login = make_pair(tolower(in1[0]),tolower(in1[5]));
                    if (repo_stars[login]<tonum(in1[12])) {
                        repo_stars[login]=tonum(in1[12]);
                    }    
                }     
            }
            break;
        case 4:
            while (in1.next()) {
                if (in1.fields > 2) {
                    auto login = make_pair(tolower(in1[4]),tolower(in1[3]));
                    if (repo_stars[login]<tonum(in1[2])) {
                        repo_stars[login]=tonum(in1[2]);
                    }    
                }     
            }
            break;
    }
}  

int main(int argc, char **argv) {
    extract("../../rawdata/crawl/repositories/repo2_0402.csv",2);
    extract("../../rawdata/crawl/repositories/repo2_0601.csv",2);
    extract("../../rawdata/crawl/repositories/repo2_0604.csv",2);
    extract("../../rawdata/crawl/repositories/repo2_0904.csv",2);
    extract("../../rawdata/crawl/repositories/repo2_1004.csv",1);
    extract("../../rawdata/crawl/repositories/repo2_1604.csv",1);
    extract("../../rawdata/crawl/repositories/repo2_2304.csv",1);
    extract("../../rawdata/crawl/repositories/repo2_fala.csv",2);
    extract("../../rawdata/crawl/repositories/repositories2404b.csv",2);
    extract("../../rawdata/crawl/repositories/repositories2404a.csv",3);
    extract("../../rawdata/crawl/repositories/repositories2404c.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_1409.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_1808.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_1809.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_1909.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2008.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2108.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2208.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2308.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2408.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_2608.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo2.csv",1);
    extract("../../rawdata/crawl/repositories/first_wave/repo_amsterdam.csv",1);
    extract("../../rawdata/crawl/repositories/repo3_0801.csv",4);

    for (auto repo_star: repo_stars) {
        stars_obtained[repo_star.first.first] += repo_star.second;
    }

    ofstream of1(argv[1]);
    
    of1 <<"user;stars_obtained" << endl;

    for (auto star_obtained: stars_obtained) {
        of1 << star_obtained.first << ";" << star_obtained.second << endl;
    }    
}    
