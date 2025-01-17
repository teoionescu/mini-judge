import os
import subprocess
import shutil

def problem_name():
    return "camp"

def time_limit():
    return 0.4

def official_source_name():
    return "piro"

def compile_gen():
    print("Compiling generator ... ", end="")
    try:
        subprocess.check_output(["g++", "-O2", "-Wall", "-std=c++11", "gen.cpp", "-o", "gen", "-lm"], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("Compile error:")
        print(e.output)
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

def run_source(source):
    try:
        shutil.rmtree('./tmp/current')
    except:
        pass
    os.mkdir("./tmp/current")
    subprocess.check_call(["cp", "./surse/" + source, "./tmp/current/" + source])
    subprocess.check_call(["cp", "./tmp/"+problem_name()+".in", "./tmp/current/"+problem_name()+".in"])
    os.chdir("./tmp/current")
    try:
        subprocess.check_call(["./" + source], timeout=time_limit())
    except:
        os.chdir("../../")
        return False
    os.chdir("../../")
    subprocess.check_call(["cp", "./tmp/current/"+problem_name()+".out", "./tmp/" + source + ".out"])
    shutil.rmtree("./tmp/current")
    return True

def score(source):
    if subprocess.call(["diff", "-w", "./tmp/" + source + ".out", "./tmp/"+problem_name()+".ok"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL):
        return 0
    return 5

