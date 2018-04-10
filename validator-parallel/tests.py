#!/usr/bin/env python3
"""
Generare teste in functie de sursa corecta.
It is done in parallel using multiprocessing, as tests have no time limit and just have to be generated as fast as possible.
"""
import os
import sys
import subprocess
import shutil
import multiprocessing
import concurrent.futures
from pathlib import Path
from common import cpp_compile, run_source, official_source_name, problem_name, temp_in, temp_out, gen_name

def gen(test: int) -> None:
    print("Generating test {}".format(test))
    ARGS = TESTS[test].split()

    os.makedirs(Path(temp_in(test)).parent, exist_ok=True)
    os.makedirs(Path(temp_out(official_source_name(), test)).parent, exist_ok=True)

    subprocess.check_call(["./"+gen_name()] + ARGS, stdout=open(temp_in(test), "w"))
    print("Done generating in for {}".format(test), flush=True)

    print("Running {} for {}".format(official_source_name(),test), flush=True)
    if run_source(official_source_name(), test, True) == False:
        print("Source error on test {}".format(test))
        exit(1)

    testno = "./teste/%d-" % test
    subprocess.check_call(["cp", temp_in(test), testno+problem_name()+".in"])
    subprocess.check_call(["cp", temp_out(official_source_name(), test), testno+problem_name()+".ok"])
    print("Done generating ok for {}".format(test), flush=True)

if __name__ == '__main__':
    cpp_compile(official_source_name())
    try:
        shutil.rmtree('./tmp', ignore_errors=False)
        shutil.rmtree('/tmp/gen', ignore_errors=False)
    except:
        pass
    os.mkdir('./tmp')

    TESTS = [line.strip() for line in open("./teste/teste.txt") if len(line.strip()) > 0 and line.strip()[0] != '#']
    try:
        futs = []
        with concurrent.futures.ProcessPoolExecutor() as executor:
            for i in range(len(TESTS)):
                futs.append(executor.submit(gen, i))

            for f in futs:
                f.result()
    except KeyboardInterrupt:
        print('Caught C-c. Goodbye...')
        os.kill(0, 9)
