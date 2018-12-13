AG = ../../agregaty
BIN = ../../bin

all: $(AG)/graph_combine/forking_graf_laczny.csv $(AG)/graph_combine/forking_graf_laczny_crawl.csv $(AG)/graph_combine/following_graf_laczny.csv $(AG)/graph_combine/following_graf_laczny_crawl.csv $(AG)/graph_combine/starring_graf_laczny.csv $(AG)/graph_combine/issues_graf_laczny.csv $(AG)/graph_combine/pull_graf_laczny.csv $(AG)/graph_combine/comments_graf_laczny.csv


# ISSUES

$(BIN)/graph_combine/daty_issue: daty_issue.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/graph_combine/issues_graf_laczny.csv: $(BIN)/graph_combine/daty_issue $(AG)/gha/issuevent/issues_graf.csv $(AG)/ght/issues_graf_ght_full.csv
	./$(BIN)/graph_combine/daty_issue $(AG)/ght/issues_graf_ght_full.csv $(AG)/gha/issuevent/issues_graf.csv $@

# ISSUES_COMMENTS

$(BIN)/graph_combine/daty_comments: daty_comments.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/graph_combine/comments_graf_laczny.csv: $(BIN)/graph_combine/daty_comments $(AG)/gha/commentevent/comments_graf.csv $(AG)/ght/comments_graf_ght.csv
	./$(BIN)/graph_combine/daty_comments $(AG)/ght/comments_graf_ght.csv $(AG)/gha/commentevent/comments_graf.csv $@


# PULLREQUESTS

$(BIN)/graph_combine/daty_pull: daty_pull.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/pull_graf_laczny.csv: $(AG)/ght/pull_graf_ght.csv $(AG)/gha/pullevent/pull_graf.csv $(BIN)/graph_combine/daty_pull
	touch $(AG)/graph_combine/zgubione.txt
	./$(BIN)/graph_combine/daty_pull $(AG)/ght/pull_graf_ght.csv $(AG)/gha/pullevent/pull_graf.csv $(AG)/graph_combine/zgubione.txt /dev/null
	./$(BIN)/graph_combine/daty_pull $(AG)/ght/pull_graf_ght.csv $(AG)/gha/pullevent/pull_graf.csv $(AG)/graph_combine/zgubione.txt $@
	rm $(AG)/graph_combine/zgubione.txt

# FORKING

$(BIN)/graph_combine/daty_fork: daty_fork.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/forking_graf_laczny.csv: $(AG)/ght/forking_graf_ght.csv $(AG)/gha/forkevent/forking_graf.csv $(BIN)/graph_combine/daty_fork
	 ./$(BIN)/graph_combine/daty_fork $(AG)/ght/forking_graf_ght.csv $(AG)/gha/forkevent/forking_graf.csv $@

$(BIN)/graph_combine/fork_crawl: fork_crawl.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(BIN)/graph_combine/pull_fix: nonprior_fork.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/forking_graf_laczny_crawl.csv: $(BIN)/graph_combine/fork_crawl $(BIN)/graph_combine/pull_fix  $(AG)/crawl/forking/forking_graf_crawl.csv $(AG)/graph_combine/forking_graf_laczny.csv
	./$(BIN)/graph_combine/fork_crawl $(AG)/graph_combine/forking_graf_laczny.csv $(AG)/crawl/forking/forking_graf_crawl.csv forking.csv
	./$(BIN)/graph_combine/pull_fix forking.csv $(AG)/graph_combine/pull_graf_laczny.csv $@
	cat forking.csv >>$@
	rm forking.csv

# STARRING
$(BIN)/graph_combine/daty_star: daty_star.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/starring_graf_laczny.csv: $(AG)/ght/starring_graf_ght.csv $(AG)/gha/starevent/starring_graf.csv $(BIN)/graph_combine/daty_star
	 ./$(BIN)/graph_combine/daty_star $(AG)/ght/starring_graf_ght.csv $(AG)/gha/starevent/starring_graf.csv $@

# FOLLOWING
$(BIN)/graph_combine/daty_follow: daty_follow.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/following_graf_laczny.csv: $(AG)/ght/following_graf_ght.csv $(AG)/gha/follevent/following_graf.csv $(BIN)/graph_combine/daty_follow
	 ./$(BIN)/graph_combine/daty_follow $(AG)/ght/following_graf_ght.csv $(AG)/gha/follevent/following_graf.csv $@

$(BIN)/graph_combine/follow_crawl: follow_crawl.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/graph_combine/following_graf_laczny_crawl.csv: $(BIN)/graph_combine/follow_crawl $(AG)/crawl/following/following_graf_crawl.csv $(AG)/graph_combine/following_graf_laczny.csv
	./$(BIN)/graph_combine/follow_crawl $(AG)/graph_combine/following_graf_laczny.csv $(AG)/crawl/following/following_graf_crawl.csv $@
