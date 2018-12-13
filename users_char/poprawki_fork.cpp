#include <ghutils.h>
#include <map>

map <string, pair<int,int> > user_forks;
 

int main(int argc, char **argv) {
    
    csvparser in2(argv[1],';');
    
    while (in2.next()) {
        user_forks[tolower(in2[0])].first = tonum(in2[1]);
    }

    csvparser in3(argv[2], ';');
    while (in3.next()) {
        user_forks[tolower(in3[0])].second = tonum(in3[1]);
    }
    
    ofstream of1(argv[3]);
    
    of1 <<"user;forked;forked_pulls" << endl;
    
    for ( auto& user: user_forks) {
        if (user.second.first == 1 && user.second.second != 0) {
            of1 << user.first << ";" << user.second.first <<";" <<user.second.second << endl;
        }
    }    
}    
