#include <ghutils.h>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <math.h> 

int number = 100;

set <pair <int, int>> edges;
set <pair <int, int>> random_net;
unordered_map <string, int> nodes;

//for simulations related to kohonen

map <int, int> neuron_classify;
int koh[10][100];
int A[520][520];

void insert_graph(const char* file) {
    csvparser in0(file, ';');
    int id = 1;  
    
    while (in0.next()) {
        if (in0[4] == "opened" && (in0[1] != in0[3])) {
            if (nodes.count(in0[3])==0) {
                nodes[in0[3]] = id;
                id++;
            }
            if (nodes.count(in0[1])==0) {
                nodes[in0[1]] = id;
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
    while (i < random_net.size()*5) {
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

void counting_distances(string file, int sim_num) {
   
    csvparser in(file.c_str(), ';');
        while (in.next()) {
            neuron_classify[nodes[in[0]]] = tonum(in[1]);
        }

    for (auto& edge: random_net) {
        if (neuron_classify.count(edge.first) > 0 && neuron_classify.count(edge.second) > 0 )  {
                koh[A[neuron_classify[edge.first]][neuron_classify[edge.second]]][sim_num]++;
        }  
    }        
}    

void leave_one_out(ofstream& out) {
    double means[10];
    double lower_means[10];
    double upper_means[10];
    double std_devs[10];
    
    double ith_avg[number];

    for (int i = 0; i<10; i++) {
        double sum = 0;
        double sum_means = 0;
        //sum of all values
        for (int j = 0; j<number; j++) {
            sum+=koh[i][j];
        }
        //ith average
        for (int z=0;z<number; z++) {
            ith_avg[z] = 0;
        }    
        for (int j = 0; j<number; j++) {
            ith_avg[j] = (sum-koh[i][j])/(number-1);
            sum_means+= ith_avg[j];
        }
        means[i] = sum_means/number;
        lower_means[i] = ith_avg[5];
        upper_means[i] = ith_avg[95];

        double sum_avgs = 0;
        for (int j = 0; j <number; j++) {
            sum_avgs += (double(ith_avg[j] - sum_means/number)*double(ith_avg[j] - sum_means/number));
        }

        std_devs[i] = sqrt(sum_avgs*(number-1)/number);
    }
    
    out << fixed <<setprecision(3);

    for (int i; i < 10; i++) {
        out << means[i] <<";"; 
    }
    for (int i; i < 10; i++) {
        out << lower_means[i] <<";"; 
    }
    for (int i; i < 10; i++) {
        out << upper_means[i] <<";"; 
    }
    for (int i; i < 9; i++) {
        out << std_devs[i] <<";"; 
    }
    out <<std_devs[9] <<"\n";
    out.flush();
}    


int main(int argc, char **argv) {
    srand( time( NULL ) ); 
    
    insert_graph(argv[1]);

    //neuron distances are always the same (the same tesselation)
    
    {
        csvparser in("../../src/kohonen/neuron-distances.csv", ';');
        int i=0;
        while (in.next()) {
            for (int j = 0; j<520; j++) {
                A[i][j]=tonum(in[j]);
            }
            i++;
        }
    }
    ofstream out(argv[3], ofstream::app); 

    for (int num=0; num <10; num++) {
        cout <<"creating random_net graph\n";
        create_random_net(edges);   

        //cleaning
        for (int x = 0; x<10; x++) {
            for (int y = 0; y <number; y++) {
                koh[x][y]=0;
            }
        }  
        
        // simulation
        // we iterate over the set of files containing results of som
        
        {
            csvparser in(argv[2], ';');
            int sim = 0;
            while  (in.next() && sim < number) {
                counting_distances(in[0],sim);
                sim++;
            }
        }
        // leave one out
        leave_one_out(out);
    }

}    
