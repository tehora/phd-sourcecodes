#include <ghutils.h>
#include <unordered_map>

unordered_map<int, string> users;

int main(int argc, char **argv) {

    // read the users logins and id from ght
    
    {csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) {
            printf("fields = %d\n", in1.fields);
            continue;
        }
        int id = tonum(in1[0]);
        users[id] = in1[1];
    }}

    csvparser in2(argv[2], ',');

    ofstream of1(argv[3]);
    of1 << "user;repo;lang;fork" << endl;
    while (in2.next()) {      
        of1 << users[tonum(in2[2])] << ";" << in2[3] << ";";
	if (in2[5] != "\\N") {
            of1  << in2[5];
	}
        if (in2[7] == "\\N") {  
            of1 << ";0" << endl;
        } else {
            of1 << ";1" << endl;
        }    
    }
}    
