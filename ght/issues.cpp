#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map<int, string> users;
unordered_map<int, pair<int, string> > repos;
unordered_map<int, int> issues;

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
        
        // first element is the owner's id, second is name of the repository
 
        repos[repo_id] = make_pair(tonum(in2[2]), in2[3]); 
    }}

    ofstream of1(argv[5]);

    {csvparser in3(argv[3], ',');
    while (in3.next()) {
        if(in3.fields < 2) {
            printf("fields = %d\n", in3.fields);
            continue;
        }
        int issue_id = tonum(in3[0]);
 
        issues[issue_id] = tonum(in3[1]);
        
        // auto -- it will "find" the type by themselves
        auto& rep = repos[tonum(in3[1])];
        if (rep.first == 0) {
            // printf("puste\n");
        } else {    
            of1 << in3[6] << ";" << users[tonum(in3[2])] << ";" << users[rep.first] <<"/" << rep.second  << ";" << users[rep.first] << ";" << "opened" << ";" << in3[7] << endl;
        }    
    }}

    {
    csvparser in4(argv[4], ','); 
    while (in4.next()) {
        
        // auto -- it will "find" the type by themselves
        int issue_repo = issues[tonum(in4[1])];
        auto& rep = repos[issue_repo];
        
        if (rep.first == 0) {
            // printf("puste\n");
        } else {
            of1 << in4[5] << ";" << users[tonum(in4[2])] << ";" << users[rep.first] <<"/" << rep.second  << ";" << users[rep.first] << ";" << in4[3] << ";" << in4[1] << endl;
        }
    }}
}   

