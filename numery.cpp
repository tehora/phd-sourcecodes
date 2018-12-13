#include <ghutils.h>

int main(int argc, char **argv) {
  csvparser in(argv[1]);
  in.next();
  for(int i=0; i<in.fields; i++)
    printf("%3d: %s\n", i, in[i].c_str());
  return 0;
  }
