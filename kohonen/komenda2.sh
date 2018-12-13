DIR=.
/home/tehora/potwory/nogit/rogueviz/hyper \
-s xx -lab -svgsize 4000/5 -svgfont latex -svggamma 1 -qpar 13 -canvas 100010 -geo 5 \
-som <(cat $DIR/samples-best.txt $DIR/samples-shown.txt) \
-color $DIR/color.csv \
-somload $DIR/neurons.txt \
-somloadw $DIR/column-weights.txt
