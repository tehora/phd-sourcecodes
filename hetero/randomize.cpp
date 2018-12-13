#include <ghutils.h>
#include <set>
#include <vector>
#include <unordered_map>

set <pair <int, int>> edges;
set <pair <int, int>> random_net;
unordered_map <int, string> nodes2;

void insert_graph(const char* file) {
    csvparser in0(file, ';');
    unordered_map <string, int> nodes;
    int id = 1;  
    
    while (in0.next()) {
        if (in0[1] != in0[3]) {
            if (nodes.count(in0[3])==0) {
                nodes[in0[3]] = id;
                nodes2[id] = in0[3];
                id++;
            }
            if (nodes.count(in0[1])==0) {
                nodes[in0[1]] = id;
                nodes2[id] = in0[1];
                id++;
            }
            edges.insert(make_pair(nodes[in0[1]], nodes[in0[3]]));
        }
    }
}

void create_random_net(set<pair<int, int>>& orig) {
    random_net = orig;
    
    vector <pair<int, int>> v;
    for (auto e:random_net) v.push_back(e);

    int wrong = 0;
    int i = 0;
    while (i < random_net.size()*100) {
        i++;
        int first = rand() % random_net.size();
        int second = rand() % random_net.size();
        if (v[first].first == v[second].second || v[first].second == v[second].first || random_net.count(make_pair(v[first].first,v[second].second))!=0 || random_net.count(make_pair(v[second].first,v[first].second))!=0) {
            wrong++;
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
    cout <<"incorrect: " <<wrong <<"\n";    
}

int main(int argc, char **argv) {
    srand( time( NULL ) );
    insert_graph(argv[1]);
    
    cout <<"creating random_net graph\n";
    create_random_net(edges);   

    cout <<"writing to a file\n";
    
    ofstream of(argv[2]);
    
    for (auto& edge: random_net) {
        of <<nodes2[edge.first] <<";" <<nodes2[edge.second] <<"\n";
    }    
}    
