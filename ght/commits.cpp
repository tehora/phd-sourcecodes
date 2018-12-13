#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map<int, string> users;
unordered_map<int, pair<int, int>> repos;
unordered_map<int, array<int, 3>> commits;

int main(int argc, char **argv) {

    // read the users logins and id from ght
    
    {
    csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) {
            printf("fields = %d\n", in1.fields);
            continue;
        }
        int id = tonum(in1[0]);
        users[id] = in1[1];
    }
    }

    // read the repos and owners from ght

    {csvparser in2(argv[2], ','); 
    while (in2.next()) {
        if(in2.fields < 2) {
            printf("fields = %d\n", in2.fields);
            continue;
        }
        int repo_id = tonum(in2[0]);
        
        // first is the owner's id, second is fork or not
 
        repos[repo_id].first = tonum(in2[2]);
        repos[repo_id].second = in2[7]!="\\N" ? 1 : 0;
    }}

    ofstream of1(argv[4]);
    
    {
    csvparser in4(argv[3], ','); 
    while (in4.next()) {
        
        // auto -- it will "find" the type by themselves
        int commit_author = tonum(in4[2]);
        auto& rep_author = repos[tonum(in4[4])].first;
        
        if (rep_author != commit_author) {
            commits[rep_author][2]++;
        } else {
            if (repos[tonum(in4[4])].second == 1 ) {
                commits[rep_author][1]++;
            } else {
                commits[rep_author][0]++;
            }    
        }
    }
    of1 << "user;self_commits_base;self_commits_forks;other_commits" <<"\n";
        for (auto& commit: commits) {            
            of1 << users[commit.first] << ";" << commit.second[0] << ";" << commit.second[1] << ";" << commit.second[2] << "\n";
        }
    }
}   

