# ---------------------------------------------------------------------------------
#  LAB 10: Reverse Polish Notation (RPN) Calculator Revisited
#  CMPS 109  Spring 2018 University of California Santa Cruz
# 
#  Boothroyd, Nichole
#  nboothro
# 
#  Language:    Awk
#  
#  Description: This program accepts a single string argument in RPN, evaluates it,
#               and prints the answer to stdout.
# 
#  Usage:       awk -f rpnc.awk "RPN expression"
# 
# ---------------------------------------------------------------------------------
BEGIN {
	stackIndex = 0;
	arrSize = split(ARGV[1], arr, " ", seps)
	for(i = 0; i <= arrSize; i++) {
		if (arr[i] ~/[0-9]/) {
			stack[stackIndex] = arr[i]
			stackIndex++
		}
		else if (arr[i] ~/+/) { 
			stackIndex--
			op_2 = stack[stackIndex]
			stackIndex--
			op_1 = stack[stackIndex]
			result = op_1 + op_2
			stack[stackIndex] = result
			stackIndex++
		}	
		else if (arr[i] ~/-/) { 
			stackIndex--
			op_2 = stack[stackIndex]
			stackIndex--
			op_1 = stack[stackIndex]
			result = op_1 - op_2
			stack[stackIndex] = result
			stackIndex++
		}	
		else if (arr[i] ~/\//) { 
			stackIndex--
			op_2 = stack[stackIndex]
			stackIndex--
			op_1 = stack[stackIndex]
			result = op_1 / op_2
			stack[stackIndex] = result
			stackIndex++
		}	
		else if (arr[i] ~/\^/) { 
			stackIndex--
			op_2 = stack[stackIndex]
			stackIndex--
			op_1 = stack[stackIndex]
			result = op_1 ** op_2
			stack[stackIndex] = result
			stackIndex++
		}	
		else if (arr[i] ~/\*/) { 
			stackIndex--
			op_2 = stack[stackIndex]
			stackIndex--
			op_1 = stack[stackIndex]
			result = op_1 * op_2
			stack[stackIndex] = result
			stackIndex++
		}	
	}
	print stack[0]
}
