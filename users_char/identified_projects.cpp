#include <ghutils.h>
#include <map>

// first value -- scraping
// second value -- GHT
// third value -- GHA

map <string, array<int, 3>> repos;

int main(int argc, char **argv) {
    //getting projects from scraping

    {
        csvparser in1("../../agregaty/crawl/owner_repo_crawl.csv", ';');
        while (in1.next()) {
            string repo = tolower(in1[0]) + "/" + tolower(in1[1]);
            repos[repo][0] = 1;
        }    
    }
    // getting users from GHT
    {
        csvparser in1("../../agregaty/ght/owner_repo_ght.csv", ';');
        in1.next();
        while (in1.next()) {
            string repo = tolower(in1[0]) + "/" + tolower(in1[1]);
            repos[repo][1] = 1;
        }    
    }
    // getting users from GHA
    {
        csvparser in1("../../agregaty/gha/commentevent/comments_graf.csv", ';');
        in1.next();
        while (in1.next()) {
            repos[tolower(in1[4])][2] = 1;
        }    
    }
    {
        csvparser in1("../../agregaty/gha/forkevent/forking_graf.csv", ';');
        in1.next();
        while (in1.next()) {
            string repo = tolower(in1[5]) + "/" + tolower(in1[4]);
            repos[repo][2] = 1;
        }    
    }
    {
        csvparser in1("../../agregaty/gha/pullevent/pull_graf.csv", ';');
        in1.next();
        while (in1.next()) {
            repos[in1[4]][2] = 1;
        }    
    }
    {
        csvparser in1("../../agregaty/gha/issuevent/issues_graf.csv", ';');
        in1.next();
        while (in1.next()) {
            repos[in1[4]][2] = 1;
        }    
    }
        {
        csvparser in1("../../agregaty/gha/starevent/starring_graf.csv", ';');
        in1.next();
        while (in1.next()) {
            string repo = tolower(in1[5]) + "/" + tolower(in1[4]);
            repos[repo][2] = 1;
        }    
    }

    int scrap_all=0;
    int scrap_uniq = 0;
    int ght_all=0;
    int ght_uniq = 0;
    int gha_all=0;
    int gha_uniq = 0;

    for (auto& repo: repos) {
        if (repo.second[0] == 1) {
            scrap_all++;
        }
        if (repo.second[1] == 1) {
            ght_all++;
        }
        if (repo.second[2] == 1) {
            gha_all++;
        }
        if (repo.second[0] == 1 && repo.second[1]== 0 && repo.second[2]==0) {
            scrap_uniq++;
        }
        if (repo.second[0] == 0 && repo.second[1]== 1 && repo.second[2]==0) {
            ght_uniq++;
        }
        if (repo.second[0] == 0 && repo.second[1]== 0 && repo.second[2]==1) {
            gha_uniq++;
        }
    }
    cout <<"Scrap_all: " <<scrap_all <<" Scrap_uniq: " <<scrap_uniq <<"\n";
    cout <<"GHT_all: " <<ght_all <<" GHT_uniq: " <<ght_uniq <<"\n";
    cout <<"GHA_all: " <<gha_all <<" GHA_uniq: " <<gha_uniq <<"\n";
}

