#include <ghutils.h>
#include <map>

map <string, int> neuron_classify;
int fol[10];
int frk[10];
int iss[10];
int plr[10];
int cmm[10];
int str[10];
int A[520][520];

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
    for (int i=0;i<10; i++) {
        fol[i]=0;
        frk[i]=0;
        iss[i]=0;
        plr[i]=0;
        cmm[i]=0;
        str[i]=0;  
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
        csvparser in("../../agregaty/laczenie_grafow/following_graf_laczny_crawl.csv", ';');
        while (in.next()) {
            if (in[1]!=in[2] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[2]) > 0 ))  {
                fol[A[neuron_classify[in[1]]][neuron_classify[in[2]]]]++;
            }    
        }
    }
    {
        csvparser in("../../agregaty/laczenie_grafow/comments_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                cmm[A[neuron_classify[in[1]]][neuron_classify[in[3]]]]++;
            }    
        }
    }
    {
        csvparser in("../../agregaty/laczenie_grafow/forking_graf_laczny_crawl.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                frk[A[neuron_classify[in[1]]][neuron_classify[in[3]]]]++;
            }    
        }
    }
    {
        csvparser in("../../agregaty/laczenie_grafow/issues_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && in[4]=="opened" && (neuron_classify.count(in[1]) > 0  && neuron_classify.count(in[3]) > 0 )) {
                iss[A[neuron_classify[in[1]]][neuron_classify[in[3]]]]++;
            }    
        }
    }
    {
        csvparser in("../../agregaty/laczenie_grafow/pull_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && in[4]=="opened" && (neuron_classify.count(in[1]) > 0  && neuron_classify.count(in[3]) > 0 )) {
                plr[A[neuron_classify[in[1]]][neuron_classify[in[3]]]]++;
            }    
        }
    }
    {
        csvparser in("../../agregaty/laczenie_grafow/starring_graf_laczny.csv", ';');
        while (in.next()) {
            if (in[1]!=in[3] && (neuron_classify.count(in[1]) > 0 && neuron_classify.count(in[3]) > 0 )) {
                str[A[neuron_classify[in[1]]][neuron_classify[in[3]]]]++;    
            }
        }    
    }
    cout <<"fol;";
    for (int i = 0; i<10; i++) {
        cout <<fol[i] <<";";
    }
    cout <<"\n" <<"com;";
    for (int i = 0; i<10; i++) {
        cout <<cmm[i] <<";";
    }
   cout <<"\n" <<"frk;";
   for (int i = 0; i<10; i++) {
       cout <<frk[i] <<";";
    }
    cout <<"\n" <<"iss;";
    for (int i = 0; i<10; i++) {
        cout <<iss[i] <<";";
    }
    cout <<"\n" <<"plr;";
    for (int i = 0; i<10; i++) {
        cout <<plr[i] <<";";
    }
    cout <<"\n" <<"str;";
    for (int i = 0; i<10; i++) {
        cout <<str[i] <<";";
    }
    cout <<"\n";
}
