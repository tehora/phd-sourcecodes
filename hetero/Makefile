AG = ../../agregaty
BIN = ../../bin
SRC = ../../src

all: $(AG)/hetero/projects_people_w.csv

# projects with people

$(BIN)/hetero/proj: projects.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/hetero/projects_people.csv: $(BIN)/hetero/proj $(AG)/laczenie_grafow/comments_graf_laczny.csv $(AG)/laczenie_grafow/issues_graf_laczny.csv $(AG)/laczenie_grafow/pull_graf_laczny.csv $(AG)/users_char/owner_repo_laczne.csv $(AG)/laczenie_grafow/forking_graf_laczny_crawl.csv
	./$(BIN)/hetero/proj aaa.csv
	sed '/^;/d' <aaa.txt | sort -T /mnt/tmp |sed -e 's| |;|' -e 's|\/|;|' > $@

# projects with people weighted

$(BIN)/hetero/proj_agg: projects_agg.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/hetero/projects_people_w.csv: $(BIN)/hetero/proj_agg $(AG)/laczenie_grafow/comments_graf_laczny.csv $(AG)/laczenie_grafow/issues_graf_laczny.csv $(AG)/laczenie_grafow/pull_graf_laczny.csv $(AG)/users_char/owner_repo_laczne.csv $(AG)/laczenie_grafow/forking_graf_laczny_crawl.csv
	./$(BIN)/hetero/proj_agg
	sed '/^;/d' <projects_people_agg.csv | sort -T /mnt/tmp | uniq -c | sed 's|^ \+\([0-9]\)|\1|' | sed -e 's| |;|' -e 's|\/|;|' > $@
#rm projects_people_agg.csv

# average distance in  project
$(BIN)/hetero/avg_dist: avg_dist.cpp ../ghutils.h
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/hetero/avg_distances_w.csv: $(BIN)/hetero/avg_dist $(AG)/hetero/projects_people_w.csv $(SRC)/kohonen/classify.txt $(SRC)/kohonen/neuron-distances.csv
	./$(BIN)/hetero/avg_dist $@
