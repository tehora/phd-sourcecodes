#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map <string, string> users;

int main(int argc, char **argv) {

    // read the users and countries from ght
    
    csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) printf("fields = %d\n", in1.fields);
        string login = in1[1];
        users[login] = in1[9]; 
    }

    ofstream of(argv[2]);
    
    for (auto user: users) {
        of << user.first << ";" << user.second  << '\n';
    }
}   
