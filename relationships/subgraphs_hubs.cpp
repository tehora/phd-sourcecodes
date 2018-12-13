#include <ghutils.h>
#include <set>
#include <unordered_map>

set <pair<int,int>> edges;
unordered_map <int, array<int, 2>> nodes;

array <int, 10> values_5;
array <int, 10> values_1;
array <int, 10> values_10;

void is_imp(const char* plik, int graph, int score, int level) {
    {
    csvparser in0(plik, ';');

    while (in0.next()) {
        
        if (nodes.count(tonum(in0[0]))==0) {
            for (int i =0 ; i<2; i++) {
                nodes[tonum(in0[0])][i] = 0; 
            }
        }    
        if (level == 1) {
            // 0 -- hubs, 1 -- auths
            if (tonum(in0[1]) >= values_1[graph]) {
                nodes[tonum(in0[0])][score]++;
            }
        } else {
            if (level == 5) {
                if (tonum(in0[1]) >= values_5[graph]) {
                    nodes[tonum(in0[0])][score]++;
                }
            } else {
                if (tonum(in0[1]) >= values_10[graph]) {
                    nodes[tonum(in0[0])][score]++;
                }
            }
        }
    }
    }
}    


int main(int argc, char **argv) {

    values_5 = {172836,491,45,8040182,3259,30539,143,201,64,94099};
    values_1 = {438251,7589,146,8046679,36844,283227,476,10500,262,157079};
    values_10 = {83451,48,23,8040010,870,4825,63,31,29,34645};

    int level = tonum(argv[5]);
    int hub_number = tonum(argv[2]);
    int auth_number = tonum(argv[4]);
    
    is_imp(argv[1], hub_number, 0, level);
    is_imp(argv[3], auth_number, 1, level);

    csvparser in1(argv[6], ';');

    while (in1.next()) {
        if (tonum(in1[0]) != tonum(in1[1])) {
            if ((nodes[tonum(in1[0])][0]==1 || nodes[tonum(in1[0])][1]==1) && (nodes[tonum(in1[1])][0]==1 || nodes[tonum(in1[1])][1]==1)) {
                edges.insert(make_pair(tonum(in1[0]), tonum(in1[1])));
            }
        }    
    }   
    
    ofstream of(argv[7]);

    of <<"id;is_hub;is_auth" <<"\n";
    
    for (auto& user: nodes) {
        if (user.second[0] == 1 || user.second[1] == 1) {
            of <<user.first <<";" << user.second[0] <<";" <<user.second[1] <<"\n";
        }    
    }

    ofstream of1(argv[8]);

    for (auto& edge: edges) {
        of1 <<edge.first <<";" <<edge.second <<"\n";
    }    
       
}    
