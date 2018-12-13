#include <ghutils.h>
#include <set>

map <int, array<int, 2>> degrees;

void count_degrees(const char* plik, int nr_out, int nr_in) {
    csvparser in0(plik, ';');

    while (in0.next()) {

        //source -- out degrees
        if (degrees.count(tonum(in0[0]))==0) {
            for (int i =0 ; i<2; i++) {
                degrees[tonum(in0[0])][i] = 0; 
            }
            degrees[tonum(in0[0])][nr_out]++;
        } else {
            degrees[tonum(in0[0])][nr_out]++;
        }

        //target -- in degrees
        if (degrees.count(tonum(in0[1]))==0) {
            for (int i =0 ; i<2; i++) {
                degrees[tonum(in0[1])][i] = 0; 
            }
            degrees[tonum(in0[1])][nr_in]++;
        } else {
            degrees[tonum(in0[1])][nr_in]++;
        }
    }
}    


int main(int argc, char **argv) {

    count_degrees("../../agregaty/qap/starring_un.csv", 0,1); 

    ofstream of("../../agregaty/qap/star_degrees.csv");

    of <<"V1;V2;starring_out.x;starring_in.x;starring_out.y;starring_in.y" <<"\n";

    csvparser in0("../../agregaty/qap/starring_un.csv", ';');

    while (in0.next()) {
        if (tonum(in0[0]) != tonum(in0[1])) {
            of <<in0[0] <<";" <<in0[1] <<";" <<degrees[tonum(in0[0])][0] <<";" <<degrees[tonum(in0[0])][1] <<";" <<degrees[tonum(in0[1])][0] <<";" <<degrees[tonum(in0[1])][1] <<"\n";
        }    
    }    
}    
