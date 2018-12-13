AG = ../../agregaty
BIN = ../../bin

all: $(AG)/langs/lang_edges.csv

$(BIN)/langs/lang_edges: lang_edges.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3

$(AG)/langs/lang_edges.csv: $(BIN)/langs/lang_edges $(AG)/users_char/owner_number_lang.csv
	$(BIN)/langs/lang_edges $(AG)/users_char/owner_number_lang.csv $@ $(AG)/langs/lang_freq.csv
