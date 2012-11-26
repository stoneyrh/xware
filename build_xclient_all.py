#!/usr/bin/env python
import os
import sys

commands = [
        'scons -f xclient.scons unicode=yes release=no',
        'scons -f xclient.scons unicode=no release=no',
        'scons -f xclient.scons unicode=yes release=yes',
        'scons -f xclient.scons unicode=no release=yes']

if __name__ == '__main__':
    for command in commands:
        os.system(' '.join([command] + sys.argv[1:]))
