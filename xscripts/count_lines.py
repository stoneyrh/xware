#!/usr/bin/env python

import os
import glob

exts = ['*.h', '*.cpp', '*.cc', '*.mm']

def count_dir(dir):
    count = 0
    for ext in exts:
        names = glob.glob(os.path.join(dir, ext))
        for name in names:
            file = open(name, 'r')
            count += len(file.readlines())
    return count

def count_dirs(dirs):
    count = 0
    for dir in dirs:
        for root, subs, files in os.walk(dir):
            count += count_dir(root)
    return count

def main():
    import sys
    print 'Total number of lines = ', count_dirs(sys.argv[1:])

if __name__ == '__main__':
    main()
