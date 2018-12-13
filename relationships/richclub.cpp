#include <ghutils.h>
#include <set>
#include <vector>
#include <unordered_map>

set <pair <int, int>> edges;
set <pair <int, int>> random_net;
unordered_map <int, array<int,3>> degrees;

set <int> nodes;
int maxk = 0;

//0 -- degree; 1 -- out-degree; 2 -- in-degree

unordered_map <int, array<double,2>> richclubs;
//unordered_map <int, array<array<double, 3>, 2>> richclubs;

void insert_graph(const char* plik) {
    csvparser in0(plik, ';');

    while (in0.next()) {
        if (tonum(in0[0]) != tonum(in0[1])) {
            if (nodes.count(tonum(in0[0]))==0) {
                nodes.insert(tonum(in0[0]));
            }
            if (nodes.count(tonum(in0[1]))==0) {
                nodes.insert(tonum(in0[1]));
            }
            edges.insert(make_pair(tonum(in0[0]), tonum(in0[1])));
            if (degrees.count(tonum(in0[0]))==0) {
                for (int i =0 ; i<3; i++) {
                    degrees[tonum(in0[0])][i] = 0; 
                }
            }
            degrees[tonum(in0[0])][0]++;
            degrees[tonum(in0[0])][1]++;   
            if (degrees.count(tonum(in0[1]))==0) {
                for (int i =0 ; i<3; i++) {
                    degrees[tonum(in0[1])][i] = 0; 
                }
            }
            degrees[tonum(in0[1])][0]++;
            degrees[tonum(in0[1])][2]++;

        }
    }
    for (auto& node: degrees) {
        if (node.second[0] > maxk) {
            maxk = node.second[0];
        }
    }
}

void create_random_net(set<pair<int,int>>& orig) {
    random_net = orig;
    
    vector <pair<int,int>> v;
    for (auto e:random_net) v.push_back(e);

    int zle = 0;
    int i = 0;
    while (i < random_net.size()*100) {
        i++;
        int first = rand() % random_net.size();
        int second = rand() % random_net.size();
        if (v[first].first == v[second].second || v[first].second == v[second].first || random_net.count(make_pair(v[first].first,v[second].second))!=0 || random_net.count(make_pair(v[second].first,v[first].second))!=0) {
            zle++;
            continue;
        } else {
            random_net.erase(v[first]);
            random_net.erase(v[second]);
            pair <int, int> a = make_pair(v[first].first,v[second].second);
            pair <int, int> b = make_pair(v[second].first,v[first].second);                              
            random_net.insert(a);
            random_net.insert(b);
            v[first] = a;
            v[second] = b;
        }    
     }  
    cout <<"bylo zle: " <<zle <<"\n";    
}

void calculate_richclubs(set<pair<int, int>>& graph, vector <int>& degs, int& type, int random_net) {
    vector<int> edge_num(maxk+1, 0);
    for (auto& edge: graph) {
        edge_num[min(degrees[edge.first][type], degrees[edge.second][type])]++;
    }
    for (int k=0; k< maxk+1; k++) {
        int nk = 0;
        int ek = 0;
        for (int j = k; j<maxk+1; j++) {
            nk+=degs[j];
            ek+=edge_num[j];
        }
        if (nk > 1) {
            if (random_net == 0) {
                richclubs[k][0] = double(ek)/(double(nk)*double(nk-1));
                //richclubs[k][0][0] = double(ek)/(double(nk)*double(nk-1));
                //richclubs[k][0][1] = double(ek);
                //richclubs[k][0][2] = double(nk-1);
            } else {
                richclubs[k][1] = double(ek)/(double(nk)*double(nk-1));
                //richclubs[k][1][0] = double(ek)/(double(nk)*double(nk-1));
                //richclubs[k][1][1] = double(ek);
                //richclubs[k][1][2] = double(nk-1);
            }
        }
    }    
}    

int main(int argc, char **argv) {
    srand( time( NULL ) );
    insert_graph(argv[1]);
    //insert_graph("../../agregaty/qap/issues_un.csv");
    //insert_graph("../../agregaty/qap/forking_un.csv");
    //insert_graph("../../agregaty/qap/pulls_un.csv");
    //insert_graph("../../agregaty/qap/starring_un.csv");
    //insert_graph("../../agregaty/qap/follow_un.csv");

    cout <<"creating random_net graph\n";
    create_random_net(edges);

    int mode = tonum(argv[2]);
    
    vector<int> deg_num(maxk+1,0);
    for (auto& node: degrees) {
        deg_num[node.second[mode]]++;
    }    
    
    cout << "calculating for empirical\n";
    calculate_richclubs(edges,deg_num,mode, 0);
    cout << "calculating for random_net\n";
    calculate_richclubs(random_net,deg_num, mode, 1);     
    
    ofstream of(argv[3]);

    of <<"k;richclub\n";
    
    for (auto& cutoff: richclubs) {
        of <<cutoff.first <<";" <<cutoff.second[0]/cutoff.second[1] <<"\n";
        //of <<cutoff.first <<";" <<cutoff.second[0][0]/cutoff.second[1][0] <<";" <<cutoff.second[0][1] <<";" <<cutoff.second[0][2] <<";" <<cutoff.second[1][1] <<";" <<cutoff.second[1][2] <<"\n";
    }    
}    
