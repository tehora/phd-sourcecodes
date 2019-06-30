#include <stdio.h>

int main() {
    int state = 0;
    while (!feof(stdin)) {
        char c = fgetc(stdin);
        if(c == '\"') {
            state = !state;
            fputc(c, stdout);
        } else if (!(c == ',' && state == 1)) {
            fputc(c, stdout);
        }
    }
    return 0;
}
