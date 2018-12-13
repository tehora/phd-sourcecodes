#include <ghutils.h>
#include <vector>

int main(int argc, char **argv) {
    
    csvparser in1(argv[1], ',');
    ofstream of1(argv[3]);
    while (in1.next()) {
        if(in1.fields < 2) {
            printf("fields = %d\n", in1.fields);
            continue;
        }
        of1 <<in1[2] <<";" <<in1[1] <<";" <<in1[0] << endl;
    }

    csvparser in2(argv[2], ',');
    while (in2.next()) {
        if(in2.fields < 2) {
            printf("fields = %d\n", in2.fields);
            continue;
        }
        of1 <<in2[0] <<";" <<in2[2] <<";" <<in2[1] << endl;
    }
}   


