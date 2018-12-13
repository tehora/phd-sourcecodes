#include <ghutils.h>

int main(int argc, char **argv) {

    csvparser in2(argv[1], ',');

    ofstream of1(argv[2]);
    of1 << "repo;date;fork" << endl;
    while (in2.next()) {      
        of1 << in2[3] << ";" << in2[6];
        if (in2[7] == "\\N") {  
            of1 << ";0" << "\n";
        } else {
            of1 << ";1" << "\n";
        }    
    }
}    
