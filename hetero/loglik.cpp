#include <ghutils.h>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include<tgmath.h> 

set <pair <string, string>> edges;

unordered_map <string, int> nodes;

const int number = 200;

//for computation of loglikelihoods

double logliks[3][number];

void insert_graph(const char* file) {
    csvparser in0(file, ';');
    
    while (in0.next()) {
        //for issues and pulls
        //if (in0[4] == "opened" && (in0[1] != in0[3])) {
        //for forking
        //if (in0[1] != in0[3]) {
        //for following
        if (in0[1] != in0[2]) {
            //edges.insert(make_pair(in0[1], in0[3]));
            edges.insert(make_pair(in0[1], in0[2]));
        }
    }
}

void leave_one_out(int ktore) {
    double mean=0;
    double lower_mean=0;
    double upper_mean=0;
    double std_dev=0;
    
    double ith_avg[number];
    double sum = 0;
    double sum_means = 0;
    
    for (int i = 0; i<number; i++) {
        //sum of all values
            sum+=logliks[ktore][i];
        }
    //ith average
    for (int z=0;z<number; z++) {
        ith_avg[z] = 0;
    }    
    for (int j = 0; j<number; j++) {
        ith_avg[j] = (sum-logliks[ktore][j])/(number-1);
        sum_means+= ith_avg[j];
    }
    mean = sum_means/number;
    sort(ith_avg, ith_avg + number);
    lower_mean = ith_avg[10];
    upper_mean = ith_avg[190];

    double sum_avgs = 0;
    for (int j = 0; j <number; j++) {
        sum_avgs += (double(ith_avg[j] - sum_means/number)*double(ith_avg[j] - sum_means/number));
    }

    std_dev = sqrt(sum_avgs*(number-1)/number);

    cout << fixed <<setprecision(3);

    cout << mean <<";" <<lower_mean <<";" << upper_mean <<";" << std_dev <<"\n";
}    

double loglik_at(long long p, long long all) {
  long long q = all - p;
  if(!p || !q) return 0;
  return log(double(p)/all)*p + log(double(q)/all)*q;
  }

int main(int argc, char **argv) {
    srand( time( NULL ) ); 

    int neuron_n = tonum(argv[1]);

    //place for storing the distances
    vector<vector<int> > A;
    A = vector<vector<int>> ( neuron_n, vector<int> (neuron_n, 0));

    //insert the network
    insert_graph(argv[2]);

    //neuron distances are always the same (the same tesselation)

    int max_dist = 0;
    
    {
        csvparser in(argv[3], ';');
        int i=0;
        while (in.next()) {
            for (int j = 0; j< neuron_n; j++) {
                A[i][j]=tonum(in[j]);
                if (tonum(in[j]) > max_dist) {
                    max_dist = tonum(in[j]);
                }    
            }
            i++;
        }
    }
    //ofstream out(argv[5], ofstream::app); 

    long obs_per_neuron[neuron_n];
    long possible_in_distance[max_dist+1];
    long emp_in_distance[max_dist+1];
    //iterating over the set of files containing results of som

    {
        csvparser in(argv[4], ';');

        int koh = 0;
        
        while (in.next() && koh < number) {
            {
            csvparser in1(in[0], ';');

            //place for storing observations per neuron

            for (int i =0; i < neuron_n; i++) {
                obs_per_neuron[i] = 0;
            }
            
            map<pair<int, int>, long> npairs;
            
            while (in1.next()) {
                nodes[in1[0]] = tonum(in1[1]);
                obs_per_neuron[tonum(in1[1])]++;
            }

            //how many observations within a given distance (in general)
            
            for (int i =0; i <= max_dist; i++) {
                possible_in_distance[i] = 0;
            }
 
            for (int n1 = 0; n1 < neuron_n; n1++) {
                for (int n2 = 0; n2 <= n1; n2++) {
                    if (n1 < n2) {
                        possible_in_distance[A[n1][n2]] += obs_per_neuron[n1]*obs_per_neuron[n2];
                    } else {
                        possible_in_distance[A[n1][n2]] += (obs_per_neuron[n1]*(obs_per_neuron[n2]-1))/2;
                    }    
                }    
            }

            //how many observations within a given distance (in a real graph)
            for (int i =0; i <= max_dist; i++) {
                emp_in_distance[i] = 0;
            }
            
            for (auto& edge: edges) {
                if (nodes.count(edge.first) > 0 && nodes.count(edge.second) > 0 ) {
                    emp_in_distance[A[nodes[edge.first]][nodes[edge.second]]]++;
                    npairs[{nodes[edge.first], nodes[edge.second]}]++;
                }
            }   

            //compute log-likelihood      

            double loglik = 0;
            
            for (int i = 0; i <= max_dist; i++) loglik += loglik_at(emp_in_distance[i], possible_in_distance[i]);
            
            double loglik2 = 0;
            
            for(int i=0; i<neuron_n; i++) for(int j=0; j<neuron_n; j++) {
              long possible = obs_per_neuron[i] * obs_per_neuron[j];
              if(i == j) possible -= obs_per_neuron[i];
              if(npairs[{i,j}] > possible)
                printf("error: npairs = %d possible = %d\n", int(npairs[{i,j}]), possible);
              else
                loglik2 += loglik_at(npairs[{i,j}], possible);
              }

            double loglik3 = 0;
            
            for (int i = 0; i <= max_dist; i+=2) {
              if(i < max_dist) emp_in_distance[i] += emp_in_distance[i+1], possible_in_distance[i] += possible_in_distance[i+1];
              loglik3 += loglik_at(emp_in_distance[i], possible_in_distance[i]);
              }
            
            logliks[0][koh] = loglik;
            logliks[1][koh] = loglik2;
            logliks[2][koh] = loglik3;
            }

            koh++;    
        }
    }
    cout << fixed <<setprecision(3);
    cout << neuron_n << ";" << max_dist << ";" << nodes.size() << ";" << edges.size() << "\n";
    for(int ktore=0; ktore<3; ktore++) {
      for (int i =0; i<number; i++) {
          cout <<logliks[ktore][i] <<";";
      }
      cout <<"\n";
      }
    // leave one out
    leave_one_out(0);
    leave_one_out(1);
    leave_one_out(2);

}    
