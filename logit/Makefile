AG = ../../agregaty
BIN = ../../bin

all: $(AG)/logit/logit-omit.out $(AG)/logit/logit-trunc.out

test: $(BIN)/logit/logit
	$(BIN)/logit/logit

$(BIN)/logit/tabela: tabela.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/logit/tabela.csv: $(BIN)/logit/tabela
	./$^

$(BIN)/logit/logit: logit.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3 -Wall

$(AG)/logit/logit-omit.out: $(BIN)/logit/logit $(AG)/logit/tabela.txt
	$(BIN)/logit/logit >$@

$(AG)/logit/logit-trunc.out: $(BIN)/logit/logit $(AG)/logit/tabela.txt
	$(BIN)/logit/logit cut >$@

logit-result.txt: logit.py $(AG)/logit/tabela.csv
	python logit.py $(AG)/logit/tabela.csv > $@

logit-pr-result.txt: logit.py $(AG)/logit/tabela_pr.csv
	python logit.py $(AG)/logit/tabela_pr.csv > $@
