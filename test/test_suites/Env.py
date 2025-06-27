from TestSuite import TestSuite

class Environment(TestSuite):
	def __init__(self):
		super(Environment, self).__init__()
		self.folder = "Environment"
		self.files = {
			"script.sh": "echo $TEST_VAR\necho $PATH",
			"nested_script.sh": "echo $NESTED_VAR"
		}
		
		self.initrc = """
		chmod +x script.sh
		chmod +x nested_script.sh
		export INITIAL_VAR="initial_value"
		export TEST_VAR="test_value"
		export NESTED_VAR="nested_value"
		"""
		
		self.test_cases = TESTCASES

TESTCASES = [
	"""
	env
	""",
	
	"""
	export NEW_VAR="new_value"
	env | grep NEW_VAR
	""",
	
	# Export with spaces and special chars
	"""
	export SPECIAL_VAR="value with spaces and $symbols"
	echo $SPECIAL_VAR
	""",
	
	# Multiple exports
	"""
	export VAR1="first" VAR2="second" VAR3="third"
	env | grep VAR
	""",
	
	# Unset single variable
	"""
	unset TEST_VAR
	echo $TEST_VAR
	""",
	
	# Unset multiple variables
	"""
	unset VAR1 VAR2 VAR3
	env | grep VAR
	""",
	
	# Export and immediately unset
	"""
	export TEMP_VAR="temporary"
	echo $TEMP_VAR
	unset TEMP_VAR
	echo $TEMP_VAR
	""",
	
	# Export with quotes
	"""
	export QUOTED_VAR='$HOME'
	echo $QUOTED_VAR
	export EXPANDED_VAR="$HOME"
	echo $EXPANDED_VAR
	""",
	
	# Modify existing variable
	"""
	echo $PATH
	export PATH="/custom/path:$PATH"
	echo $PATH
	""",
	
	# Export without value
	"""
	export EMPTY_VAR=
	echo "[$EMPTY_VAR]"
	""",
	
	# Export variable using another variable
	"""
	export REF_VAR="reference"
	export NEW_VAR=$REF_VAR
	echo $NEW_VAR
	""",
	
	# Unset nonexistent variable
	"""
	unset NONEXISTENT_VAR
	echo $?
	""",
	
	# Export with complex values
	"""
	export COMPLEX_VAR="value:with:colons;and;semicolons"
	echo $COMPLEX_VAR
	""",
	
	# Environment inheritance test
	"""
	export PARENT_VAR="parent_value"
	./script.sh
	""",
	
	# Nested environment inheritance
	"""
	export LEVEL1="level1"
	(export LEVEL2="level2"; echo $LEVEL1; echo $LEVEL2)
	echo $LEVEL2
	""",
	
	# Export with special patterns
	"""
	export var_with_underscore="underscore"
	export VAR.WITH.DOTS="dots"
	env | grep -e var_with_underscore -e VAR.WITH.DOTS
	""",
	
	# Export and env with pipe
	"""
	export PIPE_VAR="pipe_value"
	env | grep PIPE_VAR | cat
	""",
	
	# Multiple operations sequence
	"""
	export SEQ_VAR="first"
	echo $SEQ_VAR
	export SEQ_VAR="second"
	echo $SEQ_VAR
	unset SEQ_VAR
	echo $SEQ_VAR
	""",
	
	# Test environment clearing
	"""
	env -i ./script.sh
	"""
]
