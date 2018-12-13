#include <ghutils.h>
#include <map>

map <string, pair<int,int> > user_issues;
 
int main(int argc, char **argv) {
    
    csvparser in2(argv[1],';');
    
    while (in2.next()) {
        user_issues[tolower(in2[0])].first = tonum(in2[1]);
    }

    csvparser in3(argv[2], ';');
    while (in3.next()) {
        user_issues[tolower(in3[0])].second = tonum(in3[2]);
    }
    
    ofstream of1(argv[3]);
    
    of1 <<"user;repos;issues_others" << endl;
    
    for ( auto& user: user_issues) {
        if (user.second.first == 0 && user.second.second != 0) {
            of1 << user.first << ";" << user.second.first <<";" <<user.second.second << endl;
        }
    }    
}    
