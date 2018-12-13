#include <ghutils.h>

std::array<int, 11793040> id_daty;
std::array<int, 2740> number_users;

int main(int argc, char** argv) {
    csvparser in1(argv[1], ';');

    id_daty.fill(0);
    
    while (in1.next()) {
        if (in1[3]!="NA") {
            string s = in1[3] + "T00:00:00";
            id_daty[tonum(in1[0])-1]=dajczas(s);
        } else {
            if (in1[2] != "NA") {
                string s = in1[2] + "T00:00:00";
                id_daty[tonum(in1[0])-1]=dajczas(s);
            }    
        }    
    }

    int ostatnia_poprawna = 0;
    for (int& x: id_daty) { 
        if (x==0) {
            x = ostatnia_poprawna;
        } else {
            ostatnia_poprawna = x;
        }          
    }
    
    int starting = dajczas("2007-10-20T00:00:00");
    
    for (int& data: id_daty) {
        number_users[(data-starting)/86400]++;
    }    

    ofstream of1(argv[2]);

    of1 <<"data;registered_users" <<"\n";
    for (int i=0; i<2740; ++i) {
        of1 <<formatuj((starting+i*86400),0) <<";" <<number_users[i] <<"\n"; 
    }    
    
}    
