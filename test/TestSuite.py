import os
from subprocess import TimeoutExpired

VALGRIND_LOGFILE="valgrind.log"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --default-suppressions=yes --suppressions=../../../../config/valgrind.supp --log-file=../" + VALGRIND_LOGFILE
DEBUG_LOGFILE="debug.log"

SHELL_A_NAME = "bash"
SHELL_B_NAME = "minishell"
SHELL_A_PATH = "/bin/bash"
SHELL_B_PATH = "../../../../../minishell"

tcolors = {
    "HEADER" : '\033[95m',
    "OKBLUE" : '\033[94m',
    "OKCYAN" : '\033[96m',
    "OKGREEN" : '\033[92m',
    "WARNING" : '\033[93m',
    "FAIL" : '\033[91m',
    "ENDC" : '\033[0m',
    "BOLD" : '\033[1m',
    "UNDERLINE" : '\033[4m'
}

def replace_colors(str):
    for color in tcolors.values():
        str = str.replace(color, "")
    return (str)

import subprocess
from time import sleep

class TestSuite:
    def __init__(self):
        self.check_last_command_return_code = True
        self.timeout = 2
        self.folder = "TestSuite"
        self.files = {
        #   "file": "content"
        }
        self.initrc=""
        # self.initrc ="""
        # chmod 0755 file
        # """
        # self.testcases = [
        # """
        # ls | cat | cat
        # """
        # ]
    
    


    def initialise_test_suite_folder(self, results_folder):
        self.path = os.path.join(results_folder, self.folder)
        os.mkdir(self.path)


    def split_path(self, path):
        path = os.path.normpath(path).split(os.path.sep)
        return path[:-1], path[-1]
    
    def create_path_and_file(self, path, content):
        path, file = self.split_path(path)
        growing = ""
        for folder in path:
            growing += folder + os.path.sep
            if not os.path.exists(growing):
                os.mkdir(growing)

        path = os.path.sep.join(path)
        file_path = os.path.join(path, file)
        if content is None:
            if not os.path.exists(file_path):
                os.mkdir(file_path)
        else:
            with open(file_path, "w") as file:
                file.write(content)

    def initialise_test_case_folder(self, test_case_path):
        lpath, lfile = self.split_path(test_case_path)
        folder = test_case_path
        os.mkdir(folder)
        for filepath, content in self.files.items():
            self.create_path_and_file(os.path.join(folder, filepath), content)
        if self.initrc.strip() != "":
            os.chdir(test_case_path)
            for cmd in self.initrc.strip().split("\n"):
                cmd = cmd.strip()
                os.system(cmd)
                #subprocess.call(cmd.split(" "),timeout=self.timeout)
            os.chdir("../" * (len(lpath) + 1))

        #todo: run init script in folder

    def print_OK_KO(self, case_score):
        print(f"[", end="", flush=True)
        if case_score > 0:
            print(tcolors["FAIL"] + "KO" + tcolors["ENDC"], end="", flush=True)
        else:
            print(tcolors["OKGREEN"] + "OK" + tcolors["ENDC"], end="", flush=True)
        print(f"]", end="", flush=True)

    def run_test_cases(self):
        case_score = 0
        suite_score = 0

        print("\n\nTestsuite", self.folder)
        print("======================")
        for i, case in enumerate(self.test_cases):
            test_case_path = os.path.join(self.path, "test_case_" + str(i))
            os.mkdir(test_case_path)
            ret_shell_a = self.run_test_case(case, test_case_path, SHELL_A_NAME, SHELL_A_PATH)
            ret_shell_b = self.run_test_case(case, test_case_path, SHELL_B_NAME, SHELL_B_PATH, True)
            output_score, return_score, memory_score, case_score = self.analyse_test_case(ret_shell_a, ret_shell_b)
            
            if(i != 0):
                print(" - ", end="", flush=True)
            print(f"{i:02d} ", end="", flush=True)
            self.print_OK_KO(output_score)
            self.print_OK_KO(return_score)
            self.print_OK_KO(memory_score)
            
            suite_score += case_score
        # if (suite_score) > 0:
        #     print("Testsuite", self.folder, "failed.")
        # else:
        #     print("Testsuite", self.folder, "succeeded.")
        return(suite_score)

    def run_test_case(self, case, test_case_path, shell_name, shell_path, run_with_valgrind = False):
        
        folder = os.path.join(test_case_path, shell_name)
        stdout_file = os.path.join("../", shell_name + "_stdout.txt")
        stderr_file = os.path.join("../", shell_name + "_stderr.txt")
        self.initialise_test_case_folder(folder)
        os.chdir(folder)
        cmd = shell_path + " 1>" + stdout_file + " 2>" + stderr_file
        #print("\t\t", cmd)
        segfault = False
        case = case.strip() + "\n"
        if run_with_valgrind:
            p = subprocess.Popen(VALGRIND + " 1>" + stdout_file + " 2>" + stderr_file + " " + shell_path, shell=True, stdin=subprocess.PIPE, stderr=subprocess.PIPE,stdout=subprocess.PIPE, text="true")
        else:
            p = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE, stderr=subprocess.PIPE,stdout=subprocess.PIPE, text="true")
        sleep(0.1)
        try:
            p.stdin.write(case)
            p.stdin.flush()
            sleep(0.1)
            p.stdin.write("echo $?\n")
            p.stdin.flush()
            sleep(0.1)
            p.stdin.write("exit\n")
            p.stdin.flush()
        except(BrokenPipeError):
            segfault=True

        timeout = False
        try:
            p.wait(timeout=self.timeout)
        except(TimeoutExpired):
            timeout = True
            p.terminate()

        open("../stdin.txt", "w").write(case)
        stdout = open(stdout_file,"r").read()
        stderr = open(stderr_file,"r").read()
        command_code = None
        if not timeout and not p.returncode and not segfault:
            stdout = stdout.split("\n")
            if len(stdout) > 1: 
                command_code = stdout[-2]
                stdout = "\n".join(stdout[:-2])

        ret = {"exit_code": p.returncode,
               "return_code": command_code,
               "timeout": timeout,
               "segfault": segfault,
               "stdout": stdout,
               "stderr": stderr,
               "folder": test_case_path,
               "shell_folder": folder
               }
        
        os.chdir("../../../../")
        p.communicate()
        return ret
    
    def analyse_value(self, ret_a, ret_b, value, case_score, output_value=True):
        out = ""
        if ret_a[value] != ret_b[value]:
            out += "[" + tcolors["FAIL"] + "KO" + tcolors["ENDC"] + "] " + value
            if(output_value):
                out += "\t\t" + str(ret_a[value]) + " vs " + str(ret_b[value])
            out += "\n"
            case_score = 1
        else:
            out += "[" + tcolors["OKGREEN"] + "OK" + tcolors["ENDC"] + "] " + value
            if(output_value):
                out += "\t\t" + str(ret_a[value])
            out += "\n"
        return case_score, out
    
    def compare_folders(self, a, b):
        
        for node in os.listdir(a):
            if not os.path.exists(os.path.join(b, node)):
                return 0
            if os.path.isdir(os.path.join(a, node)):
                if not os.path.isdir(os.path.join(b, node)):
                    return 0
                if not self.compare_folders(os.path.join(a, node), os.path.join(b, node)):
                    return 0
            else:
                if os.path.isdir(os.path.join(b, node)):
                    return 0
                try:
                    if open(os.path.join(a, node)).read() != open(os.path.join(b, node)).read():
                        return 0
                except(Exception):
                    pass

        return 1

    def parse_valgrind(self, logfile):
        memory = ["definitely lost", "indirectly lost", "possibly lost", "still reachable"]
        has_summary = False
        while(not has_summary):
            with open(logfile, "r") as f:
                file = f.read().split("\n")
            line = file[0]
            id = line[2:]
            id = id[:id.find("==")]
            for line in file:
                if line.find("==" + id + "== ERROR SUMMARY: ") != -1:
                    has_summary = True
            sleep(0.2)

        for line in file:
            if (pos := line.find("FILE DESCRIPTORS: ")) != -1:
                rest = line[pos + len("FILE DESCRIPTORS: "):]
                open_fds = int(rest[:rest.find(" ")])
                rest = rest[rest.find("("):]
                rest = rest[1:rest.find(" ")]
                std_fds = int(rest)
                if open_fds - std_fds > 1:
                    return 1
            else:
                for key in memory:
                    if (pos := line.find(key + ": ")) != -1:
                        rest = line[pos + len(key) + 2:]
                        rest = rest[:rest.find(" ")]
                        if int(rest) > 0:
                            return 1
        return 0

    def analyse_test_case(self, ret_a, ret_b):
        folder = ret_a["folder"]
        valgrind = os.path.join(folder, VALGRIND_LOGFILE)
        case_score = 0
        out = ""
        log = ""

        if not self.compare_folders(ret_a["shell_folder"], ret_b["shell_folder"]):
            ret_a["folder"] = None

        case_score, log = self.analyse_value(ret_a, ret_b, "stdout", case_score, False)
        out += log
        case_score, log = self.analyse_value(ret_a, ret_b, "stderr", case_score, False)
        out += log
        case_score, log = self.analyse_value(ret_a, ret_b, "folder", case_score, False)
        output_score = case_score
        case_score = 0
        out += log
        out += "\n"
        case_score, log = self.analyse_value(ret_a, ret_b, "exit_code", case_score)
        out += log
        case_score, log = self.analyse_value(ret_a, ret_b, "return_code", case_score)
        out += log
        out += "\n"
        case_score, log = self.analyse_value(ret_a, ret_b, "timeout", case_score)
        out += log
        case_score, log = self.analyse_value(ret_a, ret_b, "segfault", case_score)
        return_score = case_score
        case_score = 0
        out += log
        out += "\n"

        if not os.path.exists(valgrind):
            memory_score = 0
        else:
            memory_score = self.parse_valgrind(valgrind)
        if memory_score:
            out += "[" + tcolors["FAIL"] + "KO" + tcolors["ENDC"] + "] " + "memory & fds\n"
        else:
            out += "[" + tcolors["OKGREEN"] + "OK" + tcolors["ENDC"] + "] " + "memory & fds\n"

        open(os.path.join(folder, "test.log"), "w").write(replace_colors(out))
        return (output_score, return_score, memory_score, output_score + return_score + memory_score)
        # case_score += compare_folders(os.path.join(case_folder, SHELL_A_NAME), os.path.join(case_folder, SHELL_B_NAME))
        # case_score += check_valgrind_log(os.path.join(case_folder, VALGRIND_LOGFILE))




