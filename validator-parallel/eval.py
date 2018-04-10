#!/usr/bin/env python3
import os
import subprocess
import shutil
import random
import argparse
from common import get_sources, run_source, score, compile_all, cpp_compile, problem_name, temp_in, temp_out, temp_ok, gen_name
TEST_IDX = 'eval' # Special value as to not interfere with normal test generation.

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Get scores')
    parser.add_argument('people', type=str, nargs='*')
    parser.add_argument('--all', dest='all', action='store_true')
    args = parser.parse_args()
    if not args.all and args.people == []:
        parser.print_help()
        exit(0)
    Sources = get_sources()
    if not args.all:
        Sources = list(set(Sources) & set(args.people))
    for source in Sources:
        cpp_compile(source)

    TESTS = 10000
    MAXN = 10
    MAXV = 10**9

    try:
        shutil.rmtree('./tmp', ignore_errors=False)
    except:
        pass
    os.mkdir('./tmp')

    for test in range(1, TESTS + 1):
        print("Case #%d: " % test, end="")

        N = random.randint(2, MAXN)
        subprocess.check_call(["./"+gen_name(), str(N), str(MAXV)], stdout=open(temp_in(TEST_IDX), "w"))

        for source in Sources:
            if run_source(source, TEST_IDX, True) == False:
                print("Runtime error on %s" % source)
                exit(1)

        subprocess.check_call(["cp", temp_out(Sources[0], TEST_IDX), temp_ok(TEST_IDX)])

        for source in Sources:
            if score(source, TEST_IDX) != 5:
                print("Wrong answer: %s" % source)
                exit(1)
        print("OK")
