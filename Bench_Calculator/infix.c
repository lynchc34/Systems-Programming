#include "infix.h"

double operator_ge_precendence(struct double_stack*stack, char **args, char*op){
if (stack -> top == -1){
  return 0;
}
else{
int stackIndex = double_stack_pop(stack); 
char * operatorSign = args[stackIndex];
double_stack_push(stack,stackIndex);

int opResult =0;
if (*operatorSign == '('){
  return 0;
}
else{
  if(*operatorSign == '^'){
   opResult = 3;
  }
  else if(*operatorSign == 'X' || '/'){
   opResult = 2;
  }
  else {
    opResult = 1;
  }
  
  int charResult;
  if(*op == '^'){
   charResult = 3;
  }
  else if(*op == 'X' || '/'){
   charResult = 2;
  }
  else {
    charResult = 1;
  }

  if (charResult < opResult){
    return 1;
  }
  else if (charResult == opResult){
    return 1;
  }
  else{
    return 0;
  }
 }
}
return 0;

}

double not_lbracket_on_stack(struct double_stack*stack, char** args, int lBracket){
  int stackTop = stack -> items[stack->top];
  if (*args[stackTop]==lBracket){
    return 0;
  }
  else {
    return 1;
  }
}



// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  // Write your code here 
  char ** postfix = malloc(sizeof(char*)*nargs);
  int postfix_length = 0;
  struct double_stack *stack = double_stack_new(nargs);
  
  for (int i = 0; i <nargs; i++){
    if ((args[i][0] >= '0' && args[i][0] <= '9') || (args[i][1] >= '1' && args[i][1] <= '9')){
        postfix[postfix_length] = args[i];
        postfix_length++;
    }
    else if ((args[i][0] == '('){
      double_stack_push(stack,i);
    }
    else if ((args[i][0]) == '^' || (args[i][0]) == 'X' || (args[i][0]) == '+' || (args[i][0]) == '-' || (args[i][0]) == '/'){
     char * op = args[i];
     while(operator_ge_precedence(stack, args, op)){
        int op = double_stack_pop(stack);
        postfix[postfix_length] = args[op];
        postfix_length++;
      }
      double_stack_push(stack,i);
    }
    else if ((args[i][0]) == ')'){
      while(not_lbracket_on_stack(stack, args, '(')){
        int op;
        op = double_stack_pop(stack);
        postfix[postfix_length] = args[op];
        postfix_length++; 
      }
      //pop left bracket
      int op;
      op = double_stack_pop(stack);
      assert ((*args[op] == '('));
    }
    else{
      //error
      assert(false);
    }
   }
   while (stack-> top != -1){
     int operatorPopped = double_stack_pop(stack);
     postfix[postfix_length] = args[operatorPopped];
     postfix_length++;
   }
   //code to check answer (opts being popped from stack)
   for(int i = 0; i < postfix_length; i++){
    char * a = postfix[i];
    printf("%s", a);
  }
   return evaluate_postfix_expression(postfix, postfix_length);
  }


