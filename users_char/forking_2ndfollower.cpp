#inc
lude <ghutils.h>
#include <map>

map <string, set<string> > following;
map <string, bool> obcy_fork;

int main(int argc, char **argv) {
    
    csvparser in1(argv[1],';');
    
    while (in1.next()) {
        following[in1[2]].insert(in1[1]);
    }

    csvparser in2(argv[2],';');
    
    while (in2.next()) {
        if (following[in2[3]].count(in2[1])==0) {
            for (string follower: following[in2[3]]) {
                if (following[follower].count(in2[1])>0) {
                    obcy_fork[in2[3]]=1;
                }
            }        
        }    
    }
    
    ofstream of1(argv[3]);
    
    of1 <<"user;obcy_fork" << "\n";
    
    for ( auto& user: obcy_fork) {
        of1 << user.first << ";" << user.second << "\n";
    }
}
