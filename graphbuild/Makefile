AG = ../../agregaty
BIN = ../../bin

all: $(AG)/ktoto.csv

graphbuild: graphbuild.cpp
	g++ graphbuild.cpp -o graphbuild -std=c++0x -O3 -I.

minigraph: minigraph.cpp
	g++ minigraph.cpp -o minigraph -std=c++0x -O3 -I.

$(AG)/ktoto.csv $(AG)/statystyki.csv: $(AG)/gha/nodes_gharchive.csv ../../id_eryx.csv $(BIN)/graphbuild/merge_ktoto
	./$(BIN)/graphbuild/merge_ktoto

$(BIN)/graphbuild/merge_ktoto: merger.cpp
	g++ $^ -o $@ -I/mnt/src/ -O3
