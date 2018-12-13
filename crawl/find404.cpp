#include <ghutils.h>
#include <set>

set <string> brak404;
map <string, int> poroku;
map <int, int> brakujace_lata;
map <int, int> lata404;

int main() {
    csvparser in0("../logit/poroku.csv", ';');

    while (in0.next()) {
        poroku[in0[1]]=tonum(in0[4]);
    }
    
    csvparser in1("zbior_odwiedzonych.csv", ',');

    while (in1.next()) {
        brak404.insert(in1[0]);
    }
    
    csvparser in2("zbior_nonzero_repo.csv", ',');

    while (in2.next()) {
        brak404.erase(in2[0]);
    }

    csvparser in3("zbior_norepos_crawl.csv", ',');

    while (in3.next()) {
        brak404.erase(in3[1]);
    } 

    ofstream of1("zbior_404_crawl.csv");
    for (auto user: brak404) {
        of1 <<user << endl;
    }

    csvparser in4("zbior_nieodwiedzonych.csv", ',');
    while (in4.next()) {
        brakujace_lata[poroku[in4[0]]]++;
    }

    cout <<"Brakujace obserwacje w latach:\n"; 
    for (auto rok: brakujace_lata) {
        cout <<rok.first <<": " <<rok.second <<endl;  
    }

    for (auto deleted_user: brak404) {
        lata404[poroku[deleted_user]]++;
    }

    cout <<"Znalezione 404 w podziale na lata:\n";
    for (auto rok404: lata404) {
        cout <<rok404.first <<": " <<rok404.second <<endl;  
    }
}    
