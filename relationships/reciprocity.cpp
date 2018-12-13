#include <ghutils.h>
#include <set>

set <string> reciprocity;
double edges = 0;
double mutual_edges = 0;

int main(int argc, char **argv) {

    csvparser in0(argv[1], ';');

    while (in0.next()) {
        edges++;
        string ts = in0[1] + ";" + in0[0];
        if (reciprocity.count(ts)==0) {
            string st = in0[0] + ";" + in0[1]; 
            reciprocity.insert(st);
        }  else {
            mutual_edges++;
        }    
    }

    cout <<"Krawedzi znaleziono: " <<edges <<endl;
    cout <<"Wspolnych znaleziono: " <<mutual_edges <<endl;
    cout <<"Jest to procent: " <<(mutual_edges/edges)*100 <<endl;   
}    
