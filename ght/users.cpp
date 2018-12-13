#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map <int, string> users;

int main(int argc, char **argv) {

    // read the users logins and id from ght
    
    csvparser in1(argv[1], ',');
    ofstream of(argv[2]);
    while (in1.next()) {
        if(in1.fields < 2) printf("fields = %d\n", in1.fields);
        of << tolower(in1[1]) << ";" << in1[3] <<"\n";
    }
    
} 
