import os
import sys

commands = [
        'scons unicode=yes release=no',
        'scons unicode=no release=no',
        'scons unicode=yes release=yes',
        'scons unicode=no release=yes']

if __name__ == '__main__':
    for command in commands:
        os.system(' '.join([command] + sys.argv[1:]))
