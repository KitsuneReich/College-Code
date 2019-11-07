//---------------------------------------------------------------------------------
// LAB 10: Reverse Polish Notation (RPN) Calculator Revisited
// CMPS 109  Spring 2018 University of California Santa Cruz
// 
// Boothroyd, Nichole
// nboothro
//
// Language:    JavaScript/Node.js
// 
// Description: This program accepts a single string argument in RPN, evaluates it,
//              and prints the answer to stdout. 
//
// Usage:       node rpnc.js  "RPN expression"
//
//---------------------------------------------------------------------------------

var stack = [];
argS = process.argv;
var tokens = argS[2].split(" ");
//console.log(tokens);

tokens.forEach(function(element) {
	if(!isNaN(element)) {
		stack.push(element);
	}
	else {
	op_2 = parseInt(stack.pop());
	op_1 = parseInt(stack.pop());

	if (element == "+") {
		var result = (op_1 + op_2);
		stack.push(result);
	}
	if (element == "-") {
		var result = (op_1 - op_2);
		stack.push(result);
	}
	if (element == "/") {
		var result = (op_1 / op_2);
		stack.push(result);
	}
	if (element == "^") {
		var result = Math.pow(op_1, op_2);
		stack.push(result);
	}
	if (element == "*") {
		var result = (op_1 * op_2);
		stack.push(result);
	}
	}
});
console.log(stack[0]);
