#include <ghutils.h>

//std::array<int, 2740> number_all;
//std::array<int, 2740> number_forks;

map <int, pair<int,int>> date_number;

int main(int argc, char** argv) {
    csvparser in1(argv[1], ';');
    
    while (in1.next()) {
        string s = in1[1] + "T00:00:00";
        date_number[dajczas(s)].first++;
        if (tonum(in1[2])==1) {
            date_number[dajczas(s)].second++;
        }    
    }
    
    ofstream of1(argv[2]);

    of1 <<"data;created_repositories;created_forks" <<"\n";
    for (auto& date: date_number) {
        of1 <<formatuj((date.first),0) <<";" <<date.second.first <<";" <<date.second.second <<"\n"; 
    }    
    
}    
