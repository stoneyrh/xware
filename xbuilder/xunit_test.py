#!/bin/env python
"""
Builder for building test program
"""

import os
import subprocess
from SCons.Builder import Builder
from SCons.Action import Action
from SCons.Script import COMMAND_LINE_TARGETS

def run_unit_test(target,source,env):
    # Turn to string
    program = str(source[0])
    # Get current work directory
    cwd = os.getcwd()
    # Split the path and the program name
    pwd,program = os.path.split(program)
    pwd = os.path.realpath(pwd)
    # CD to pwd
    os.chdir(pwd)
    # Get the result file name
    filename = os.path.basename(str(target[0]))
    # Extra library file path
    extra_lib_path = []
    if env.has_key('TEST_LIB_PATH'):
        extra_lib_path = env.subst(env['TEST_LIB_PATH'])
        # Get absolute path for each element
        extra_lib_path = map(lambda p:env.Dir(p).get_abspath(),extra_lib_path)
    # Set the LD_LIBRARY_PATH on non-windows platform
    if not env.IsWindows():
        path = []
        try:
            path = os.environ['LD_LIBRARY_PATH']
            path = path.split(os.pathsep)
        except:
            pass
        path.append(pwd)
        if len(extra_lib_path):
            path += extra_lib_path
        os.environ['LD_LIBRARY_PATH'] = os.pathsep.join(path)
    # Set PATH on windows platform
    else:
        path = []
        try:
            path = os.environ['PATH']
            path = path.split(os.pathsep)
        except:
            pass
        path.append(pwd)
        if len(extra_lib_path):
            path += extra_lib_path
        os.environ['PATH'] = os.pathsep.join(path)
    # Run the test program in the program file directory
    if env.IsWindows():
        command = program
    else:
        command = './%s' % program
    file = open(filename,'w')
    if env.IsDebuggingUnitTest():
        if env.IsWindows():
            command = 'devenv /debugexe %s' % command
        else:
            command = 'gdb %s' % command
        returncode = subprocess.call(command.split(),cwd = pwd)
    else:
        returncode = subprocess.call(command.split(),stdout = file,stderr = file,cwd = pwd)
    file.close()
    if returncode == 0:
        print ' ' * 10 + 'PASSED'
    else:
        # Print out the content if fail
        file = open(filename, 'r')
        print file.read()
        file.close()
        print ' ' * 10 + 'FAILED'
    os.chdir(cwd)
    return returncode

def add_alias(func):
    def alias_it(target,source,env):
        target,source = func(target,source,env)
        env.Alias('test',target)
        # Normally, the target should end with 'test_result.txt'
        alias = 'test' + str(target[0]).replace('test_result.txt','')
        env.Alias(alias,target)
        return target,source
    return alias_it

def clean_if_test(func):
    def clean_target_if_test(*args,**kwargs):
        target,source = func(*args,**kwargs)
        result = str(target[0])
        if 'test' in COMMAND_LINE_TARGETS:
            if os.path.exists(result):
                os.remove(result)
        return target,source
    return clean_target_if_test

@add_alias
#@clean_if_test
def append_result_to_target(target,source,env):
    appendix = '_result'
    def do_append(name):
        name = str(name)
        base,ext = os.path.splitext(name)
        if not base.endswith(appendix):
            base += appendix
        return base + ext
    return map(do_append,target),source

def run_unit_test_desc(target, source, env):
    column_count = 80
    head_and_tail = '=' * column_count
    content = 'Running ' + os.path.splitext(os.path.basename(str(source[0])))[0]
    lines = [head_and_tail, content, head_and_tail]
    return '\n'.join(lines)

_run_unit_test = Action(run_unit_test, run_unit_test_desc)
RunUnitTest = Builder(action = _run_unit_test,suffix = '.txt', emitter = append_result_to_target)

class Collector(object):
    def __init__(self):
        self.files = []

    def Append(self, file):
        if isinstance(file, (list, tuple)):
            self.files.extend([str(item) for item in file])
        else:
            self.files.append(str(file))

    def GetFiles(self):
        return self.files

def collect_unit_test(target, source, env):
    file = open(str(target[0]), 'w')
    # Count how many unit tests we have
    total            = 0
    not_finished_cnt = 0
    error_cnt        = 0
    import re
    running = re.compile('Running (\d*) tests')
    flag    = re.compile('<--NOT IMPLEMENTED TEST-->')
    error   = re.compile('ERROR errorLogger')
    for s in source:
        content = open(str(s), 'r').read()
        counters = running.findall(content)
        for c in counters:
            total += int(c)
        flags  = flag.findall(content)
        errors = error.findall(content)
        not_finished_cnt += len(flags)
        error_cnt += len(errors)
        file.write('[' + str(s) + ']\n' + content)
    appendix = '-' * 80 + '\n[SUMMARY]Totally, there are %d tests' % total
    if not_finished_cnt > 0:
        appendix += ', but %d not finished.' % not_finished_cnt
    if error_cnt > 0:
        appendix += '\nThere are some error information output from error logger, please make sure they are output as you expect'
    file.write('\n' + appendix)
    file.close()

def get_unit_test_result(target, source, env):
    if env.has_key('COLLECTOR'):
        return target, env['COLLECTOR'].GetFiles()
    return target, source

_collect_unit_test = Action(collect_unit_test, 'Collecting unit test result...')
CollectUnitTest = Builder(action = _collect_unit_test, suffix = '.txt', src_suffix = '.txt', emitter = get_unit_test_result)
