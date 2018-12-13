AG = ../../agregaty
BIN = ../../bin
RAW = ../../rawdata

all: $(AG)/users_char/owner_repo_laczne.csv $(AG)/users_char/owner_number_repo.csv $(AG)/users_char/owner_number_lang.csv $(AG)/users_char/user_forked.csv $(AG)/users_char/user_forked_pulls.csv $(AG)/users_char/user_forking_others.csv $(AG)/users_char/user_stars_laczne.csv $(AG)/users_char/user_information.csv $(AG)/users_char/user_follow_laczne.csv $(AG)/users_char/user_comments.csv $(AG)/users_char/user_issues_opened.csv $(AG)/users_char/user_number_forks.csv

#all: $(AG)/users_char/user_follow_laczne.csv  $(AG)/users_char/user_information.csv

# combining repositories from ght and web-scraper

$(BIN)/repo_merge: repo_merge_ght_crawl.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/owner_repo_laczne.csv: $(AG)/ght/owner_repo_ght.csv $(AG)/crawl/owner_repo_crawl.csv $(BIN)/repo_merge
	./$(BIN)/repo_merge $(AG)/ght/owner_repo_ght.csv $(AG)/crawl/owner_repo_crawl.csv $@

# user -- number of repositories

$(BIN)/users_char/owner_number: owner_number_repo.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/owner_number_repo.csv: $(BIN)/users_char/owner_number $(AG)/users_char/owner_repo_laczne.csv $(AG)/crawl/owner_norepos_crawl.csv
	./$(BIN)/users_char/owner_number $(AG)/users_char/owner_repo_laczne.csv $(AG)/crawl/owner_norepos_crawl.csv $@

# user -- number of own repositoried forked by others 

$(BIN)/users_char/owner_forkedrepos: owner_number_forked.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/owner_number_forkedrepos.csv: $(BIN)/users_char/owner_forkedrepos $(AG)/users_char/owner_repo_laczne.csv $(AG)/crawl/owner_norepos_crawl.csv
	./$(BIN)/users_char/owner_forkedrepos $(AG)/users_char/owner_repo_laczne.csv $(AG)/crawl/owner_norepos_crawl.csv $@

# user -- languages used

$(BIN)/users_char/owner_lang: owner_lang.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/owner_number_lang.csv: $(BIN)/users_char/owner_lang $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/project_languages1.csv $(AG)/users_char/owner_repo_laczne.csv
	./$(BIN)/users_char/owner_lang $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/project_languages1.csv $(AG)/users_char/owner_repo_laczne.csv $@

# user -- forked + forked_pulls; forking others

$(BIN)/users_char/owner_forked: owner_forked.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_forked.csv: $(BIN)/users_char/owner_forked $(AG)/graph_combine/forking_graf_laczny_crawl.csv
	./$(BIN)/users_char/owner_forked $(AG)/graph_combine/forking_graf_laczny_crawl.csv $@

$(BIN)/users_char/owner_pulls: owner_forked_pulls.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_forked_pulls.csv: $(BIN)/users_char/owner_pulls $(AG)/users_char/owner_repo_laczne.csv $(AG)/graph_combine/forking_graf_laczny_crawl.csv $(AG)/graph_combine/pull_graf_laczny.csv
	./$(BIN)/users_char/owner_pulls $(AG)/users_char/owner_repo_laczne.csv $(AG)/graph_combine/forking_graf_laczny_crawl.csv $(AG)/graph_combine/pull_graf_laczny.csv $@

$(BIN)/users_char/forking_others: forking_others.cpp 
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_forking_others.csv: $(BIN)/users_char/forking_others $(AG)/graph_combine/forking_graf_laczny_crawl.csv $(AG)/users_char/owner_repo_laczne.csv
	./$(BIN)/users_char/forking_others $(AG)/graph_combine/forking_graf_laczny_crawl.csv $(AG)/users_char/owner_repo_laczne.csv $@

$(BIN)/users_char/number_forks: owner_number_forks.cpp 
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_number_forks.csv: $(BIN)/users_char/number_forks $(AG)/graph_combine/forking_graf_laczny_crawl.csv
	./$(BIN)/users_char/number_forks $(AG)/graph_combine/forking_graf_laczny_crawl.csv $@

# user -- stars obtained/given

$(BIN)/users_char/owner_stars: owner_stars.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_stars_laczne.csv: $(BIN)/users_char/owner_stars  $(AG)/graph_combine/starring_graf_laczny.csv $(AG)/crawl/user_starsobtained_crawl.csv $(AG)/crawl/user_starsgiven_crawl.csv owner_stars.cpp
	./$(BIN)/users_char/owner_stars  $(AG)/graph_combine/starring_graf_laczny.csv $(AG)/crawl/user_starsobtained_crawl.csv $(AG)/crawl/user_starsgiven_crawl.csv $@

# user -- issues opened in others' projects/own projects
$(BIN)/users_char/issues_opened: issues_opened.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_issues_opened.csv: $(BIN)/users_char/issues_opened  $(AG)/graph_combine/issues_graf_laczny.csv
	./$(BIN)/users_char/issues_opened $(AG)/graph_combine/issues_graf_laczny.csv $@

# user -- comments in other's projects/own projects
$(BIN)/users_char/user_comments: user_comments.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_comments.csv: $(BIN)/users_char/user_comments  $(AG)/graph_combine/comments_graf_laczny.csv
	./$(BIN)/users_char/user_comments $(AG)/graph_combine/comments_graf_laczny.csv $@

# user -- information (site, email,...)

$(BIN)/users_char/user_info: user_information.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_information.csv: $(BIN)/users_char/user_info $(RAW)/crawl/users/*
	./$(BIN)/users_char/user_info $@

# user -- following and followers
$(BIN)/users_char/user_follow: user_follow_graf.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/users_char/user_follow_laczne.csv: $(BIN)/users_char/user_follow $(AG)/graph_combine/following_graf_laczny.csv $(AG)/crawl/user_follow_crawl.csv 
	./$(BIN)/users_char/user_follow $(AG)/graph_combine/following_graf_laczny.csv $(AG)/crawl/user_follow_crawl.csv $@
