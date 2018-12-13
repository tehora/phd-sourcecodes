#include <ghutils.h>
#include <map>

map <string, int> neuron_classify;
int A[520][520];
map <string, array<int,5>> projects_d;
map <string, array<int,5>> projects_w;

int main(int argc, char **argv) {

    {
        csvparser in(argv[1], ';');
        while (in.next()) {
            neuron_classify[in[0]] = tonum(in[1]);
        }
    }

    for (int i=0;i<520; i++) {
        for (int j=0; j<520; j++) {
            A[i][j]=0;
        }    
    }    

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

    {
        csvparser in("../../agregaty/hetero/projects_people_w.csv", ';');
        while (in.next()) {
            if (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0)  {
                string repo = in[1] + "/" + in[2];
                if (in[4] == "c") {
                    projects_d[repo][0] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                    projects_d[repo][1] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                    projects_w[repo][0] += tonum(in[0]);
                    projects_w[repo][1] += tonum(in[0]);
                } else {
                    if (in[4] == "i") {
                        projects_d[repo][0] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                        projects_d[repo][2] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                        projects_w[repo][0] += tonum(in[0]);
                        projects_w[repo][2] += tonum(in[0]);
                    } else {
                        if (in[4] == "m") {
                           projects_d[repo][0] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                           projects_d[repo][3] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                           projects_w[repo][0] += tonum(in[0]);
                           projects_w[repo][3] += tonum(in[0]); 
                        } else {
                            projects_d[repo][0] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                            projects_d[repo][4] += tonum(in[0])*A[neuron_classify[in[1]]][neuron_classify[in[3]]];
                            projects_w[repo][0] += tonum(in[0]);
                            projects_w[repo][4] += tonum(in[0]);
                        }    
                    }    
                }                                                           
            }    
        }
    }
    ofstream of1(argv[2]);
    of1 <<"project;overall;comments;issues;forks;pulls" <<"\n";
    for (auto project: projects_d) {
        of1 <<project.first <<";";
        for (int i = 0; i<5; i++) {
            if (projects_w[project.first][i] !=0) {
                of1 <<double(project.second[i])/double(projects_w[project.first][i]) <<";";
            } else {
                of1 <<99 <<";";
            }    
        }
        of1 <<"\n";
    }       
}
