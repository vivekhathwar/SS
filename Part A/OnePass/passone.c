#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
FILE *f1,*f2,*f3,*f4;
char opcode[20],label[20],operand[20],mnemonic[20],xyz[10];
int start,locctr,length;
f1=fopen("input.txt","r");
f2=fopen("output.txt","w");
f3=fopen("optab.txt","r");
f4=fopen("symtab.txt","w");

fscanf(f1,"%s%s%s", label,opcode,operand);
if(strcmp(opcode,"START")==0){
    start=strtol(operand,NULL,16);
    locctr=start;
    fprintf(f2,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
}
else
    locctr=0;
fscanf(f1,"%s%s%s",label,opcode,operand);
while(strcmp(opcode,"END")!=0){
    fprintf(f2,"%x\t",locctr);
    if(strcmp(label,"*")!=0)
        fprintf(f4,"%s\t%x\n",label,locctr);
    rewind(f3);
    fscanf(f3,"%s%s",mnemonic,xyz);
    while(strcmp(mnemonic,"END")!=0){
        if(strcmp(mnemonic,opcode)==0){
            locctr+=3;
            break;
            }
        fscanf(f3,"%s%s",mnemonic,xyz);
    }
    if(strcmp(opcode,"WORD")==0)
        locctr+=3;
    else if(strcmp(opcode,"RESB")==0)
        locctr+=atoi(operand);
    else if(strcmp(opcode,"RESW")==0)
        locctr+=3*atoi(operand);
    else if(strcmp(opcode,"BYTE")==0)
        if(operand[0]=='X')locctr++;
        else
            locctr+=strlen(operand)-3;
fprintf(f2,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(f1,"%s%s%s",label,opcode,operand);
}
fprintf(f2,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
length=locctr-start;
printf("Length of the program is %d\n",length);
fclose(f1);fclose(f2);fclose(f3);fclose(f4);
}
