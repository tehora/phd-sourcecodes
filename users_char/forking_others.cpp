#include <ghutils.h>
#include <map>

map <string, int > forking;

int main(int argc, char **argv) {
    
    csvparser in1(argv[1],';');
    
    while (in1.next()) {
        forking[tolower(in1[1])] = 1;
    }

    csvparser in2(argv[2], ';');
    while (in2.next()) {
        if (tonum(in2[3])==1) {
            forking[in2[0]] = 1;
        }
    }
    
    ofstream of1(argv[3]);
    
    of1 <<"user;forking_others" << endl;
    
    for ( auto& user: forking) {
        of1 << user.first << ";" << user.second << endl;
    }
}
