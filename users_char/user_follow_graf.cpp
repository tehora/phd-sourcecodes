#include <ghutils.h>

map <string, pair<int, int> > users;

//first is following, second if followers

int main(int argc, char **argv) {
    csvparser in1(argv[1], ';');

    while (in1.next()) {
        users[in1[1]].first++;
        users[in1[2]].second++;
    }    

    ofstream of1(argv[3]);

    of1 <<"user;following;followers" << endl;

    csvparser in2(argv[2], ';');

    while (in2.next()) {
        if (users[in2[0]].first < tonum(in2[1])) {
            users[in2[0]].first = tonum(in2[1]);
        }   
        if (users[in2[0]].second < tonum(in2[2])) {
            users[in2[0]].second = tonum(in2[2]);
        } 
        
    } 
    
    for (auto user: users) {
        of1 << user.first <<";" <<user.second.first << ";" <<user.second.second << endl;
    }    
}    
