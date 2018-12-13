#include <ghutils.h>
#include <unordered_map>
#include <bitset>

unordered_map <int, int> common_in;
unordered_map <int, int> common_out;

// "comments_out;comments_in;issues_out;issues_in;forking_out;forking_in;pulls_out;pulls_in;starring_out;starring_in;follow_out;follow_in";
  
int main(int argc, char **argv) {

    //degree centrality
    //array <int, 12> values_5 = {5,11,4,7,7,16,5,7,17,67,15,16};
    //array <int, 12> values_1 = {39,31,25,21,55,47,24,19,207,288,53,53};
    //array <int, 12> values_10 = {2,6,2,4,3,9,3,4,5,27,8,8};

    //hubs & authorities
    array <int, 12> values_5 = {172836,490,45,8040182,3259,30539,143,201,11536,170,64,94098};
    array <int, 12> values_1 = {438251,7588,146,8046679,36844,283227,476,10500,44938,2120,261,157078};
    array <int, 12> values_10 = {83451,47,23,8040010,870,4825,63,31,4689,36,28,34644};

    csvparser in0("../../agregaty/qap/hubs_auths/scores/hubs_laczne.csv", ';');
    
    while (in0.next()) {
        int out = 0;
        int in = 0;
        for (int i = 1; i<13; i++) {
            if (tonum(in0[i]) >= values_10[i-1]) {
                if ((i+1) % 2 == 0) {
                    out += 1 << i/2;
                }  else {
                    in += 1 << (i-1)/2;
                }    
            }        
        }
        common_in[in]++;
        common_out[out]++;
    }
    
    ofstream of("../../agregaty/qap/auths_10.csv");

    for (auto& liczba: common_in) {
        of <<bitset<6>(liczba.first).to_string() <<";" <<liczba.second <<"\n";
    }

    ofstream of1("../../agregaty/qap/hubs_10.csv");

    for (auto& liczba: common_out) {
        of1 <<bitset<6>(liczba.first).to_string() <<";" <<liczba.second <<"\n";
    }

    
}    
