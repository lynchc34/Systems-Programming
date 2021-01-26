#include "postfix.h"
#include "math.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  struct double_stack *double_stack  = double_stack_new(nargs);

  for (int i =0; i < nargs; i++) {
    if ((args[i][0] >= '0' && args[i][0] <= '9') || (args[i][1] >= '1' && args[i][1] <= '9')) {
      double operand = atof(args[i]);
      double_stack_push(double_stack,operand);
    }
    else if ((args[i][0] =='+')||(args[i][0]=='-')||(args[i][0]=='X')||(args[i][0]=='/')||(args[i][0]=='^')||(args[i][0]==' ')){
      switch (args[i][0])
      {
        double digitOne;
        double digitTwo;
        double result;

      case '+':
        digitOne = double_stack_pop(double_stack);
        digitTwo = double_stack_pop(double_stack);
        result = digitOne + digitTwo;
        double_stack_push(double_stack, result);
        break;
      case '-':
        digitOne = double_stack_pop(double_stack);
        digitTwo = double_stack_pop(double_stack);
        result = digitTwo - digitOne;
        double_stack_push(double_stack,result);
        break;
      case 'X':
        digitOne = double_stack_pop(double_stack);
        digitTwo = double_stack_pop(double_stack);
        result = digitOne*digitTwo;
        double_stack_push(double_stack, result);
        break;
      case '/':
        digitOne = double_stack_pop(double_stack);
        digitTwo = double_stack_pop(double_stack);
        result = digitTwo/digitOne;
        double_stack_push(double_stack, result);
        break;
      case '^':
        digitOne = double_stack_pop(double_stack);
        digitTwo = double_stack_pop(double_stack);
        result = pow(digitTwo,digitOne);
        double_stack_push(double_stack, result); 
        break;
      case ' ':
        break;
        
      //default:
      //break;
      }
    }
  }
  double calcAnswer = double_stack_pop(double_stack);
  return calcAnswer;
}
