AG = ../../agregates
BIN = ../../bin
RAW = ../../rawdata

all: $(AG)/crawl/user_follow_crawl.csv

#FOLLOWING
$(AG)/crawl/following/following_graph_crawl.csv: $(RAW)/crawl/following/following*
	cat $(RAW)/crawl/following/1wavefollowing.csv $(RAW)/crawl/following/2wavefollowing.csv >>following
	for x in $^; do \
		sed -s 's|^\(.*\)//\(.*\)/\(.*\)/\(.*\),/\(.*\)$$|\3;\5|' <$$x >>following; \
	done;
	sort following | uniq >$@
	rm following

#FORKING

$(AG)/crawl/forking/forking_rev.csv: $(RAW)/crawl/forking/members2111.csv $(RAW)/crawl/forking/members2211.csv
	cat $^ >merged
	sort merged | uniq -d >duplic
	sort merged | uniq -u >unique
	cat duplic unique >$@
	rm duplic unique merged

$(BIN)/crawl/fork: fork.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/forking/forking_cat.csv: $(RAW)/crawl/forking/members2_full.csv $(RAW)/crawl/forking/members2_0603a.csv $(RAW)/crawl/forking/members2_0603.csv $(RAW)/crawl/forking/members2_2002.csv
	cat $^ >$@

$(AG)/crawl/forking/forking_a.csv: $(BIN)/crawl/fork $(AG)/crawl/forking/forking_odwroc.csv $(AG)/crawl/forking/forking_cat.csv
	./$(BIN)/crawl/fork $(AG)/crawl/forking/forking_odwroc.csv $(AG)/crawl/forking/forking_cat.csv $@

$(AG)/crawl/forking/forking_graph_crawl.csv: $(AG)/crawl/forking/forking_a.csv
	sort $^ | uniq -d >duplic
	sort $^ | uniq -u >unique
	cat duplic unique >$@
	rm duplic unique

# REPOSITORIES

$(BIN)/crawl/repo_crawl: repo_crawl.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/owner_repo_unsorted.csv: $(BIN)/crawl/repo_crawl
	./$(BIN)/crawl/repo_crawl $@

$(BIN)/crawl/quotes: quotes.c
	gcc $^ -o $@

$(AG)/crawl/owner_repo_crawl.csv: $(AG)/crawl/owner_repo_unsorted.csv
	sort $(AG)/crawl/owner_repo_unsorted.csv | sed "s/,//g" > repos
	uniq -u < repos > unique
	uniq -d < repos > duplic
	cat unique duplic > $(AG)/crawl/owner_repo_uniq.csv
	rm unique duplic repos
	sed -s "s:^\(.*\);/\(.*\)/\(.*\);\(.*\);\(.*\)$$:\1;\3;\4;\5:" <$(AG)/crawl/owner_repo_uniq.csv >$@
	rm $(AG)/crawl/owner_repo_uniq.csv

$(AG)/crawl/owner_norepos_crawl.csv: $(RAW)/crawl/repositories/no_repo/no_repo0704.csv $(RAW)/crawl/repositories/no_repo/no_repo1704a.csv $(RAW)/crawl/repositories/no_repo/no_repo1704.csv $(RAW)/crawl/repositories/no_repo/norepos_crawl.csv
	cat $^ > missings
	grep "have any public repositories yet" <missings >miss1
	sed -s "s:^\(.*\),\(.*\)/\(.*\)/\(.*\)?\(.*\)$$:0,\4:" <miss1 >miss2
	sed -s "s:^,\(.*\)/\(.*\)/\(.*\)?\(.*\)$$:0,\3:" <$(RAW)/crawl/repositories/no_repo/miss_2009.csv >miss3
	cat miss3 miss2 $(RAW)/crawl/repositories/no_repo/norepos_crawl.csv >$@
	rm miss1 missings miss2 miss3

# STARS: GIVEN / OBTAINED

$(BIN)/crawl/stars_obtained: user_stars_obtained.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/user_starsobtained_crawl.csv: $(BIN)/crawl/stars_obtained $(RAW)/crawl/repositories
	./$(BIN)/crawl/stars_obtained $@

$(BIN)/crawl/stars_given: user_stars_given.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/user_starsgiven_crawl.csv: $(BIN)/crawl/stars_given $(RAW)/crawl/users/*
	./$(BIN)/crawl/stars_given $@

# FOLLOWING: IN + OUT DEGREE

$(BIN)/crawl/user_follow: user_follow.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/user_follow_crawl.csv: $(BIN)/crawl/user_follow $(RAW)/crawl/users/*
	./$(BIN)/crawl/user_follow $@
