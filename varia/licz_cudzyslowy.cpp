#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream in("users.csv");
    ofstream out("cudzyslowy");
    string row;
    while (getline(in,row)) {
        int liczba=0;
        for (int i=0; i<row.length(); ++i) {
            if (row[i] == '\"') {
                ++liczba;
            }
        }
        out <<liczba;
        out <<'\n';
    }
    return 0;
}
