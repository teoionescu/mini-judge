#!/usr/bin/env python3
import os
import subprocess
import shutil
import tabulate
import argparse
from common import cpp_compile, get_sources, problem_name, time_limit
from sys import stdout

def compile_prepare(source):
    print("Compiling %s ... " % source, end="")
    try:
        subprocess.check_output(["g++", "-O2", "-Wall", "-std=c++11", "./prepare/" + source + ".cpp", "-o", "./prepare/" + source, "-lm"], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("Compile error:")
        print(e.output)
    print("Done")

def run_source_smen(source):
    print("Running %s.................. " % source, end="")
    try:
        shutil.rmtree('./tmp/current')
    except:
        pass
    os.mkdir("./tmp/current")
    subprocess.check_call(["cp", "./surse/" + source, "./tmp/current/" + source])
    subprocess.check_call(["cp", "./prepare/prepare0", "./tmp/prepare0"])
    subprocess.check_call(["cp", "./prepare/prepare1", "./tmp/prepare1"])
    subprocess.check_call(["cp", "./prepare/verif", "./tmp/verif"])

    os.chdir("./tmp")
    try:
        subprocess.check_call(["./prepare0"], timeout=10)
    except:
        os.chdir("../")
        print("Exception-1")
        return False
    os.chdir("../")


    subprocess.check_call(["cp", "./tmp/"+problem_name()+".in.0", "./tmp/current/"+problem_name()+".in"])


    os.chdir("./tmp/current")
    try:
        subprocess.check_call(["./" + source], timeout=time_limit())
    except:
        os.chdir("../../")
        print("Exception-2")
        return False
    os.chdir("../../")


    subprocess.check_call(["cp", "./tmp/current/"+problem_name()+".out", "./tmp/"+problem_name()+".out.0"])


    os.chdir("./tmp")
    try:
        subprocess.check_call(["./prepare1"], timeout=10)
    except:
        os.chdir("../")
        print("Exception-3")
        return False
    os.chdir("../")

    subprocess.check_call(["cp", "./tmp/"+problem_name()+".in.1", "./tmp/current/"+problem_name()+".in"])


    os.chdir("./tmp/current")
    try:
        subprocess.check_call(["./" + source], timeout=time_limit())
    except:
        os.chdir("../../")
        print("Exception-4")
        return False
    os.chdir("../../")


    subprocess.check_call(["cp", "./tmp/current/"+problem_name()+".out", "./tmp/"+problem_name()+".out.1"])

    os.chdir("./tmp")
    try:
        process = subprocess.Popen("./verif", stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out = process.stdout.readline()
        print("Mesaj Verif: %s" % out)
        optr = [int(s) for s in out.split() if s.isdigit()]
        result = open("op.ok", "w+")
        result.write("%s" % optr[0])
        result.close()
    except:
        os.chdir("../")
        print("Exception-5")
        return False
    os.chdir("../")

    shutil.rmtree("./tmp/current")
    return True

def score_smen(source):
    fp = open("./tmp/op.ok")
    result = 0
    for line in fp:
        data = line.split()
        result = int(data[0])
    return result

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

    # initialize ./tmp folder
    try:
        shutil.rmtree('./tmp', ignore_errors=False)
    except:
        pass
    os.mkdir('./tmp')

    TESTS = [test.name[:-3] for test in os.scandir('./teste') if test.name[-3:] == '.in']
    SCORES = {source: 0 for source in SOURCES}
    RESULTS = {source: [] for source in SOURCES}

    compile_prepare("prepare0");
    compile_prepare("prepare1");
    compile_prepare("verif");

    for test in range(len(TESTS)):
        print(".", end="")
        stdout.flush()
        subprocess.check_call(["cp", "./teste/" + str(test) + "-"+problem_name()+".in", "./tmp/"+problem_name()+".in"])
        #subprocess.check_call(["cp", "./teste/" + str(test) + "-"+problem_name()+".ok", "./tmp/"+problem_name()+".ok"])

        for source in SOURCES:
            if run_source_smen(source) == False:
                RESULTS[source] += ['X']
            else:
                #subprocess.check_call(["cp", "./tmp/" + source + ".out", "./tmp/"+problem_name()+".out"])
                s = score_smen(source)
                RESULTS[source] += [str(s)]
                SCORES[source] += s
    print()
    SCORES = [[name, score] for name, score in SCORES.items()]
    RESULTS = [[name] + results for name, results in RESULTS.items()]

    print(tabulate.tabulate(SCORES, ["Nume", "Scor"], tablefmt="grid"))
    print(tabulate.tabulate(RESULTS, ["Nume"] + list(range(len(TESTS))), tablefmt="grid"))
