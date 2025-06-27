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
"""
ls
""",
"""
asdf | ls
""",
"""
echo asdf > csdf
""",
"""
ls folder_a/folder_b
""",
"""
ls | cat
""",
"""
cat
"""
]