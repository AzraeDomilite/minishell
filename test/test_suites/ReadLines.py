from TestSuite import TestSuite

class EOF1(TestSuite):
    def __init__(self):
        super(EOF1, self).__init__()
        self.folder = "EOF1"
        self.files = {}
        self.test_cases = TESTCASES


TESTCASES = [
"""
/usr/bin/cat | /usr/bin/cat
)
EOF
""",
"""
/usr/bin/ls | /usr/bin/cat
)
EOF
""",
"""
/usr/bin/cat << EOF
)
EOF
)
""",
"""
/usr/bin/cat; /usr/bin/cat << EOF
)
EOF
""",
"""
/usr/bin/cat; /usr/bin/cat << EOF
)
EOF
USA
""",
"""
/usr/bin/cat | /usr/bin/cat << EOF
)
EOF
""",
"""
/usr/bin/cat
a
"""
]