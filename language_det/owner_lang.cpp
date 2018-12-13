#include <ghutils.h>
#include <map>
#include <unordered_map>
#include <vector>

int nextkey = 1;

unordered_map<string, int> keys;
vector<const string*> keytostr;

int getkey(const string& s) {
  auto& i = keys[s];
  if(i == 0) { i = nextkey++; keytostr.push_back(&(keys.find(s)->first)); }
  return i;
  }

typedef int strkey;

map<pair<strkey, strkey>, set<strkey>> repo_langs;
map<pair<strkey, strkey>, int> langs_count;

int main(int argc, char **argv) {

    string nul = "(NULL)";
    keytostr.push_back(&nul);

    // read the users logins and id from ght
    
    unordered_map<int, strkey> users;
    {csvparser in1(argv[1], ','); 
    while (in1.next()) {
        if(in1.fields < 2) {
            printf("\n fields = %d\n", in1.fields);
            continue;
        }
        int id = tonum(in1[0]);
        users[id] = getkey(tolower(in1[1]));
    }}

    // read the repos and owners from ght

    unordered_map<int, pair<strkey, strkey> > repos;
    {csvparser in2(argv[2], ','); 
    while (in2.next()) {
        if(in2.fields < 2) {
            printf("\n fields = %d\n", in2.fields);
            continue;
        }
        int repo_id = tonum(in2[0]);
        
        // first element is the owner's name, second is name of the repository
 
        repos[repo_id] = make_pair(users[tonum(in2[2])], getkey(tolower(in2[3])));
    }}

    users.clear();

    {csvparser in3(argv[3], ',');

    while(in3.next()) {
        if(in3.fields <2) {
            printf("\n fields = %d\n", in3.fields);
            continue;
        }    
        auto user_repo = repos[tonum(in3[0])];
        repo_langs[user_repo].insert(getkey(in3[1]));
    }}

    repos.clear();

    {csvparser in4(argv[4], ';'); in4.next();

    while(in4.next()) {
        string& login = in4[0];
        string& repo =  in4[1];
        auto user_repo = make_pair(getkey(tolower(login)), getkey(tolower(repo)));
        // if (!repo_langs.count(user_repo)) {
        // repo_langs[user_repo].insert(tolower(in4[2]));
        // } else {
        if (in4[2]!="") {
            repo_langs[user_repo].insert(getkey(tolower(in4[2])));
        }
    }}

    /* for (auto& entry: repo_langs) {
        for (auto& lang: entry.second) {
            auto user_lang = make_pair(entry.first.first, lang);
            langs_count[user_lang]++;
        }
        entry.second.clear();
    } */
    
    while(!repo_langs.empty()) {
      auto &entry = *repo_langs.begin();
      for (auto& lang: entry.second) {
          auto user_lang = make_pair(entry.first.first, lang);
          langs_count[user_lang]++;
      }
      repo_langs.erase(repo_langs.begin());
      }

    repo_langs.clear();
        
    ofstream of1(argv[5]);

    of1 <<"user;lang;number" << endl;
    
    for(auto lang: langs_count ) {
        of1 << *keytostr[lang.first.first] << ";" << *keytostr[lang.first.second] <<";" <<lang.second  << "\n"; 
    }    
}    
