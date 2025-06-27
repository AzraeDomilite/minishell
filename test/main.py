#!/usr/bin/env python
import os
import shutil
from test_suites.ReadLines import EOF1
from test_suites.Easy import Easy
from test_suites.Env import Environnement
from test_suites.Echo import Echo
from test_suites.Awk import Awk

RESULTS_FOLDER = "results"

test_suites = [Easy(), EOF1(), Environnement(), Echo(), Awk()]

if __name__ == "__main__":
    if os.path.exists(RESULTS_FOLDER):
        shutil.rmtree(RESULTS_FOLDER)
    os.mkdir(RESULTS_FOLDER)

    print("Three OKs/KOs per test case:")
    print("\t1 - stdout, stderr and files in test folder")
    print("\t2 - return code of shell, return code of last command and timeout/segfault")
    print("\t3 - memory leaks and open file handlers", end="")

    total_score = 0
    for suite in test_suites:
        suite.initialise_test_suite_folder(RESULTS_FOLDER)
        total_score += suite.run_test_cases()

    print("\n")
    # if (total_score) > 0:
    #     print("Some tests failed.")
    # else:
    #     print("All tests succeeded.")