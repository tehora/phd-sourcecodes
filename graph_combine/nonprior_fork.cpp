#include <unordered_map>
#include <ghutils.h>

using namespace std;

set <string> forks;

int main(int argc, char **argv) {
  char buf[64];
  
  {
  csvparser in1(argv[1], ';');
  while (in1.next()) {
      string id = in1[1] + ";" + in1[3] + "/" + in1[2] + ";" + in1[3];
      forks.insert(id);
    }
  }
  ofstream fix(argv[3]);
 {
  csvparser in1(argv[2], ';');
  while (in1.next()) {
      string id = in1[1] + ";" + in1[2] + ";" + in1[3];
      if (forks.count(id)==0) {
          forks.insert(id);
          string project_name = in1[2].substr(in1[2].find('/')+1);
          fix <<in1[0] <<";" << in1[1] << ";" << project_name <<";" <<in1[3] <<"\n";          
      }    
    }
  }
  return 0;
  }

