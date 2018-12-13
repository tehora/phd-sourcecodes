#include <ghutils.h>
#include <unordered_map>

unordered_map<int, string> users;
unordered_map<int, pair<int, string> > repos;
unordered_map<int, pair<int, int> > pr;  

ostream& userinfo(ostream& s, int id) {
  return s << "(UID " << id << ":" << users[id] << ")";
  }

ostream& repoinfo(ostream &s, int id) {
  auto p = repos[id];
  s << "(REPO " << id << ": owner ";
  userinfo(s, p.first);
  return s << ", " << p.second << ")";
  }

ostream& prinfo(ostream &s, int id) {
  auto p = pr[id];
  s << "(PR " << id << ": original ";
  repoinfo(s, p.first);
  s << ", fork "; 
  repoinfo(s, p.second);
  return s << ")";
  }

int main(int argc, char **argv) {

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
        if(in2.fields < 2) {
            printf("fields = %d\n", in2.fields);
            continue;
        }
        int repo_id = tonum(in2[0]);
        
        // first element is the owner's id, second is name of the repository
 
        repos[repo_id] = make_pair(tonum(in2[2]), in2[3]); 
    }

    csvparser in3(argv[3], ',');
    while (in3.next()) {
        if(in3.fields < 2) {
            printf("fields = %d\n", in3.fields);
            continue;
        }
        int pr_id = tonum(in3[0]);

        //first is base_repo_id, second is head_repo_id
        
        pr[pr_id] = make_pair(tonum(in3[2]), tonum(in3[1]));
    }

    csvparser in4(argv[4], ',');
    ofstream of1(argv[5]);

    while (in4.next()) {

        // auto -- it will "find" the type by themselves
        auto& pr_repo = pr[tonum(in4[1])];
        auto& rep_base = repos[pr_repo.first];
        
        if (rep_base.first == 0) {
            printf("puste\n");
        } else {
        //    if (in4[3]=="closed" && users[tonum(in4[4])] == users[rep_base.first]) {
               // of1 << in4[2] << ";" << users[repos[pr_repo.second].first] << ";" << users[rep_base.first] << "/" << rep_base.second  << ";" << users[rep_base.first] << ";" << in4[3] << ";" << in4[1] << endl;
           // } else {
            of1 << in4[2] << ";" << users[tonum(in4[4])] << ";" << users[rep_base.first] << "/" << rep_base.second  << ";" << users[rep_base.first] << ";" << in4[3] << ";" << in4[1] << endl;
            }
        //}
    }
}
