from TestSuite import TestSuite

class Echo(TestSuite):
	def __init__(self):
		super(Echo, self).__init__()
		self.folder = "Echo"
		self.files = {
			"empty.txt": "",
			"existing.txt": "previous content\n"
		}
		
		self.initrc = """
		chmod 0644 empty.txt
		chmod 0644 existing.txt
		"""
		
		self.test_cases = TESTCASES

TESTCASES = [
	"""
	echo hello world
	""",
	
	"""
	echo The quick brown fox
	""",
	
	"""
	echo
	""",
	
	"""
	echo -n hello world
	""",
	
	"""
	echo -n The quick brown fox
	""",
	
	"""
	echo multiple     spaces      test
	""",
	
	"""
	echo "hello    world"
	""",
	
	"""
	echo 'hello    world'
	""",
	
	"""
	echo -n "hello    world"
	""",
	
	"""
	echo hello\tworld
	""",
	
	"""
	echo hello world > output.txt
	""",
	
	"""
	echo -n hello world > output.txt
	""",
	
	"""
	echo hello world >> existing.txt
	""",
	
	"""
	echo "hello   'world'"
	""",
	
	"""
	echo hello\\nworld
	""",
	
	"""
	echo -n hello\\nworld
	""",
	
	"""
	echo -n -n hello
	""",
	
	"""
	echo hello -n world
	""",
	
	"""
	echo hello world | cat
	""",
	
	"""
	echo -n hello world | cat
	"""
]
