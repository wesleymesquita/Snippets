/*
* @brief Solution to http://www.spoj.com/problems/ONP/ 
* @author Wesley Mesquita
* @email wesleymesquita@gmail.com
*
* @note followed these instructions http://csis.pace.edu/~wolf/CS122/infix-postfix.htm 
*       
* @note generate tests with the help of http://scriptasylum.com/tutorials/infix_postfix/infix_postfix.html
*/


#include<stdio.h>
#include<string.h>

int prec(char c){
  if(c == '+' || c == '-')
    return 0;
  else if(c == '/' || c == '*')
    return 1;
  else if(c == '^')
    return 2; 
  
  return -1;
}

int main(){
  
  int n_expr;	
  
  char expr[401];
  char stack[401];
  char new_expr[401];
  int i, j, k, stack_p, expr_sz, new_expr_p, first, equal_prec;
  
  
  first = 1;
  scanf("%d", &n_expr);
  
  while(n_expr--){
    scanf("%s", expr);
    
    stack_p = -1;
    new_expr_p = -1;
    expr_sz= strlen(expr);
    
    for(i=0; i<expr_sz; i++){
      
      if(expr[i]=='+'||expr[i]=='-'||expr[i]=='*'||expr[i]=='/'||expr[i]=='^'){
	
        if( stack_p < 0 || stack[stack_p] == '(' ) 
          stack[++stack_p] = expr[i];
        else{          
          if( prec(expr[i]) > prec(stack[stack_p]) ){
            stack[++stack_p] = expr[i];
          }
          else if( prec(expr[i]) <= prec(stack[stack_p]) ){
	    
            while(stack > 0 &&  stack[stack_p] != '(' && 
		  prec(expr[i]) <= prec(stack[stack_p]) ){
	      
	      if(prec(expr[i]) < prec(stack[stack_p])){	  
		new_expr[++new_expr_p] = stack[stack_p--];           
              }	
              else if(prec(expr[i]) == prec(stack[stack_p])){
                if(expr[i] != '^'){
                  new_expr[++new_expr_p] = stack[stack_p--];
                }                          
		else
		  break; 
	      }           
            }
	    stack[++stack_p] = expr[i]; 
	  }
        }
      }
      else if(expr[i] == '(' ){
        stack[++stack_p] = expr[i];
      }
      else if(expr[i] == ')'){
        while(stack[stack_p] != '('){
          new_expr[++new_expr_p] = stack[stack_p--];
        }
        stack_p--;
      }
      else{
        new_expr[++new_expr_p] = expr[i];
      }
    }
    
    while(stack_p >= 0){      
      new_expr[++new_expr_p] = stack[stack_p--]; 
    }
    
    new_expr[++new_expr_p] = '\0';
    
    if(first)
      first = 0;
    else
      printf("\n");
    
    printf("%s", new_expr);
  }
  
  printf("\n");	
  return 0;
}
