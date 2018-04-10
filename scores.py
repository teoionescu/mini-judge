#!/usr/bin/env python3
import os
import subprocess
import shutil
import tabulate
import argparse
from common import cpp_compile, run_source, get_sources, score, problem_name, temp_in, temp_out, temp_ok
from sys import stdout

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Get scores')
    parser.add_argument('people', type=str, nargs='*')
    parser.add_argument('--all', dest='all', action='store_true')
    args = parser.parse_args()
    if not args.all and args.people == []:
        parser.print_help()
        exit(0)
    SOURCES = get_sources()
    if not args.all:
        SOURCES = list(set(SOURCES) & set(args.people))

    for source in SOURCES:
        cpp_compile(source)

    try:
        shutil.rmtree('./tmp', ignore_errors=False)
    except:
        pass
    os.mkdir('./tmp')

    TESTS = [test.name[:-3] for test in os.scandir('./teste') if test.name[-3:] == '.in']
    SCORES = {source: 0 for source in SOURCES}
    RESULTS = {source: [] for source in SOURCES}
    for test in range(len(TESTS)):
        print(".", end="")
        stdout.flush()
        subprocess.check_call(["cp", "./teste/" + str(test) + "-"+problem_name()+".in", temp_in(test)])
        subprocess.check_call(["cp", "./teste/" + str(test) + "-"+problem_name()+".ok", temp_ok(test)])

        for source in SOURCES:
            if run_source(source, test) == False:
                RESULTS[source] += ['X']
            else:
                s = score(source, test)
                RESULTS[source] += [str(s)]
                SCORES[source] += s
    print()
    SCORES = [[name, score] for name, score in SCORES.items()]
    RESULTS = [[name] + results for name, results in RESULTS.items()]

    print(tabulate.tabulate(SCORES, ["Nume", "Scor"], tablefmt="grid"))
    print(tabulate.tabulate(RESULTS, ["Nume"] + list(range(len(TESTS))), tablefmt="grid"))
