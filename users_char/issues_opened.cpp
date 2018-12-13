#include <ghutils.h>
#include <map>

map <string, pair<int, int> > issues;

int main(int argc, char **argv) {
    
    csvparser in1(argv[1],';');
    
    while (in1.next()) {
        if (in1[4] == "opened") {
            if (in1[1] == in1[3]) {
                ++issues[in1[1]].second;
            } else {
                ++issues[in1[1]].first;
            }    
        }        
    }

    ofstream of1(argv[2]);
    
    of1 <<"user;issues_others;issues_self" << "\n";
    
    for ( auto& user: issues) {
        of1 << user.first << ";" << user.second.first <<";" <<user.second.second  << "\n";
    }
}
