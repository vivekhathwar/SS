%{
#include<stdio.h>
#include<stdlib.h>
%}
%token NUMBER
%%
S: S NUMBER |
     NUMBER NUMBER NUMBER ;
%%
void main(){
yyparse();
printf("Valid\n");
}
int yyerror()
{
printf("Invalid\n");
exit(0);
}
