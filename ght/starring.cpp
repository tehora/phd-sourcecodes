#include <ghutils.h>
#include <vector>
#include <unordered_map>

unordered_map<int, string> users;
unordered_map<int, pair<int, string> > repos;

void write_graph(csvparser& in, ofstream& of) {
    // first: repo
    // second: source_id
    // created_at

    while (in.next()) {

        // auto -- it will "find" the type by themselves
        
        auto& rep = repos[tonum(in[0])];
        if (rep.first == 0) {
            printf("puste\n");
        } else {
            of << in[2] << ";" << users[tonum(in[1])] << ";" << rep.second << ";" << users[rep.first] << endl;
        }
    }
}

int main(int argc, char *argv[]) {

    // read the users logins and id from ght
    
    csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) {
            printf("fields = %d\n", in1.fields);
            continue;
        }
        int id = tonum(in1[0]);
        users[id] = in1[1];
    }

    // read the repos and owners from ght

    csvparser in2(argv[2], ','); 
    while (in2.next()) {
        in2.progressbar();
        if(in2.fields < 2) {
            printf("fields = %d\n", in2.fields);
            continue;
        }
        int repo_id = tonum(in2[0]);
        
        // first element is the owner's id, second is name of the repository
 
        repos[repo_id] = make_pair(tonum(in2[2]), in2[3]); 
    }
	csvparser in3(argv[3], ',');
        ofstream of1(argv[4]);
        write_graph(in3, of1);
    
}   

