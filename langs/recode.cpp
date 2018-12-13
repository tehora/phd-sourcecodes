#include <ghutils.h>
#include <map>
#include <vector>

map< string, int > jezyki;

int main() {

    //csvparser in1("jezyki.csv", ';');

    //ofstream of1("lang_nodes.csv");

    //int numer_jezyka = 1;
    
    //while(in1.next()) { 
    //    jezyki[in1[1]] = numer_jezyka;
    //    of1 << numer_jezyka <<";" <<in1[1] <<";" <<in1[0] <<endl;
    //    numer_jezyka++;
    //} 

    csvparser in1("lang_nodes.csv", ';');
    
    while(in1.next()) { 
        jezyki[in1[1]] = tonum(in1[0]);
    } 
    
    
    ofstream of2("lang_edges_gephi.csv");
    csvparser in2("lang_edges.csv", ';');

    while(in2.next()) {
        of2 << jezyki[in2[0]] <<";" <<jezyki[in2[1]] <<";" <<in2[2] <<";" <<"Undirected" <<endl;
    }   
}    
