// VERSION 4
// Homework 2
// Part 5

#include <stack>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

//////////////////////////////////
//		FUNCTION PROTOTYPES		//
//////////////////////////////////

int opPrecedence(const char ch);
int evaluate(string infix, string& postfix, bool& result);
string noSpaceInfix(string infix);
bool infixValid(string infix);
void infixpostfixConversion(string infix, string& postfix);

//////////////////////////////
//		MAIN FUNCTION		//
//////////////////////////////

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	cout << "Passed all tests" << endl;
}

//////////////////////////////////////////
//		FUNCTION IMPLEMENTATIONS		//
//////////////////////////////////////////

int evaluate(string infix, string& postfix, bool& result)	// evaluate postifx
{
	// cerr << "current infix: " << infix << endl;				/// TESTING COMMENT
	string evalinfix = noSpaceInfix(infix);	// remove the spaces from our expression
	// cerr << "new infix: " << evalinfix << endl;				/// TESTING COMMENT
	if (infixValid(evalinfix) == true)
	{
		// cerr << endl << "current postfix: " << postfix << endl;
		infixpostfixConversion(evalinfix, postfix);				// convert infix to postfix
		// cerr << "new postfix: " << postfix << endl;
		stack<bool> boolStack;									// stack for holding our bool
		for (size_t i = 0; i < postfix.size(); i++)
		{
			char ch = postfix[i];
			if (ch == 'T')
			{
				boolStack.push(true);
			}
			else if (ch == 'F')
			{
				boolStack.push(false);
			}
			else if (ch == '!')						// flip our boolean
			{
				bool temp = boolStack.top();
				boolStack.pop();
				boolStack.push(!temp);
			}
			else
			{
				bool boolOperand = boolStack.top();
				boolStack.pop();
				if (boolStack.empty() == true)
				{
					return 1;
				}
				bool boolOperand2 = boolStack.top();
				boolStack.pop();
				if (ch == '|')
				{
					boolStack.push(boolOperand2 || boolOperand);		// push true or false
				}
				if (ch == '&')
				{
					boolStack.push(boolOperand2 && boolOperand);		// push true or false
				}
			}
		}
		result = boolStack.top();	// assigns the boolean value to result
		return 0;
	}
	else
	{
		return 1;
	}
}

