#include <ez.h>
#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <_stack.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#	define fix_offset  1

#	define digit        2 
#	define add_sub     3 
#	define prod_dev	   4 
#	define left_bracket      5 
#	define right_bracket  6
#	define other_ch     1

int precedence (const char); 

char* 
infix_to_postfix (const char*);

int precedence (const char _ch) {
	if (isdigit (_ch)) 
		return digit;
	else if (_ch == '+' || _ch == '-') 
		return add_sub;
	else if (_ch == '*' || _ch == '/') 
		return prod_dev;
	else if (_ch == '(') 
		return left_bracket;
	else if (_ch == ')')
		return right_bracket;
	else 
		return other_ch;
}


char*
infix_to_postfix (const char* _fix) {
	int len, i = 0, idx = 0;
	len = strlen (_fix) + 1;
	char* post = calloc (len + 1, sizeof (char));
	_stack stk = create_stack (len);
	for (; i < len; i ++) {
		int prec = precedence (_fix [i]);

		if (prec == digit) { // digit
			post [idx ++] = _fix [i];

		} else if (prec != other_ch && 
				prec != left_bracket && prec != right_bracket) { // not other and bracket
			int top_prec = precedence (top (stk)); 
			if (prec > top_prec || top_prec == left_bracket)
				push (stk, _fix [i]);
			else if (prec <= top_prec) {
				while (! empty_stk (stk))
					if ((top_prec = precedence 
						(top (stk))) >= prec)
						post [idx ++] = topandpop (stk);
				push (stk, _fix [i]);
			} 			
		} else if (prec == right_bracket) {
			while (! empty_stk (stk)) 
				if (precedence (top (stk))
						!= left_bracket)
					post [idx ++] = 
						topandpop (stk);
				else {
					pop (stk);
					break;
				}
		} else if (prec == left_bracket) {
			push (stk, _fix [i]);
		}
	} 
	while (! empty_stk (stk)) {
		post [idx ++] = topandpop (stk);
	}

	return post;
}



int main (argc, argv)
	int argc;
	char* argv [];
{
	const char* infix = "3+(9-6+4)-(8*3)";
	char* postfix;
//	if (argc >= 2)
//		infix = argv [fix_offset];
//	else { 
//		println ("no infix to convert!");
//		return 0;
//	}


	postfix = infix_to_postfix (infix);

	println (postfix);
	return 0;
}
