#include <ghutils.h>
#include <map>
#include <unordered_map>
#include <vector>

set<string> base_projects;
unordered_map<string, string> forks;
set<string> relationships; 

void read_graphs(const char* plik, char type) {
     {csvparser in(plik, ';');
     while(in.next()) {
         if (in[1] != in[3]) {
             if (base_projects.count(in[2]) > 0) {
                 string rel = in[2] + ";" + in[1] + ";" + type; 
                 relationships.insert(rel);
             } else {
                 if (forks.count(in[2]) > 0) {
                     string rel = forks[in[2]] + ";" + in[1] + ";" + type;
                     relationships.insert(rel);
                 } else {
                     base_projects.insert(in[2]);
                     string rel = in[2] + ";" + in[1] + ";" + type;
                     relationships.insert(rel);
                 }    
             }    
         }
     }
     }    
}    


int main(int argc, char **argv) {
//start with reading the list of repositories
    {csvparser in("../../agregaty/users_char/owner_repo_laczne.csv", ';'); in.next();
     while(in.next()) {
         if (tonum(in[3]) == 0) {
             string project = in[0] + "/" + in[1];
             base_projects.insert(project);
         }             
     }   
    }
    //forks from the members network -- contain information from list of repositories
    
    {csvparser in("../../agregaty/laczenie_grafow/forking_graf_laczny_crawl.csv", ';');
     while(in.next()) {
             string fork = in[1] + "/" + in[2];
             string proj = in[3] + "/" + in[2];
             string rel = proj + ";" + in[1] + ";" + "m";
             relationships.insert(rel);
             forks[fork] = proj;
         }
     }
    
    //relationships from networks
    read_graphs("../../agregaty/laczenie_grafow/comments_graf_laczny.csv", 'c');    
    read_graphs("../../agregaty/laczenie_grafow/issues_graf_laczny.csv", 'i');
    read_graphs("../../agregaty/laczenie_grafow/pull_graf_laczny.csv", 'p');
    
    ofstream of1(argv[1]);
    for (auto relation: relationships) {
        of1 << relation <<"\n";
    } 
}      
