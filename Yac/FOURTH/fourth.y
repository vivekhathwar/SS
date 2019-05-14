%{
#include<stdio.h>
#include<stdlib.h>
%}
%token A B
%%
S: A S | S B | ;
%%
void main(){
yyparse();
printf("valid\n");
}
void yyerror(){
printf("Invalid\n");
exit(0);
}
