#include <ghutils.h>

ofstream of1;

void fix_lang(string lang, string fork) {
    if (lang == "1" || lang == "0") {
        of1 << fork << ";" << lang << endl;
    } else {
        of1 << lang << ";" << fork << endl;
    }
}

//owner, onwer/name, lang, fork

void extract(const char* plik, int fala) {
    csvparser in1(plik, ',');
    in1.escquote = true;
    switch (fala) {
        case 1:
            in1.next();
            while (in1.next()) {
                if (in1.fields > 2) {
                    of1 << tolower(in1[6]) << ";" << tolower(in1[4]) << ";" << in1[0] << ";" << in1[1] << endl;
                    //fix_lang(in1[0], in1[1]);
                }    
            }
            break;
        case 2:
            in1.next();
            while (in1.next()) {
                if (in1.fields > 2) {
                    of1 << tolower(in1[6]) << ";" << tolower(in1[4]) << ";"  << in1[1] << ";" << in1[0] << endl;
                    //fix_lang(in1[1], in1[0]);
                }     
            }
            break;
        case 3:
            in1.next();
            while (in1.next()) {
                if  (in1.fields > 2) {
                    of1 << tolower(in1[0]) << ";" << tolower(in1[5]) << ";"  << in1[2] << ";" << in1[1] << endl;
                    //fix_lang(in1[2], in1[1]);
                }     
            }
            break;
        case 4:
             in1.next();
             while (in1.next()) {
                if  (in1.fields > 2) {
                    of1 << tolower(in1[4]) << ";" << tolower(in1[3]) << ";"  << in1[1] << ";" << in1[0] << endl;
                    //fix_lang(in1[2], in1[1]);
                }     
            }
    }
}  

int main(int argc, char **argv) {
    of1.open(argv[1]);
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
}

