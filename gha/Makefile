AG = ../../agregaty
RAW = ../../rawdata
BIN = ../../bin

all: $(AG)/gha/nodes_gharchive.csv

# FOLLOWING

$(AG)/gha/follevent/following1.csv $(AG)/gha/follevent/following2.csv: $(RAW)/gha/following12 $(RAW)/gha/following13
	jq -R -r "include \"./events\"; foll" $^

$(AG)/gha/follevent/following_graf.csv: $(AG)/gha/follevent/following1.csv $(AG)/gha/follevent/following2.csv
	echo "created_at;source_id;source_login;source_gravatar;target_id;target_login;target_gravatar" > $@
	cat $^ >> $@

# STARRING

$(AG)/gha/starevent/starring1.csv $(AG)/gha/starevent/starring2.csv $(AG)/gha/starevent/starring3.csv $(AG)/gha/starevent/starring4.csv: $(RAW)/gha/starring12 $(RAW)/gha/starring13 $(RAW)/gha/starring14 $(RAW)/gha/starring15 $(RAW)/gha/starring16 $(RAW)/gha/starring_braki
	jq -R -r "include \"./events\"; star" $^

$(AG)/gha/starevent/starring1a.csv: $(AG)/gha/starevent/starring1.csv
	sort $^ | uniq >s1
	sed -s "s:^\(.*\);\(.*\);\(.*\);\(.*\);\(.*\)/\(.*\);;\(.*\)$$:\1;\2;\3;\4;\6;\5;\7:" < s1 > $@
	rm s1

$(AG)/gha/starevent/starring3a.csv: $(AG)/gha/starevent/starring3.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/starevent/starring3b.csv
	sed -s "s:^\(.*\);\(.*\);;;\(.*\);\(.*\)/\(.*\);$$:\1;\2;;;\3;\4;:" < $(AG)/gha/starevent/starring3b.csv > $@
	rm $(AG)/gha/starevent/starring3b.csv

$(AG)/gha/starevent/starring4a.csv: $(AG)/gha/starevent/starring4.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/starevent/starring4b.csv
	sed -s "s:^\(.*\);\(.*\);\(.*\);;\(.*\)/\(.*\);;$$:\1;\2;\3;;\5;\4;:" < $(AG)/gha/starevent/starring4b.csv > $@
	rm $(AG)/gha/starevent/starring4b.csv

$(AG)/gha/starevent/starring_graf.csv: $(AG)/gha/starevent/starring1a.csv $(AG)/gha/starevent/starring2.csv $(AG)/gha/starevent/starring3a.csv $(AG)/gha/starevent/starring4a.csv
	echo "created_at;source_login;source_gravatar;source_id;repo;target_login;org" > $@
	cat $^ >> $@

# FORKING

$(AG)/gha/forkevent/forking1.csv $(AG)/gha/forkevent/forking2.csv $(AG)/gha/forkevent/forking3.csv $(AG)/gha/forkevent/forking4.csv: $(RAW)/gha/forking12 $(RAW)/gha/forking13 $(RAW)/gha/forking14 $(RAW)/gha/forking15 $(RAW)/gha/forking16 $(RAW)/gha/forking_braki
	jq -R -r "include \"./events\"; fork" $^

$(AG)/gha/forkevent/bledy_forking: $(RAW)/gha/forking12 $(RAW)/gha/forking13 $(RAW)/gha/forking13_app $(RAW)/gha/forking14 $(RAW)/gha/forking15
	jq -R -r ". as \$$x | try (fromjson|empty) catch \$$x" $^ > $@

$(AG)/gha/forkevent/forking1a.csv: $(AG)/gha/forkevent/forking1.csv
	sort $^ | uniq >f1
	sed -s "s:^\(.*\);\(.*\);\(.*\);\(.*\);\(.*\)/\(.*\);;\(.*\)$$:\1;\2;\3;\4;\6;\5;\7:" < f1 > $@
	rm f1

$(AG)/gha/forkevent/forking_graf.csv: $(AG)/gha/forkevent/forking1a.csv $(AG)/gha/forkevent/forking2.csv $(AG)/gha/forkevent/forking3.csv $(AG)/gha/forkevent/forking4.csv
	echo "created_at;source_login;source_gravatar;source_id;repo;target_login;org" > $@; \
	cat $^ >> $@

# ISSUES

