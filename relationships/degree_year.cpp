#include <ghutils.h>
#include <set>

map <int, array<int, 18>> degrees;

void count_degrees(const char* plik) {
    csvparser in0(plik, ';');

    while (in0.next()) {
        if (tonum(in0[0]) < 2008) continue; 
            //source -- out degrees 
            if (degrees.count(tonum(in0[1]))==0) {
                for (int i = 0; i<18; i++) {
                    degrees[tonum(in0[1])][i] = 0; 
                }
                int starting = (tonum(in0[0]) - 2008)*2;
                for (int s = starting; s < 18; s+=2) {
                    degrees[tonum(in0[1])][s]++;
                }    
            } else {
                int starting = 1+ (tonum(in0[0]) - 2008)*2;
                for (int s = starting; s < 18; s+=2) {
                    degrees[tonum(in0[1])][s]++;
                }
            }

            //target -- in degrees
            if (degrees.count(tonum(in0[2]))==0) {
                for (int i =0 ; i<18; i++) {
                    degrees[tonum(in0[2])][i] = 0; 
                }
                int starting = (tonum(in0[0]) - 2008)*2;
                for (int s = starting; s < 18; s+=2) {       
                    degrees[tonum(in0[2])][s]++;
                }     
            } else {
                int starting = 1+ (tonum(in0[0]) - 2008)*2;
                for (int s = starting; s < 18; s+=2) {
                    degrees[tonum(in0[2])][s]++;
                }     
            }
        }    
}    


int main(int argc, char **argv) {

    //count_degrees("../../agregaty/qap/comments_un.csv");
    count_degrees("../../agregaty/qap/is_years_un.csv");
    //count_degrees("../../agregaty/qap/forking_un.csv");
    //count_degrees("../../agregaty/qap/pul_years_un.csv");
    //count_degrees("../../agregaty/qap/starring_un.csv");
    //count_degrees("../../agregaty/qap/follow_un.csv");
    
    ofstream of("../../agregaty/qap/issues_degrees_years.csv");

    of <<"id;2008_out;2008_in;2009_out;2009_in;2010_out;2010_in;2011_out;2011_in;2012_out;2012_in;2013_out;2013_in;2014_out;2014_in;2015_out;2015_in;2016_out;2016_in" <<"\n";
    
    for (auto& user: degrees) {
        of <<user.first;
        for (int i=0; i<18; i++) {
            of <<";" <<user.second[i];
        }
        of <<"\n";
    }    
}    
