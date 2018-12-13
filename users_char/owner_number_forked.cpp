#include <ghutils.h>
#include <map>

map<string, int> repos;

int main(int argc, char **argv) {

    {csvparser in1(argv[1], ';');

    while(in1.next()) {
        if (tonum(in1[3])==1) {
            if (!repos.count(in1[0])) {
                repos[in1[0]] = 1;
            } else {
                repos[in1[0]]++;
            }
        }    
    }}

    {csvparser in2(argv[2], ',');

    while(in2.next()) {
        if (repos.count(in2[1])==0) {
            repos[in2[1]] = 0;
        }
    }}    

    ofstream of1(argv[3]);

    of1 <<"user;forked_repos" << "\n";
    
    for(auto repo: repos) {
        of1 << repo.first << ";" << repo.second << "\n"; 
    }    
}    
