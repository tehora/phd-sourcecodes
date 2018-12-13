AG = ../../agregaty
BIN = ../../bin
RAW = ../../rawdata

all: $(AG)/language_det/*.detected.csv

$(BIN)/language_det/user_desc: users_description.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/language_det/users_description.csv: $(BIN)/language_det/user_desc $(RAW)/ght/users.csv $(RAW)/ght/projects.csv
	./$(BIN)/language_det/user_desc $(RAW)/ght/users.csv $(RAW)/ght/projects.csv | sed -e 's| ;)| :wink: |g' -e 's| ;(| :cry: |g' | grep -v ';\\N'| grep -v ';$$' | ./clean.sh >$@

$(BIN)/language_det/commits_body: commits_body.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/language_det/commit_comments.csv: $(BIN)/language_det/commits_body $(RAW)/ght/users.csv $(RAW)/ght/commit_comments.csv
	./$(BIN)/language_det/commits_body $(RAW)/ght/users.csv $(RAW)/ght/commit_comments.csv 2 3 | sed -e 's| ;)| :wink: |g' -e 's| ;(| :cry: |g' -e 's|;|:|g' | sed 's/|&&&&"/;"/' | ./clean.sh > $@

$(AG)/language_det/issue_comments.csv: $(AG)/gha/commentevent/comments1.csv
	awk -F ";" '{print $$2"|&&&&"$$8}' <$^ |  sed -e 's| ;)| :wink: |g' -e 's| ;(| :cry: |g' -e 's|;|:|g' | sed 's/|&&&&/;/' | ./clean.sh > $@

$(AG)/language_det/issue_bodies.csv: $(AG)/gha/bodyissues/body1.csv
	awk -F ";" '{print $$2"|&&&&"$$5}' <$^ |  sed -e 's| ;)| :wink: |g' -e 's| ;(| :cry: |g' -e 's| ;-)| :wink: |g' -e 's|;-(| :cry: |g' -e 's|;|:|g' | sed 's/|&&&&/;/' | ./clean.sh > $@

$(AG)/language_det/pull_comments.csv: $(BIN)/language_det/commits_body $(RAW)/ght/users.csv $(RAW)/ght/pull_request_comments.csv
	./$(BIN)/language_det/commits_body $(RAW)/ght/users.csv $(RAW)/ght/pull_request_comments.csv 1 4 | sed -e 's| ;)| :wink: |g' -e 's| ;(| :cry: |g' -e 's|;|:|g' | sed 's/|&&&&"/;"/' | ./clean.sh > $@

$(AG)/language_det/user_lang_detected.csv: language_detector.py $(AG)/language_det/users_description.csv
	python language_detector.py $(AG)/language_det/users_description.csv $@

$(AG)/language_det/commit_lang_detected.csv: language_detector.py $(AG)/language_det/commit_comments.csv
	python language_detector.py $(AG)/language_det/commit_comments.csv $@

$(AG)/language_det/pull_lang_detected.csv: language_detector.py $(AG)/language_det/pull_comments.csv
	python language_detector.py $(AG)/language_det/pull_comments.csv $@

$(AG)/language_det/issue_lang_detected.csv: language_detector.py $(AG)/language_det/issue_comments.csv
	python language_detector.py $(AG)/language_det/issue_comments.csv $@

$(AG)/language_det/bodies_lang_detected.csv: language_detector.py $(AG)/language_det/issue_bodies.csv
	python language_detector.py $(AG)/language_det/issue_bodies.csv $@