$(AG)/gha/issuevent/issues1.csv $(AG)/gha/issuevent/issues2.csv $(AG)/gha/issuevent/issues3.csv $(AG)/gha/issuevent/issues4.csv : $(RAW)/gha/issues12 $(RAW)/gha/issues13 $(RAW)/gha/issues13_app $(RAW)/gha/issues14 $(RAW)/gha/issues15 $(RAW)/gha/issues16 $(RAW)/gha/issues_braki
	jq -R -r "include \"./events\"; issues" $^

$(AG)/gha/issuevent/bledy_issues: $(RAW)/gha/issues12 $(RAW)/gha/issues13 $(RAW)/gha/issues13_app $(RAW)/gha/issues14 $(RAW)/gha/issues15
	jq -R -r ". as \$$x | try (fromjson|empty) catch \$$x" $^ > $@

$(AG)/gha/issuevent/issues1a.csv: $(AG)/gha/issuevent/issues1.csv
	sort $^ | uniq >is1
	sed -s "s:^\(.*\);\(.*\);\(.*\);\(.*\);\(.*\)/\(.*\);;\(.*\);\(.*\);\(.*\)$$:\1;\2;\3;\4;\6;\5;\7;\8;\9:" < is1 > $@
	rm is1 

$(AG)/gha/issuevent/issues3a.csv: $(AG)/gha/issuevent/issues3.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/issuevent/issues3b.csv
	sed "s|/issues/[0-9]\+||" < $(AG)/gha/issuevent/issues3b.csv > $(AG)/gha/issuevent/issues3c.csv
	sed -s "s:^\(.*\);\(.*\);;;\(.*\);\(.*\)/\(.*\);;\(.*\);\(.*\)$$:\1;\2;;;\3;\4;;\6;\7:" < $(AG)/gha/issuevent/issues3c.csv > $@
	rm $(AG)/gha/issuevent/issues3c.csv $(AG)/gha/issuevent/issues3b.csv

$(AG)/gha/issuevent/issues4a.csv: $(AG)/gha/issuevent/issues4.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/issuevent/issues4b.csv
	sed "s|/issues/[0-9]\+||" < $(AG)/gha/issuevent/issues4b.csv > $(AG)/gha/issuevent/issues4c.csv
	sed -s "s:^\(.*\);\(.*\);\(.*\);;\(.*\)/\(.*\);;;\(.*\);\(.*\)$$:\1;\2;\3;;\5;\4;;\6;\7:" < $(AG)/gha/issuevent/issues4c.csv > $@
	rm $(AG)/gha/issuevent/issues4c.csv $(AG)/gha/issuevent/issues4b.csv

$(AG)/gha/issuevent/issues_graf1.csv: $(AG)/gha/issuevent/issues1a.csv $(AG)/gha/issuevent/issues2.csv $(AG)/gha/issuevent/issues3a.csv $(AG)/gha/issuevent/issues4a.csv
	echo "created_at;source_login;source_gravatar;source_id;repo;target_login;org;action;issue_id" > $@
	cat $^ >> $@

$(AG)/gha/issuevent/issues_graf.csv: $(AG)/gha/issuevent/issues_graf1.csv
	grep -v ";.*/" < $^ > sporne
	awk -F ";" '{print $$1";"$$2";"$$3";"$$4";"$$6"/"$$5";"$$6";"$$7";"$$8";"$$9}' <sporne > $@
	grep ";.*/" < $^ >> $@
	rm sporne

# ISSUES_COMMENTS

testclean: $(RAW)/gha/comments15
	cat $^ | head -n 100000 | grep "stop the clean" -A 25 -B 25 > testclean

test: testclean
	cat $^ | sed -e 's|\\n||g' -e 's|\\u0000||g' -e 's|\\r| |g' -e 's|\\t||g' -e 's|;||g' -e 's|\\"||g' | jq -R -r "include \"./events\"; commentstest"

$(AG)/gha/commentevent/comments1.csv $(AG)/gha/commentevent/comments2.csv $(AG)/gha/commentevent/comments3.csv $(AG)/gha/commentevent/comments4.csv $(AG)/gha/commentevent/orig_comments1.csv $(AG)/gha/commentevent/orig_titles1.csv  : $(RAW)/gha/comments12 $(RAW)/gha/comments13 $(RAW)/gha/comments14 $(RAW)/gha/comments15  $(RAW)/gha/comments16 $(RAW)/gha/comments_braki
	cat $^ | sed -e 's|\\n| |g' -e 's|\\u0000| |g' -e 's|\\r| |g' -e 's|\\t| |g' -e 's|;| |g' -e 's|\\"| |g' -e 's|| |g' | jq -R -r "include \"./events\"; comments"
