#include <ghutils.h>
#include <map>
#include <vector>

using namespace std;

map <string, pair<string, string> > dep;
map <string, pair<string, string> > dep_pr;

int main(int argc, char **argv) {

    vector <string> kolejnosc = {"followers", "followers2", "stars_obtained", "stars_obtained2", "evc_following", "evc_following2", "following", "following2", "stars_given", "stars_given2", "forking_others", "forking_others2", "commits_others", "commits_others2", "comments_self", "comments_self2", "issues_self", "issues_self2", "comments_others", "comments_others2", "issues_others", "issues_others2", "javascript", "java", "ruby", "python", "php", "css", "html", "c++", "c", "objectivec", "c#", "shell", "perl", "coffeescript", "langcount", "fraction_functional", "fraction_web", "fraction_scientific", "email", "site", "repos", "repos2", "year2009", "year2010", "year2011", "year2012", "year2013", "year2014", "commits_self_base", "commits_self_base2", "commits_self_fork", "commits_self_fork2", "intercept" };
    
    {//wczytanie logitu
    csvparser in1("logit-short.txt",';');
    in1.next();
    while (in1.next()) {
        dep[in1[0]] = make_pair(in1[1], in1[4]);
    }
    }
    {
    //wczytanie pullrequests
    csvparser in2("logit-pr-short.txt",';');
    in2.next();
    while (in2.next()) {
        dep_pr[in2[0]] = make_pair(in2[1], in2[4]);
    }
    }
    ofstream of1("tabela.tex");

    of1 <<"\\begin{footnotesize}" <<"\n";
    of1 <<"\\begin{tabular}{l|c|cc||cc}" <<"\n";
    of1 <<"\\hline" <<"\n";
    of1 <<"\\multicolumn{2}{c}{} & \\multicolumn{2}{c}{\\emph{Forkability} & \\multicolumn{2}{c}{\\emph{Pullrequestability} \\\\" <<"\n";
    of1 <<"Set & Variable & Coef. & p-value & Coef. & p-value \\\\ \\hline" <<"\n";
    for (int i=0; i<kolejnosc.size(); i++) {
        switch(i)
        {
            case 0:
                of1 <<"\\multirow{6}{*}{Reputation} & " <<kolejnosc[1] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;
   
            case 6:
                of1 <<"\\multirow{8}{*}{Reciprocity} & " <<kolejnosc[i] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;
   
            case 14:
                of1 <<"\\multirow{8}{*}{Communication} & " <<kolejnosc[i] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;

            case 40:
                of1 <<"\\multirow{14}{*}{Information} &  " <<kolejnosc[i] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;

           case 23:
                of1 <<"\\multirow{18}{*}{Standardization} &  " <<kolejnosc[i] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;     
                
            default:
                of1 <<"& " <<kolejnosc[i] <<" & " <<dep[kolejnosc[i]].first <<" & " <<dep[kolejnosc[i]].second <<" & " << dep_pr[kolejnosc[i]].first <<" & " <<dep_pr[kolejnosc[i]].second <<" \\\\\n"; 
                break;
        }
    }
    of1 <<"\\multicolumn{6}{l}{Source: Own elaboration} \\\\\n";
    of1 <<"\\end{tabular}" <<"\n";
    of1 <<"\\end{footnotesize}" <<"\n";
}
