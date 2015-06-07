
import os
import sys

if __name__ == '__main__':
    if len(sys.argv) <= 1:
        print "usage: %s <file>" % sys.argv[0]
        exit(1)

    f_handler = open(sys.argv[1], 'r')
    index = 0
    for l in f_handler.xreadlines():
        row_data = l.strip().split(',')
        for item in row_data:
            print "8'h%02X: data <= 8'h%s;" % (index, format(int(item,16), '02X')),
            index += 1
        print ""
