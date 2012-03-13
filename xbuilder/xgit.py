#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

git = u'git'

def commit(file_name, message = None):
    if not message:
        message = u'commited by xgit.py'
    command = u'%s commit %s -m "%s"' % (git, file_name, message)
    return os.system(command) == 0

def push():
    command = u'%s push' % git
    return os.system(command) == 0

def pull():
    command = u'%s pull' % git
    return os.system(command) == 0

def main():
    if len(sys.argv) < 2:
        print 'Usage: xgit.py <file> [<message>]'
    else:
        file_name = sys.argv[1]
        message = None
        if len(sys.argv) == 3:
            message = sys.argv[2]
        commit(file_name, message)

if __name__ == u'__main__':
    main()
