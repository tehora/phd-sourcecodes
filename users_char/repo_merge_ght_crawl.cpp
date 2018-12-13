#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <ghutils.h>

using namespace std;

int main(int argc, char **argv) {
    char buf[64];

    set <string> repo;

    csvparser in1(argv[1], ';');
    in1.next();
    
    ofstream wsp(argv[3]);
    wsp << "user;repo;lang;fork\n";
    
    while (in1.next()) {
        string z = tolower(in1[0])+";"+tolower(in1[1])+";"+in1[2]+";"+in1[3];
        repo.insert(z);
        wsp << z << "\n";
    }

    csvparser in2(argv[2], ';');
    
    while (in2.next()) {
        string z = in2[0]+";"+in2[1]+";"+in2[2]+";"+in2[3];
        if(!repo.count(z)) {
            wsp << z << "\n";
        }
    }

    return 0;
} 
