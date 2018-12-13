#include <ghutils.h>
#include <map>
#include <vector>

// first value -- scraping
// second value -- GHT
// third value -- GHA

map <string, array<int, 3>> users;

int main(int argc, char **argv) {
    //getting users from scraping
    {
        csvparser in1("../../id_eryx.csv", ',');
        in1.next();
        while (in1.next()) {
            if (in1[1]=="user") {
                users[tolower(in1[2])][0] = 1;
            }           
        }    
    }
    {
        csvparser in1("../../agregaty/crawl/following/following_graf_crawl.csv", ';');
        while (in1.next()) {
            users[tolower(in1[1])][0] = 1;
        }    
    }
    {
        csvparser in1("../../agregaty/crawl/forking/forking_graf_crawl.csv", ';');
        while (in1.next()) {
            users[tolower(in1[2])][0] = 1;
        }    
    }
    // getting users from GHT
    {
        csvparser in1("../../rawdata/ght/users.csv", ',');
        while (in1.next()) {
            users[tolower(in1[1])][1] = 1;
        }    
    }
    // getting users from GHA
    {
        csvparser in1("../../agregaty/gha/nodes_gharchive.csv", ';');
        while (in1.next()) {
            users[tolower(in1[1])][2] = 1;
        }    
    }

    int scrap_all=0;
    int scrap_uniq = 0;
    int ght_all=0;
    int ght_uniq = 0;
    int gha_all=0;
    int gha_uniq = 0;

    for (auto& user: users) {
        if (user.second[0] == 1) {
            scrap_all++;
        }
        if (user.second[1] == 1) {
            ght_all++;
        }
        if (user.second[2] == 1) {
            gha_all++;
        }
        if (user.second[0] == 1 && user.second[1]== 0 && user.second[2]==0) {
            scrap_uniq++;
        }
        if (user.second[0] == 0 && user.second[1]== 1 && user.second[2]==0) {
            ght_uniq++;
        }
        if (user.second[0] == 0 && user.second[1]== 0 && user.second[2]==1) {
            gha_uniq++;
        }
    }
    cout <<"Scrap_all: " <<scrap_all <<" Scrap_uniq: " <<scrap_uniq <<"\n";
    cout <<"GHT_all: " <<ght_all <<" GHT_uniq: " <<ght_uniq <<"\n";
    cout <<"GHA_all: " <<gha_all <<" GHA_uniq: " <<gha_uniq <<"\n";
}

