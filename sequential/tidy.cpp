#include <ghutils.h>
#include <set>

set <string> known;
  
int main(int argc, char **argv) {
    
    ofstream of(argv[2]);

    of <<"number;rule;conf;lift;conv;supp" <<"\n";

    csvparser in0(argv[1], ';');
    while (in0.next()) {
        string s = in0[0] + ";" + in0[2] + ";" + in0[4] + ";" + in0[5];
        if (known.count(s)==0) {
            known.insert(s);
            of << in0[0] << ";" << in0[1] <<";" << in0[2] << ";" << in0[3] << ";" << in0[4] << ";" + in0[5] <<"\n";
        }    
    }    
  
}    
