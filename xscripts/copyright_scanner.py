#!/usr/bin/env python
import os

copyRight = '''/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright      *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      *
* * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        *
* * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    *
* * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
* * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    *
* * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    *
* * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
* * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
* * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    *
* * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     *
* *                                                                          *
* * Author: stoneyrh@163.com                                                 *
* *                                                                          *
* ****************************************************************************
*/

'''
def insertCopyRight(name):
    file = open(name, 'r')
    content = file.read()
    file.close()
    file = open(name, 'w')
    content = copyRight + content
    file.write(content)
    file.close()

def walk(walkOnly, dirname, fnames):
    if dirname.find('GeneratedFiles') >= 0:
        return
    careExts = ['.cpp', '.cc', '.h', '.mm', '.m']
    for fname in fnames:
        ext = os.path.splitext(fname)[1]
        if ext in careExts:
            name = os.path.join(dirname, fname)
            file = open(name, 'r')
            firstLine = file.readline()
            file.close()
            if not firstLine.startswith('/*'):
                if not walkOnly:
                    print 'Handling ', name, '...'
                    insertCopyRight(name)
                else:
                    print name, ' needs handling.'

if __name__ == '__main__':
    import sys
    argc = len(sys.argv)
    root = '.'
    if argc >= 2:
        root = sys.argv[1]
    walkOnly = True
    if argc >= 3:
        arg = sys.argv[2].lower()
        if arg.startswith('n') or arg.startswith('f'):
            walkOnly = False
    os.path.walk(root, walk, walkOnly)
