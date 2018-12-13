#include <ghutils.h>
#include <map>

map <string, pair<int, int> > comments;

int main(int argc, char **argv) {
    
    csvparser in1(argv[1],';');
    
    while (in1.next()) {
            if (in1[1] == in1[3]) {
                ++comments[in1[1]].second;
            } else {
                ++comments[in1[1]].first;
            }    
    }        

    ofstream of1(argv[2]);
    
    of1 <<"user;comments_others;comments_self" << "\n";
    
    for ( auto& user: comments) {
        of1 << user.first << ";" << user.second.first <<";" <<user.second.second  << "\n";
    }
}
