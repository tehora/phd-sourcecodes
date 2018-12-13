#include <ghutils.h>
#include <set>

set <string> base_repos;
set <string> forked_pulls_owners;

int main(int argc, char **argv) {

    csvparser in0(argv[1], ';');

    while (in0.next()) {
        if (in0[3] == "0") {
            string repo = in0[0]+"/"+in0[1];
            base_repos.insert(repo);
        }
    }

    csvparser in1(argv[2], ';');

    while (in1.next()) {
        string repo = in1[3]+"/"+in1[2];
        base_repos.insert(repo);
    }    
    
    csvparser in2(argv[3],';');
    
    while (in2.next()) {
        //if (base_repos.count(in2[2])!=0) {
        //        forked_pulls_owners.insert(in2[3]);
        //}
        forked_pulls_owners.insert(in2[3]);
    }

    ofstream of1(argv[4]);
    
    of1 <<"user;forked_with_pulls" << endl;
    
    for ( auto& user: forked_pulls_owners) {
        of1 << user << ";" << "1" << endl;
    }    
}    
