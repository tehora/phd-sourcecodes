import csv
import argparse
import pycld2

#i = 1

import sys
maxInt = sys.maxsize
decrement = True

while decrement:
    # decrease the maxInt value by factor 10 
    # as long as the OverflowError occurs.

    decrement = False
    try:
        csv.field_size_limit(maxInt)
    except OverflowError:
        maxInt = int(maxInt/10)
        decrement = True

# read the arguments
argument_parser = argparse.ArgumentParser(description="Detecting language for csv files")
argument_parser.add_argument("in_file", help="a file with language to detect")
argument_parser.add_argument("out_file", help="an output file")
args = vars(argument_parser.parse_args())

with open(args["out_file"], "w") as out:
    with open(args["in_file"]) as file:
        reader = csv.reader(file,delimiter=";")
        writer = csv.writer(out, delimiter=";")
        for line in reader:
            #print('%d' % i)
            detectedLang, detectedCode, details = pycld2.detect(line[1].encode('utf-8'))
            writer.writerow([line[0], line[1], details[0][0]])
            #i = i+1

