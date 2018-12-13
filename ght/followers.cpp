#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map <int, string> users;

int main(int argc, char **argv) {

    // read the users logins and id from ght
    
    csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) printf("fields = %d\n", in1.fields);
        int id = tonum(in1[0]);
        users[id] = in1[1]; 
    }
    
// first: source
// second: target
// created_at

    ofstream of(argv[3]);
    
    csvparser in2(argv[2], ',');
    while (in2.next()) {
        of << in2[2] << ";" << users[tonum(in2[0])] << ";" << users[tonum(in2[1])]  << endl;
    }
}   

