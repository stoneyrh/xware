#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import sys

def increase_build_number(file_name, delta = 1):
    if os.path.exists(file_name):
        file = open(file_name, 'r')
        contents = file.read()
        file.close()
        m = re.search('(BUILD_VALUE)(\s+)(\d+)', contents)
        if m:
            name, space, value = m.groups()
            value = int(value)
            value = value + delta
            definition = '#define %s%s%d' % (name, space, value)
            lines = contents.split('\n')
            contents = []
            for line in lines:
                if line.find('BUILD_VALUE') >= 0:
                    contents.append(definition)
                else:
                    contents.append(line)
            file = open(file_name, 'w')
            file.write('\n'.join(contents))
            file.close()
            sys.exit(0)
        else:
            pass
    else:
        print file_name + ' does not exits'
    sys.exit(-1)
 
def main():
    if len(sys.argv) < 2:
        print 'Usage: xbuild_number <file>'
    else:
        file_name = sys.argv[1]
        increase_build_number(file_name)

if __name__ == '__main__':
    main()
