#include <ghutils.h>

int main() {
    
    csvparser in1("dziwni.csv",';');

    int liczba_repo=0;
    while (in1.next()) {
        liczba_repo+=tonum(in1[1]);
    }
    cout << "\nLiczba repo: " <<liczba_repo <<endl;
}
