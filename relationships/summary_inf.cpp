#include <ghutils.h>
#include <unordered_map>
#include <bitset>

array<int, 6> nodes_network;
array<int, 6> unique_nodes;
array<int, 6> common;

// "comments_out;comments_in;issues_out;issues_in;forking_out;forking_in;pulls_out;pulls_in;starring_out;starring_in;follow_out;follow_in";

double shared_nodes(const char* file, int a, int b) {
    csvparser in1(file, ';');
    int common = 0;
    while (in1.next()) {
        if (tonum(in1[a])==1 & tonum(in1[b])==1) {
            common += tonum(in1[6]);
        }    
    }
    return 100*double(common)/double(-common + nodes_network[a] + nodes_network[b]);
}    

int main(int argc, char **argv) {

    csvparser in0(argv[1], ';');
    
    while (in0.next()) {
        int j = 0;
        for (int i = 0; i<6; i++) {
            j+= tonum(in0[i]);
            nodes_network[i]+= tonum(in0[i])*tonum(in0[6]);
        }
        if (j != 0 ) {
            common[j-1]+=tonum(in0[6]);
        }    
        if (j==1) {
            for (int m = 0; m < 6; m++) {
                unique_nodes[m] += tonum(in0[m])*tonum(in0[6]);
            }    
        }    
    }

    int all_nodes = common[0] + common[1] + common[2] + common[3] + common[4] + common[5];

    cout <<"\n";
    cout << "all nodes: " <<all_nodes <<"\n";

    cout << "follow_all: " <<nodes_network[5] <<"\n";
    cout << "star_all: " <<nodes_network[4] <<"\n";
    cout << "fork_all: " <<nodes_network[2] <<"\n";
    cout << "issues_all: " <<nodes_network[1] <<"\n";
    cout << "pulls_all: " <<nodes_network[3] <<"\n";
    cout << "comm_all: " <<nodes_network[0] <<"\n";

    cout << "follow_uniq: " <<100*double(unique_nodes[5])/double(nodes_network[5]) <<"\n";
    cout << "star_uniq: " <<100*double(unique_nodes[4])/double(nodes_network[4]) <<"\n";
    cout << "fork_uniq: " <<100*double(unique_nodes[2])/double(nodes_network[2]) <<"\n";
    cout << "issues_uniq: " <<100*double(unique_nodes[1])/double(nodes_network[1]) <<"\n";
    cout << "pulls_uniq: " <<100*double(unique_nodes[3])/double(nodes_network[3]) <<"\n";
    cout << "comm_uniq: " <<100*double(unique_nodes[0])/double(nodes_network[0]) <<"\n";

    cout <<"common 6: " <<100*double(common[5])/double(all_nodes) <<"\n";
    cout <<"common 5: " <<100*double((common[5] + common[4]))/double(all_nodes) <<"\n";
    cout <<"common 4: " <<100*double((common[5] + common[4] + common[3]))/double(all_nodes) <<"\n";
    cout <<"common 3: " <<100*double((common[5] + common[4] + common[3] + common[2]))/double(all_nodes) <<"\n";
    cout <<"common 2: " <<100*double((common[5] + common[4] + common[3] + common[2] + common[1]))/double(all_nodes) <<"\n";

    cout <<shared_nodes(argv[1],0,5) <<"\n";
    cout <<shared_nodes(argv[1],0,4) <<"\n";
    cout <<shared_nodes(argv[1],0,2) <<"\n";
    cout <<shared_nodes(argv[1],2,5) <<"\n";
    cout <<shared_nodes(argv[1],2,4) <<"\n";
    cout <<shared_nodes(argv[1],0,1) <<"\n";
    cout <<shared_nodes(argv[1],1,5) <<"\n";
    cout <<shared_nodes(argv[1],1,2) <<"\n";
    cout <<shared_nodes(argv[1],1,4) <<"\n";
    cout <<shared_nodes(argv[1],0,3) <<"\n";
    cout <<shared_nodes(argv[1],3,5) <<"\n";
    cout <<shared_nodes(argv[1],2,3) <<"\n";
    cout <<shared_nodes(argv[1],1,3) <<"\n";
    cout <<shared_nodes(argv[1],3,4) <<"\n";
    cout <<shared_nodes(argv[1],4,5) <<"\n";
    
}    
