#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
FILE *f1,*f2,*f3,*f4;
char label[20],opcode[20],operand[20],tempcode[20],tempval[20],atoper[20],addr[20];
int i;
f1=fopen("input.txt","r");
f2=fopen("output.txt","w");
f3=fopen("symtab.txt","r");
f4=fopen("optab.txt","r");
fscanf(f1,"%s%s%s%s",addr,label,opcode,operand);
if(strcmp(opcode,"START")==0){
    fprintf(f2,"%s\t%s\t%s\t%s\t**\n",addr,label,opcode,operand);
}
fscanf(f1,"%s%s%s%s",addr,label,opcode,operand);
while(strcmp(opcode,"END")!=0){
    fprintf(f2,"%s\t%s\t%s\t%s\t",addr,label,opcode,operand);
    rewind(f4);
    fscanf(f4,"%s%s",tempcode,tempval);
    while(!feof(f4)){
        if(strcmp(tempcode,opcode)==0){
            fprintf(f2,"%s",tempval);
            break;
        }
        fscanf(f4,"%s%s",tempcode,tempval);
    }
    strcpy(atoper,"");
    if(operand[strlen(operand)-1]=='X'){
        for(i=0;i<strlen(operand)-2;i++)
            atoper[i]=operand[i];
        atoper[i]='\0';
    }
    else
        strcpy(atoper,operand);
    rewind(f3);
    fscanf(f3,"%s%s",tempcode,tempval);
    while(!feof(f3)){
        if(strcmp(atoper,tempcode)==0){
            i=strtol(tempval,NULL,16);
            if(operand[strlen(operand)-1]=='X')
                i+=0x8000;
            fprintf(f2,"%x\n",i);
        }
        fscanf(f3,"%s%s",tempcode,tempval);
    }
    if(strcmp(opcode,"WORD")==0){
        i=strtol(operand,NULL,16);
        fprintf(f2,"%6x\n",i);
    }
    if(strcmp(opcode,"BYTE")==0){
        if(operand[0]=='X'){
            for(i=2;i<strlen(operand)-1;i++)
                fprintf(f2,"%c",operand[i]);
            fprintf(f2,"\n");
        }
        else if(operand[0]=='C'){
            for(i=2;i<strlen(operand)-1;i++)
                fprintf(f2,"%02x",operand[i]);
            fprintf(f2,"\n");
        }
    }
    if(strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0)
        fprintf(f2,"**\n");
    fscanf(f1,"%s%s%s%s",addr,label,opcode,operand);
}
fprintf(f2,"%s\t%s\t%s\t%s\n",addr,label,opcode,operand);
fclose(f1);fclose(f2);fclose(f3);fclose(f4);
}
