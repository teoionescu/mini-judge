import os
import subprocess
import shutil
from common import problem_name
#generat teste in fct de sursa corecta


if __name__ == '__main__':
    try:
        shutil.rmtree('./tmp', ignore_errors=False)
    except:
        pass
    os.mkdir('./tmp')

    TESTS = [line.strip() for line in open("./teste/teste.txt") if len(line.strip()) > 0 and line.strip()[0] != '#']
    for test in range(len(TESTS)):
        print("Test %d:" % test)
        ARGS = TESTS[test].split()

        print("  Generating ...................... ", end="")
        subprocess.check_call(["./gen"] + ARGS, stdout=open("./tmp/"+problem_name()+".in", "w"))
        print("Done")

        testno = "./teste/%d-" % test
        subprocess.check_call(["cp", "./tmp/"+problem_name()+".in", testno+problem_name()+".in"])
        subprocess.check_call(["touch", testno+problem_name()+".ok"])
        print("Done")