#jq -R -r "include \"./events\"; orig_comments" $^
#jq -R -r "include \"./events\"; orig_titles" $^

$(AG)/gha/commentevent/comments1a.csv: $(AG)/gha/commentevent/comments1.csv
	sort -T ../../tmp/ $^ | uniq >com1
	sed -s "s:^\(.*\);\(.*\);\(.*\);\(.*\);\(.*\)/\(.*\);;\(.*\);\(.*\);\(.*\)$$:\1;\2;\3;\4;\6;\5;\7;\8;\9:" < com1 > $@
	rm com1 

$(AG)/gha/commentevent/comments3a.csv: $(AG)/gha/commentevent/comments3.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/commentevent/comments3b.csv
	sed "s|/issues/[0-9]\+#issuecomment-|;|" < $(AG)/gha/commentevent/comments3b.csv > $(AG)/gha/commentevent/comments3c.csv
	sed -s "s:^\(.*\);\(.*\);;;\(.*\);\(.*\)/\(.*\);\(.*\);;;null$$:\1;\2;;;\3;\4;;;:" < $(AG)/gha/commentevent/comments3c.csv > $@
	rm $(AG)/gha/commentevent/comments3c.csv $(AG)/gha/commentevent/comments3b.csv

$(AG)/gha/commentevent/comments4a.csv: $(AG)/gha/commentevent/comments4.csv
	sed "s|https://github.com/||" < $^ > $(AG)/gha/commentevent/comments4b.csv
	sed "s|/issues/[0-9]\+#issuecomment-|;|" < $(AG)/gha/commentevent/comments4b.csv > $(AG)/gha/commentevent/comments4c.csv
	sed -s "s:^\(.*\);\(.*\);\(.*\);;\(.*\)/\(.*\);\(.*\);;;;\(.*\)$$:\1;\2;\3;;\5;\4;;;\7:" < $(AG)/gha/commentevent/comments4c.csv > $@
	rm $(AG)/gha/commentevent/comments4c.csv $(AG)/gha/commentevent/comments4b.csv

$(AG)/gha/commentevent/comments_graf1.csv: $(AG)/gha/commentevent/comments1a.csv $(AG)/gha/commentevent/comments2.csv $(AG)/gha/commentevent/comments3a.csv $(AG)/gha/commentevent/comments4a.csv
	echo "created_at;source_login;source_gravatar;source_id;repo;target_login;org;comment;comment_id" > $@
	cat $^ >> $@

$(AG)/gha/commentevent/comments_graf.csv: $(AG)/gha/commentevent/comments_graf1.csv
	#grep -v ";.*/" < $^ > sporne
	awk -F ";" '{print $$1";"$$2";"$$3";"$$4";"$$6"/"$$5";"$$6";"$$7";"$$8";"$$9}' <$^ > $@
	#grep ";.*/" < $^ >> $@
	#rm sporne

$(AG)/gha/bodyissues/body1.csv: $(RAW)/gha/issues12 $(RAW)/gha/issues13 $(RAW)/gha/issues14 $(RAW)/gha/issues15  $(RAW)/gha/issues16 $(RAW)/issues_braki
	cat $^ | sed -e 's|\\n| |g' -e 's|\\u0000| |g' -e 's|\\r| |g' -e 's|\\t| |g' -e 's|;| |g' -e 's|\\"| |g' -e 's|| |g' | jq -R -r "include \"./events\"; isbody"


# PULLREQUESTS

$(AG)/gha/pullevent/pulls1.csv $(AG)/gha/pullevent/pulls2.csv $(AG)/gha/pullevent/pulls3.csv: $(RAW)/gha/pullrequests12 $(RAW)/gha/pullrequests13 $(RAW)/gha/pullrequests14 $(RAW)/gha/pullrequests15 $(RAW)/gha/pullrequests16 $(RAW)/gha/pullrequests_braki
	jq -R -r "include \"./events\"; pulls" $^

$(AG)/gha/pullevent/pulls1a.csv: $(AG)/gha/pullevent/pulls1.csv
	sort -T /mnt/tmp $^ | uniq >$@

$(AG)/gha/pullevent/bledy_pulls: $(RAW)/gha/pullrequests12 $(RAW)/gha/pullrequests13 $(RAW)/gha/pullrequests14 $(RAW)/gha/pullrequests15
	jq -R -r ". as \$$x | try (fromjson|empty) catch \$$x" $^ > $@

