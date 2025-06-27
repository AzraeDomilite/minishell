from TestSuite import TestSuite

class AWK(TestSuite):
	def __init__(self):
		super(AWK, self).__init__()
		self.folder = "AWK"
		self.files = {
			"numbers.txt": "1 apple\n2 banana\n3 cherry\n4 date\n5 elderberry",
			"names.txt": "John Doe 25\nJane Smith 30\nBob Johnson 45\nAlice Brown 35\nCharlie Davis 28",
			"data.csv": "id,name,score\n1,Alice,95\n2,Bob,87\n3,Charlie,92\n4,David,78\n5,Eva,98",
			"empty.txt": "",
			"spaces.txt": "  leading spaces\ntrailing spaces  \n  both  sides  \nnormal text"
		}

		self.initrc = """
		chmod 0644 numbers.txt
		chmod 0644 names.txt
		chmod 0644 data.csv
		chmod 0644 empty.txt
		chmod 0644 spaces.txt
		"""
		
		self.test_cases = TESTCASES

TESTCASES = [
	"""
	awk '{print $1}' numbers.txt
	""",
	
	"""
	awk -F',' '{print $2}' data.csv
	""",
	
	"""
	awk '/John/' names.txt
	""",
	
	"""
	awk '{sum += $3} END {print "Average Score:", sum/NR}' data.csv
	""",
	
	"""
	awk 'BEGIN {print "Processing numbers..."} {print $1 ": " $2}' numbers.txt
	""",

	"""
	awk '$3 >= 90 {print $2 " passed"}' data.csv
	""",
	
	"""
	awk '{print NR ": " $0}' numbers.txt names.txt
	""",
	
	"""
	awk '{print tolower($2)}' names.txt
	""",
	
	"""
	awk '{total += $3} {print "Running total: " total}' names.txt
	""",
	
	"""
	awk '/^[0-9]/ {print "Starts with number: " $0}' numbers.txt
	""",
	
	"""
	cat data.csv | awk -F',' 'NR>1 {print $2}'
	""",
	
	"""
	awk -F',' '$3>85 && $3<95 {print $2 " needs review"}' data.csv
	""",
	
	"""
	awk '{print "Line: " $0}' empty.txt
	""",
	
	"""
	awk '{gsub(/^[ \t]+|[ \t]+$/, ""); print}' spaces.txt
	""",
	
	"""
	awk '{print $1}' nonexistent.txt
	"""
]
