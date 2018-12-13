DIR=.
/home/tehora/potwory/nogit/rogueviz/hyper \
-s xx -lab -svgsize 4000/5 -svgfont latex -svggamma 1 -qpar 13 -canvas 100010 -geo 5 \
-somtmax 300000 -somlearn 0.01 \
-som $DIR/kohonen-data.txt \
-color $DIR/color.csv \
-somloadw $DIR/kohonen-columns.txt \
-somrun --run -somfinish \
-somsave $DIR/neurons.txt \
-somclassify $DIR/classify.txt \
-somlistbest $DIR/samples-best.txt \
-somlistbestc $DIR/samples-color.txt \
-somlistshown $DIR/samples-shown.txt \
-somsavew $DIR/column-weights.txt

