#include <ghutils.h>
#include <map>

map <string, int> neuron_classify;
int A[520][520];

int main(int argc, char **argv) {

    {
        csvparser in("../../src/kohonen/classify.txt", ';');
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

    ofstream of1("follow_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/following_graf_laczny_crawl.csv", ';');
        while (in.next()) {
            if (in[1]!=in[2] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[2]) > 0 ))  {
                of1 <<A[neuron_classify[in[1]]][neuron_classify[in[2]]] <<"\n";
            }    
        }
    }
    ofstream of2("comment_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/comments_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                of2 <<A[neuron_classify[in[1]]][neuron_classify[in[3]]] <<"\n";
            }    
        }
    }
     ofstream of3("fork_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/forking_graf_laczny_crawl.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                of3 <<A[neuron_classify[in[1]]][neuron_classify[in[3]]] <<"\n";
            }    
        }
    }
    ofstream of4("issues_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/issues_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && in[4]=="opened" && (neuron_classify.count(in[1]) > 0  && neuron_classify.count(in[3]) > 0 )) {
                of4 <<A[neuron_classify[in[1]]][neuron_classify[in[3]]] <<"\n";
            }    
        }
    }
    ofstream of5("pr_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/pull_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && in[4]=="opened" && (neuron_classify.count(in[1]) > 0  && neuron_classify.count(in[3]) > 0 )) {
                of5 <<A[neuron_classify[in[1]]][neuron_classify[in[3]]] <<"\n";
            }    
        }
    }
    ofstream of6("starring_dist.csv");
    {
        csvparser in("../../agregaty/laczenie_grafow/starring_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                of6 <<A[neuron_classify[in[1]]][neuron_classify[in[3]]] <<"\n";    
            }
        }    
    }

}
