#!/usr/bin/env python3
import os
import subprocess
import shutil
from pathlib import Path

def problem_name():
    return "countfefete"

def time_limit():
    return 2

def official_source_name():
    return "piro_100"

def problem_type():
    from enum import Enum
    class ProblemType(Enum):
        STANDARD = "standard"
        VERIF = "verif"
        #MULTIRUN = "multirun"
    return ProblemType.STANDARD.value

def gen_name():
    return "gen_{}".format(os.uname()[0][0:2])

def compile_gen():
    print("Compiling generator ... ", end="")
    try:
        subprocess.check_output(["g++", "-O2", "-Wall", "-std=c++11", "gen.cpp", "-o", gen_name(), "-lm"], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("Compile error:")
        print(e.output)
    print("Done")

def compile_validator():
    try:
        Validator = [entry.name[:-4] for entry in os.scandir('./validator') if entry.is_file() and entry.name[-4:] == '.cpp']
    except:
        return
    if Validator:
        print("Compiling validator ... ", end="")
        try:
            os.chdir("./validator")
            subprocess.check_output(["g++", "-O2", "-Wall", "-std=c++11", "./%s.cpp" % Validator[0], "-o", "validator", "-lm"], stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:
            os.chdir("../")
            print("Compile error:")
            print(e.output)
        os.chdir("../")
        print("Done")

def get_sources():
    return [entry.name[:-4] for entry in os.scandir('./surse') if entry.is_file() and entry.name[-4:] == '.cpp']

def cpp_compile(source):
    print("Compiling %s ... " % source, end="")
    try:
        subprocess.check_output(["g++", "-O2", "-Wall", "-std=c++11", "./surse/" + source + ".cpp", "-o", "./surse/" + source, "-lm"], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("Compile error:")
        print(e.output)
    print("Done")

def compile_all():
     for source in get_sources():
        cpp_compile(source)

def temp_in(test: int) -> str:
    ret = '/tmp/gen/{}/{}.in'.format(test, problem_name())
    os.makedirs(Path(ret).parent, exist_ok=True)
    return ret

def temp_out(source:str, test: int) -> str:
    ret = '/tmp/gen/{}/{}/{}.out'.format(source, test, problem_name())
    os.makedirs(Path(ret).parent, exist_ok=True)
    return ret

def temp_ok(test: int) -> str:
    ret = '/tmp/gen/{}/{}.ok'.format(test, problem_name())
    os.makedirs(Path(ret).parent, exist_ok=True)
    return ret

def run_source(source: str, test: int, verbose=False):
    tmp_current = "./tmp/{}/{}/".format(source, test)
    try:
        shutil.rmtree(tmp_current)
    except:
        pass

    os.makedirs(tmp_current)
    subprocess.check_call(["cp", "./surse/" + source, tmp_current + source])
    subprocess.check_call(["cp", temp_in(test), tmp_current + problem_name() + ".in"])

    try:
        subprocess.check_call(["./" + source], timeout=time_limit(), cwd=tmp_current)
    except Exception as e:
        if verbose:
            print("{ " + str(e) + " } -> ", end='')
        return False

    subprocess.check_call(["cp", tmp_current + problem_name() + ".out", temp_out(source, test)])
    return True

def score_verif(source, test):
    subprocess.check_call(["cp", temp_in(test), "./validator/"+problem_name()+".in"])
    subprocess.check_call(["cp", temp_ok(test), "./validator/"+problem_name()+".ok"])
    subprocess.check_call(["cp", temp_out(source, test), "./validator/"+problem_name()+".out"])
    try:
        proc = subprocess.Popen(["./validator"], stdout=subprocess.PIPE, cwd="./validator")
        score, *message = proc.stdout.read().split()
        if int(score) == 10:
            return 5
        else:
            print("_".join(map(lambda m: str(m,"utf-8"), message)) + "(\"{}\",test-{})".format(source, test))
            return 0
    except Exception as e:
        print("Failed to run validator: " + str(e))

def score(source, test):
    if problem_type() == "verif":
        return score_verif(source, test)

    if subprocess.call(["diff", "-w", temp_out(source, test), temp_ok(test)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL):
        return 0
    return 5
