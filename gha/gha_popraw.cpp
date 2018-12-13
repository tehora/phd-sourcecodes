#include <ghutils.h>
#include <set>

set <string> dates;
 
int main(int argc, char **argv) {
    
    csvparser in2(argv[1],';');
    
    while (in2.next()) {
        dates.insert(in2[0]);
    }

    csvparser in3(argv[2], ';');
    while (in3.next()) {
        dates.erase(in3[0]);
    }
    
    ofstream of1(argv[3]);
    
    for ( auto& date: dates) {
        of1 << date << "\n";
    }    
}    
