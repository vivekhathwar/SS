#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
FILE *f1,*f2;
f1=fopen("input.txt","r");
f2=fopen("output.txt","w");
char temp[80],add[10],label[20],opcode[20],operand[20],objc[10],st[10];
int start,end,len;
fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
start=strtol(add,NULL,16);
while(!feof(f1))
    fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
end=strtol(add,NULL,16);
len=end-start;
rewind(f1);
fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
fprintf(f2,"%s\t%04x\t%06x\n",label,start,len);
strcpy(st,"T 00");
len=0;
fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
strcat(st,add);
while(strcmp(opcode,"END")!=0){
    if((len==30)||(strcmp(opcode,"RESW")==0)||(strcmp(opcode,"RESB")==0)||((strlen(objc)/2)+len>=30)){
        fprintf(f2,"%s\t%02x\t%s\n",st,len,temp);
        strcpy(st,"T 00");
        strcpy(temp,"");
        fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
        len=0;
        if(strcmp(objc,"**")!=0){
            strcat(st,add);
            strcat(temp,objc);
            strcat(temp," ");
            len=(strlen(objc)/2);
        }
    }
    else{
        strcat(temp,objc);
        strcat(temp," ");
        len+=strlen(objc)/2;
    }
    fscanf(f1,"%s%s%s%s%s",add,label,opcode,operand,objc);
}
if(len!=0)
    fprintf(f2,"%s\t%02x\t%s\n",st,len,temp);
fprintf(f2,"E 00%04x",start);
fclose(f1);fclose(f2);
}
