#!/bin/zsh

month=$1
day=$2

# pierwszy argument to liczba dni
# drugi argument to miesiac
# trzeci argument to dzien

function gharchive_wget() {
    if [[ $2 -lt 10 ]]; then
        for j in `seq $3 $1`; do
            if [[ $j -lt 10 ]]; then
                wget http://data.githubarchive.org/2016-0$2-0$j-{0..23}.json.gz
            else
                wget http://data.githubarchive.org/2016-0$2-$j-{0..23}.json.gz
            fi;
        done;
    else
         for j in `seq $3 $1`; do
            if [[ $j -lt 10 ]]; then 
                wget http://data.githubarchive.org/2016-$2-0$j-{0..23}.json.gz
            else
                wget http://data.githubarchive.org/2016-$2-$j-{0..23}.json.gz
            fi;
         done;         
    fi;
}

# pierwszy argument to miesiac
# drugi argument to dzien

function identify_month() {
if [[ $1 -eq 4 ]] || [[ $1 -eq 6 ]] || [[ $1 -eq 9 ]] || [[ $1 -eq 11 ]]; then
        gharchive_wget 30 $1 $2
    elif [[ $month -eq 2 ]]; then
        gharchive_wget 29 $1 $2
    else
        gharchive_wget 31 $1 $2
fi;

}    

function grep_events() {
    for f in *.json.gz; do
        gunzip $f
    done;
    for f in *json; do
        grep '"type":"FollowEvent"' <$f >>following16
        grep '"type":"ForkEvent"' <$f >>forking16
        grep '"type":"IssuesEvent"' <$f >>issues16
        grep '"type":"PullRequestEvent"' <$f >>pullrequests16
        grep '"type":"WatchEvent"' <$f >>starring16
    done;
    rm *json;
}

# dociagniecie brakow z miesiaca

identify_month $month $day
grep_events
month=$[month+1]

for i in `seq $month 12`; do
    identify_month $i 1
    grep_events
done;
