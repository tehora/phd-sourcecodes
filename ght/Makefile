AG = ../../agregaty
BIN = ../../bin
RAW = ../../rawdata

#all: $(AG)/ght/following_graf_ght.csv $(AG)/ght/forking_graf_ght.csv $(AG)/ght/starring_graf_ght.csv $(AG)/ght/issues_graf_ght_full.csv $(AG)/ght/pull_graf_ght.csv $(AG)/ght/owner_repo_ght.csv
all: $(RAW)/ght/project_languages1.csv

# FOLLOWERS

$(BIN)/ght/followers: followers.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/following_graf_ght.csv: $(RAW)/ght/users.csv $(RAW)/ght/followers.csv $(BIN)/ght/followers
	./$(BIN)/ght/followers $(RAW)/ght/users.csv $(RAW)/ght/followers.csv $@

# FORKING

$(BIN)/ght/forking: forking.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/forking_graf_ght.csv: $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(BIN)/ght/forking
	./$(BIN)/ght/forking $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $@

# STARRING

$(BIN)/ght/starring: starring.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/starring_graf_ght.csv: $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/watchers.csv $(BIN)/ght/starring
	./$(BIN)/ght/starring $(RAW)/ght/users.csv $(RAW)/ght/projects.csv  $(RAW)/ght/watchers.csv $@

# ISSUES

#$(RAW)/ght/isevent.csv: $(RAW)/ght/issue_events.csv
#	mv $^ $@

$(BIN)/ght/issues: issues.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/issues_graf_ght_full.csv: $(BIN)/ght/issues $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/issues.csv $(RAW)/ght/isevent.csv
	./$(BIN)/ght/issues $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/issues.csv $(RAW)/ght/isevent.csv $@

# ISSUES_COMMENTS

$(BIN)/ght/comments: comments.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/comments_graf_ght.csv: $(BIN)/ght/comments $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/issues.csv $(RAW)/ght/issue_comments.csv
	./$(BIN)/ght/comments $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/issues.csv $(RAW)/ght/issue_comments.csv $@

# PULLREQUESTS

$(BIN)/ght/pullrequests: pullrequests.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/ght/pull_graf_ght.csv: $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/pull_requests.csv $(RAW)/ght/pull_request_history.csv $(BIN)/ght/pullrequests
	./$(BIN)/ght/pullrequests $(RAW)/ght/users.csv $(RAW)/ght/projects.csv $(RAW)/ght/pull_requests.csv $(RAW)/ght/pull_request_history.csv $@


# rrepozytoria z ght

$(BIN)/ght/repo_extract: repo_ght.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src -O3

$(AG)/ght/owner_repo_ght.csv: $(BIN)/ght/repo_extract $(RAW)/ght/users.csv $(RAW)/ght/projects.csv
	./$(BIN)/ght/repo_extract $(RAW)/ght/users.csv $(RAW)/ght/projects.csv owner_repo_ght1.csv
	sed "s/ //g" <owner_repo_ght1.csv >repo1
	sed "s/Objective-/Objective/g" <repo1 >repo2
	sed "s/DCPU-/DCPU/g" <repo2 >repo1
	sed "s/Modula-2/Modula2/g" <repo1 >repo2
	sed "s/-RaySDL/RaySDL/g" <repo2 >repo1
	sed "s/Cap'n/Capn/g" <repo1 > repo2
	sed "s:Max/MSP:MaxMSP:g" <repo2 >repo1
	sed "s/Ren'Py/Renpy/g" <repo1 >$@
	rm repo1 repo2 owner_repo_ght1.csv

$(RAW)/ght/project_languages1.csv: $(RAW)/ght/project_languages.csv
	sed "s/ //g" <$^ >repo1
	sed "s/objective-/objective/g" <repo1 >repo2
	sed "s/dcpu-/dcpu/g" <repo2 >repo1
	sed "s/modula-2/modula2/g" <repo1 >repo2
	sed "s/-raysdl/raysdl/g" <repo2 >repo1
	sed "s/cap'n/capn/g" <repo1 > repo2
	sed "s:max/msp:maxmsp:g" <repo2 >repo1
	sed "s/ren'py/renpy/g" <repo1 >$@
	rm repo1 repo2
