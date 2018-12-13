AG = ../../agregaty
BIN = ../../bin
RAW = ../../rawdata

all: $(AG)/crawl/user_follow_crawl.csv

#FOLLOWING
$(AG)/crawl/following/following_graf_crawl.csv: $(RAW)/crawl/following/following*
	cat $(RAW)/crawl/following/1falafollowing.csv $(RAW)/crawl/following/2falafollowing.csv >>following
	for x in $^; do \
		sed -s 's|^\(.*\)//\(.*\)/\(.*\)/\(.*\),/\(.*\)$$|\3;\5|' <$$x >>following; \
	done;
	sort following | uniq >$@
	rm following

#FORKING

$(AG)/crawl/forking/forking_odwroc.csv: $(RAW)/crawl/forking/members2111.csv $(RAW)/crawl/forking/members2211.csv
	cat $^ >laczne
	sort laczne | uniq -d >podwojne
	sort laczne | uniq -u >pojedyncze
	cat podwojne pojedyncze >$@
	rm podwojne pojedyncze laczne

$(BIN)/crawl/fork: fork.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/forking/forking_cat.csv: $(RAW)/crawl/forking/members2_full.csv $(RAW)/crawl/forking/members2_0603a.csv $(RAW)/crawl/forking/members2_0603.csv $(RAW)/crawl/forking/members2_2002.csv
	cat $^ >$@

$(AG)/crawl/forking/forking_a.csv: $(BIN)/crawl/fork $(AG)/crawl/forking/forking_odwroc.csv $(AG)/crawl/forking/forking_cat.csv
	./$(BIN)/crawl/fork $(AG)/crawl/forking/forking_odwroc.csv $(AG)/crawl/forking/forking_cat.csv $@

$(AG)/crawl/forking/forking_graf_crawl.csv: $(AG)/crawl/forking/forking_a.csv
	sort $^ | uniq -d >podwojne
	sort $^ | uniq -u >pojedyncze
	cat podwojne pojedyncze >$@
	rm podwojne pojedyncze

# REPOZYTORIA

$(BIN)/crawl/repo_crawl: repo_crawl.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/owner_repo_unsorted.csv: $(BIN)/crawl/repo_crawl
	./$(BIN)/crawl/repo_crawl $@

$(BIN)/crawl/cudzyslowy: cudzyslowy.c
	gcc $^ -o $@

$(AG)/crawl/owner_repo_crawl.csv: $(AG)/crawl/owner_repo_unsorted.csv
	sort $(AG)/crawl/owner_repo_unsorted.csv | sed "s/,//g" > repos
	uniq -u < repos > unikat
	uniq -d < repos > duplikat
	cat unikat duplikat > $(AG)/crawl/owner_repo_uniq.csv
	rm unikat duplikat repos
	sed -s "s:^\(.*\);/\(.*\)/\(.*\);\(.*\);\(.*\)$$:\1;\3;\4;\5:" <$(AG)/crawl/owner_repo_uniq.csv >$@
	rm $(AG)/crawl/owner_repo_uniq.csv

$(AG)/crawl/owner_norepos_crawl.csv: $(RAW)/crawl/repozytoria/brak_repo/brak_repo0704.csv $(RAW)/crawl/repozytoria/brak_repo/brak_repo1704a.csv $(RAW)/crawl/repozytoria/brak_repo/brak_repo1704.csv $(RAW)/crawl/repozytoria/brak_repo/zbior_norepos_crawl.csv
	cat $^ > braki
	grep "have any public repositories yet" <braki >braki1
	sed -s "s:^\(.*\),\(.*\)/\(.*\)/\(.*\)?\(.*\)$$:0,\4:" <braki1 >braki2
	sed -s "s:^,\(.*\)/\(.*\)/\(.*\)?\(.*\)$$:0,\3:" <$(RAW)/crawl/repozytoria/brak_repo/braki_2009.csv >braki3
	cat braki3 braki2 $(RAW)/crawl/repozytoria/brak_repo/zbior_norepos_crawl.csv >$@
	rm braki1 braki braki2 braki3

# STARS: GIVEN / OBTAINED

$(BIN)/crawl/stars_obtained: user_stars_obtained.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/crawl/user_starsobtained_crawl.csv: $(BIN)/crawl/stars_obtained $(RAW)/crawl/repozytoria
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