$(AG)/gha/pullevent/pull_graf1.csv: $(AG)/gha/pullevent/pulls1a.csv $(AG)/gha/pullevent/pulls2.csv $(AG)/gha/pullevent/pulls3.csv
	echo "created_at;source_login;source_gravatar;source_id;repo;target_login;target_id;target_gravatar;org;action;pull_id;deletions;additions;commmits;changed_files;merged_at" > $@
	cat $^ >> $@

$(AG)/gha/pullevent/pull_graf2.csv: $(AG)/gha/pullevent/pull_graf1.csv
	grep -v ";.*/" < $^ | awk -F ";" '{print $$1";"$$2";"$$3";"$$4";"$$6"/"$$5";"$$6";"$$7";"$$8";"$$9";"$$10";"$$11";"$$12";"$$13";"$$14";"$$15";"$$16}' > $@
	grep ";.*/" < $^ >> $@

$(AG)/gha/pullevent/pull_merge.csv: $(BIN)/gha/find_merged_pulls $(AG)/gha/pullevent/pull_graf2.csv
	./$(BIN)/gha/find_merged_pulls

$(BIN)/gha/find_merged_pulls: find_merged_pulls.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/gha/pullevent/pull_graf.csv: $(AG)/gha/pullevent/pull_graf2.csv $(AG)/gha/pullevent/pull_merge.csv
	cat $^ > $@

# ZBIOR OSOB

# login / id / gravatar

$(AG)/gha/nodes_gharchive.csv: $(AG)/gha/follevent/following_graf.csv $(AG)/gha/starevent/starring_graf.csv $(AG)/gha/forkevent/forking_graf.csv $(AG)/gha/issuevent/issues_graf.csv $(AG)/gha/pullevent/pull_graf.csv $(AG)/gha/commentevent/comments_graf.csv
	echo "typ;login_gha;id_gha;gravatar_gha" >$@
	awk -F ";" '{print "fs;"$$3";"$$2";"$$4}' <$(AG)/gha/follevent/following_graf.csv >>$@
	awk -F ";" '{print "ft;"$$6";"$$5";"$$7}' <$(AG)/gha/follevent/following_graf.csv >>$@
	awk -F ";" '{print "ss;"$$2";"$$4";"$$3}' <$(AG)/gha/starevent/starring_graf.csv >>$@
	awk -F ";" '{print "st;"$$6";"";"}' <$(AG)/gha/starevent/starring_graf.csv >>$@
	awk -F ";" '{print "fks;"$$2";"$$4";"$$3}' <$(AG)/gha/forkevent/forking_graf.csv >>$@
	awk -F ";" '{print "fkt;"$$6";"";"}' <$(AG)/gha/forkevent/forking_graf.csv >>$@
	awk -F ";" '{print "is;"$$2";"$$4";"$$3}' <$(AG)/gha/issuevent/issues_graf.csv >>$@
	awk -F ";" '{print "it;"$$6";"";"}' <$(AG)/gha/issuevent/issues_graf.csv >>$@
	awk -F ";" '{print "ps;"$$2";"$$4";"$$3}' <$(AG)/gha/pullevent/pull_graf.csv >>$@
	awk -F ";" '{print "pt;"$$6";"$$7";"$$8}' <$(AG)/gha/pullevent/pull_graf.csv >>$@
	awk -F ";" '{print "cs;"$$2";"$$4";"$$3}' <$(AG)/gha/commentevent/comments_graf.csv >>$@
	awk -F ";" '{print "ct;"$$6";"";"}' <$(AG)/gha/commentevent/comments_graf.csv >>$@

$(BIN)/gha/id-dla-loginow: id-dla-loginow.cpp csv2.h
	g++ id-dla-loginow.cpp -o id-dla-loginow -O3

$(AG)/gha/nodes_wyniki.txt: $(BIN)/gha/id-dla-loginow ../$(AG)/gha/nodes_gharchive.csv
	./$(BIN)/gha/id-dla-loginow > $@

#$(BIN)/gha/merger: merger.cpp
#	g++ $^ -o $@ -I/mnt/src/ -g

#$(AG)/gha/statystyki.csv $(AG)/gha/ktoto.csv: $(BIN)/gha/merger $(AG)/gha/nodes_gharchive.csv
#	./$(BIN)/gha/merger
