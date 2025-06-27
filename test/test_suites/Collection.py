from TestSuite import TestSuite

class Easy(TestSuite):
    def __init__(self):
        super(Easy, self).__init__()
        self.folder = "Easy"
        self.files = {"asdf": "asdf",
                      "bsdf": "bsdf",
                      "folder_a/folder_b": None,
                      "a/b/c/d.txt": "d"
                      }
        self.initrc = """
        chmod 0700 asdf
        chmod 0100 bsdf
        """
        self.test_cases = TESTCASES


TESTCASES = [
"(ls | cat) | (cat | cat)",
"(ls | cat|)",
"(ls; )",
"""
ls | cat |

cat
""",
"ls < file 1 < file 2 | cat",
"(ls < file1) < file2|cat",
"ls < file1 < file 2 | cat",
"((ls << heredoc) | cat);",
"((echo "asdf" > asdf) ; < bsdf cat) > asdf",
"""
( (ls )
| cat)
""",

"""
( (ls ) |
cat)
""",

]