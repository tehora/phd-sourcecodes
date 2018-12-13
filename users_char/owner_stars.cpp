#include <ghutils.h>
#include <map>

map <string, pair<int, int> > user_stars;

int main(int argc, char **argv) {

    //pierwsze jest stars_obtained; drugie stars_given
    
    csvparser in1(argv[1],';');
    
    while (in1.next()) {
        user_stars[in1[1]].second++;
        user_stars[in1[3]].first++;
    }
    
    csvparser in2(argv[2], ';');
    while (in2.next()) {
        if (user_stars[in2[0]].first < tonum(in2[1])) {
            user_stars[in2[0]].first = tonum(in2[1]);

        }
    }

    csvparser in3(argv[3], ';');
    while (in3.next()) {
        if (user_stars[in3[0]].second < tonum(in3[1])) {
            user_stars[in3[0]].second = tonum(in3[1]);

        }
    } 

    ofstream of1(argv[4]);
    
    of1 <<"user;stars_obtained;stars_given" << endl;
    
    for ( auto& user_star: user_stars) {
        of1 << user_star.first << ";" << user_star.second.first << ";" << user_star.second.second << endl;
    }    

}    
