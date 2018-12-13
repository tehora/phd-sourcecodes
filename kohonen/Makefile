DIR=.
GEO?=-qpar 13 -geo 5
HYPER?=rogueviz/hyper -nogui -s xx -lab -svgsize 4000/5 -svgfont latex -svggamma 1 -canvas 100010 $(GEO)

all: classify.txt

tabela: tabela.cpp
	g++ tabela.cpp -o tabela -O3 -I ..

kohonen-data.txt kohonen-columns.txt: tabela
	./tabela
        
classify.txt:
	make classify

classify: kohonen-data.txt
	$(HYPER) \
	-som $(DIR)/kohonen-data.txt \
	-color $(DIR)/color.csv \
	-somloadw $(DIR)/kohonen-columns.txt \
	-somlearn 0.2 -somtmax 300000 \
	-somrun -somfinish \
	-somsave $(DIR)/neurons${PARAM}.txt \
	-somclassify $(DIR)/classify${PARAM}.txt \
	-somlistbest $(DIR)/samples-best.txt \
	-somlistbestc $(DIR)/samples-color.txt \
	-somlistshown $(DIR)/samples-shown.txt \
	-somsavew $(DIR)/column-weights.txt \
	-somndist $(DIR)/neuron-distances.txt \
	-somshowbest

$(DIR)/samples-all.txt: $(DIR)/samples-best.txt $(DIR)/samples-shown.txt
	cat $(DIR)/samples-best.txt $(DIR)/samples-shown.txt > $(DIR)/samples-all.txt

view: $(DIR)/samples-all.txt
	$(HYPER) \
        -som $(DIR)/samples-all.txt \
	-color $(DIR)/color.csv \
	-somload $(DIR)/neurons.txt \
	-somloadw $(DIR)/column-weights.txt

viewall: $(DIR)/samples-all.txt
	$(HYPER) \
        -som $(DIR)/kohonen-data.txt \
	-color $(DIR)/color.csv \
	-color $(DIR)/samples-color.txt \
	-somload $(DIR)/neurons.txt \
	-somloadw $(DIR)/column-weights.txt

