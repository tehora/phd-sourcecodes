#include <ghutils.h>
#include <set>

map <int, array<int, 12>> degrees;

void count_degrees(const char* plik, int nr_out, int nr_in) {
    csvparser in0(plik, ';');

    while (in0.next()) {

        //source -- out degrees
        if (degrees.count(tonum(in0[0]))==0) {
            for (int i =0 ; i<12; i++) {
                degrees[tonum(in0[0])][i] = 0; 
            }
            degrees[tonum(in0[0])][nr_out]++;
        } else {
            degrees[tonum(in0[0])][nr_out]++;
        }

        //target -- in degrees
        if (degrees.count(tonum(in0[1]))==0) {
            for (int i =0 ; i<12; i++) {
                degrees[tonum(in0[1])][i] = 0; 
            }
            degrees[tonum(in0[1])][nr_in]++;
        } else {
            degrees[tonum(in0[1])][nr_in]++;
        }
    }
}    


int main(int argc, char **argv) {

    count_degrees("../../agregaty/qap/comments_un.csv", 0,1);
    count_degrees("../../agregaty/qap/issues_un.csv", 2,3);
    count_degrees("../../agregaty/qap/forking_un.csv", 4,5);
    count_degrees("../../agregaty/qap/pulls_un.csv", 6,7);
    count_degrees("../../agregaty/qap/starring_un.csv", 8,9);
    count_degrees("../../agregaty/qap/follow_un.csv", 10,11);
    
    ofstream of("../../agregaty/qap/graph_degrees.csv");

    of <<"comments_out;comments_in;issues_out;issues_in;forking_out;forking_in;pulls_out;pulls_in;starring_out;starring_in;follow_out;follow_in" <<"\n";
    
    for (auto& user: degrees) {
        of <<user.first;
        for (int i=0; i<12; i++) {
            of <<";" <<user.second[i];
        }
        of <<"\n";
    }    
}    