bool infixValid(string infix)		// returns true if valid
{
	if (infix.empty())					// check if its empty  
	{
		return false;
	}
	// cerr << "passed empty check" << endl;

	for (size_t i = 0; i < infix.size(); i++)	// returns false if invalid character detected
	{
		if (infix[i] == 'T' || infix[i] == 'F' || infix[i] == '(' || infix[i] == ')' || infix[i] == '&' || infix[i] == '|' || infix[i] == '!')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	// cerr << "passed invalid character check" << endl;

	int brackets = 0;							// returns false if brackets value is anything but zero
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ')')					// closed bracket increments
		{
			brackets++;
		}
		if (infix[i] == '(')					// open bracket decreases
		{
			brackets--;
		}
	}
	if (brackets != 0)
	{
		return false;
	}
	// cerr << "passed bracket equality check" << endl;

	if (infix[0] == '&' || infix[0] == ')' || infix[0] == '|')			// cannot start with '&', '|', or ')'
	{
		return false;
	}
	// cerr << "passed bad start check" << endl;

	// if it ends with '!', '&', '|', '('
	if (infix[infix.size() - 1] == '&' || infix[infix.size() - 1] == '!' || infix[infix.size() - 1] == '|' || infix[infix.size() - 1] == '(')
	{
		return false;
	}
	// cerr << "passed  bad end check" << endl;

	// if there are no operands present in the string
	int operandCount = 0;
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i] == 'T' || infix[i] == 'F')
		{
			operandCount++;
		}
	}
	if (operandCount == 0)
	{
		return false;
	}
	// cerr << "passed no operands check" << endl;

	// if there is a binary operator violation
	for (size_t i = 1; i < infix.size(); i++)
	{
		if (infix[i] == '&' || infix[i] == '|')
		{
			if (infix[i - 1] != 'F' && infix[i - 1] != 'T' && infix[i - 1] != ')')
			{
				return false;
			}
		}
	}
	for (size_t i = 0; i < infix.size() - 1; i++)
	{
		if (infix[i] == '&' || infix[i] == '|')
		{
			if (infix[i + 1] != 'F' && infix[i + 1] != 'T' && infix[i + 1] != '(' && infix[i + 1] != '!')
			{
				return false;
			}
		}

	}
	// cerr << "passed binary operator violation check" << endl;

	// if there is an '!' violation ( assuming nand and nor are not allowed)
	for (size_t i = 0; i < infix.size() - 1; i++)
	{
		if (infix[i] == '!')
		{
			if (infix[i + 1] != 'T' && infix[i + 1] != 'F' && infix[i + 1] != '(' && infix[i + 1] != '!')
			{
				return false;
			}
		}
	}
	// cerr << "passed '!' check" << endl;

	// adjacent operands
	for (size_t i = 0; i < infix.size() - 1; i++)
	{
		if (infix[i] == 'T' && infix[i + 1] == 'T')
		{
			return false;
		}
		if (infix[i] == 'F' && infix[i + 1] == 'F')
		{
			return false;
		}
		if (infix[i] == 'F' && infix[i + 1] == 'T')
		{
			return false;
		}
		if (infix[i] == 'T' && infix[i + 1] == 'F')
		{
			return false;
		}
	}

	// adjacent operators
	for (size_t i = 0; i < infix.size() - 1; i++)
	{
		if (infix[i] == '&' && infix[i + 1] == '&')
		{
			return false;
		}
		if (infix[i] == '|' && infix[i + 1] == '|')
		{
			return false;
		}
		if (infix[i] == '(' && infix[i + 1] == ')')
		{
			return false;
		}
	}

	// operand before '(' and operand after ')'
	for (size_t i = 0; i < infix.size() - 1; i++)   // this one looks ahead
	{
		if (infix[i] == 'F' || infix[i] == 'T')
		{
			if (infix[i + 1] == '(')
			{
				return false;
			}
		}
	}
	for (size_t i = 1; i < infix.size(); i++) // this one looks behind
	{
		if (infix[i] == 'F' || infix[i] == 'T')
		{
			if (infix[i - 1] == ')')
			{
				return false;
			}
		}
	}
	cerr << endl << "expression is valid" << endl;
	return true;
}

string noSpaceInfix(string infix)
{
	string spacelessInfix = "";
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
		{
			continue;
		}
		spacelessInfix = spacelessInfix + infix[i];
	}
	return spacelessInfix;
}

void infixpostfixConversion(string infix, string& postfix)
{
	postfix = "";								//Intialize postfix to empty
	stack<char> opStack;						// Initialize the operator stack to empty
	string noSpaces = noSpaceInfix(infix);
	for (size_t i = 0; i < noSpaces.size(); i++)		// cycle through expression
	{														// size_t instead of int, due to signed unsigned mismatch
		char ch = noSpaces[i];
		switch (ch)								// utilizing fall through
		{
		case 'T':
		case 'F':
			postfix = postfix + ch;
			break;
		case '(':
			opStack.push(ch);
			break;
		case ')':
			while (opStack.top() != '(')
			{
				postfix = postfix + opStack.top();
				opStack.pop();
			}
			opStack.pop();
			break;
		case '!':
		case '&':
		case '|':
			while (!opStack.empty() && opStack.top() != '(' && opPrecedence(ch) <= opPrecedence(opStack.top()))
			{
				postfix = postfix + opStack.top();
				opStack.pop();
			}
			opStack.push(ch);
			break;
		default:
			break;
		}
	}
	while (!opStack.empty())
	{
		postfix = postfix + opStack.top();
		opStack.pop();
	}
}

int opPrecedence(const char ch)		// this function determines the precendence
{
	switch (ch)
	{
	case '!':
		return 2;
	case '&':
		return 1;
	case '|':
		return 0;
	default:
		return -1;
	}
}

