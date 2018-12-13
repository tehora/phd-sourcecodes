#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map <int, string> users;

int main(int argc, char **argv) {

    // read the users and id from ght
    
    csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) printf("fields = %d\n", in1.fields);
        int id = tonum(in1[0]);
        users[id] = in1[1]; 
    }
    // ofstream of(argv[3]);
    //projects
    csvparser in2(argv[2], ','); 
    while (in2.next()) {
        if(in2.fields < 2) printf("fields = %d\n", in2.fields);
        cout << users[tonum(in2[2])] <<";" <<in2[4] <<'\n';
    }
}   
