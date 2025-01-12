//P1601 A+B Problem（高精）

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int digital(char c) {  //将存入的char类型数字，转为int
    if (isdigit(c)) {
        return c - '0'; 
    } else {  
         
        return -1;  
    }  
}
void add(char*a,char*b,int *c){
    c[0]=0;
    int i=0;
    int min=strlen(a)>strlen(b)?strlen(b):strlen(a);
    int max=strlen(a)<strlen(b)?strlen(b):strlen(a);
    for(i=0;i<min;i++){
        c[i+1]=0;
            if(digital(a[i])+digital(b[i])+c[i]>=10){
                   c[i]+=digital(a[i])+digital(b[i])-10;
                   c[i+1]++;
            }
            else{
                c[i]+=digital(a[i])+digital(b[i]);
            }
    }
    if(c[i]!=1)
    c[i]=0;
    if(strlen(a)>strlen(b)){
        for(i;i<max;i++){
             c[i+1]=0;
            if(c[i]+digital(a[i])>=10){
                c[i]+=digital(a[i])-10;
                c[i+1]++;
            }
            else
            c[i]+=digital(a[i]);
        }
    }
    if(strlen(a)<strlen(b)){
        for(i;i<max;i++){
             c[i+1]=0;
            if(c[i]+digital(b[i])>=10){
                c[i]+=digital(b[i])-10;
                c[i+1]++;
            }
            else
            c[i]+=digital(b[i]);
        }
    }
    else
    return;
    
}
void reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
int main()
{
    char a[1050], b[1050];
    int  result[1051];
    scanf("%s", a);
    scanf("%s", b);

    reverse(a); // 反转字符串
    reverse(b);
    int max=strlen(a)<strlen(b)?strlen(b):strlen(a);
    add(a, b, result);
    if(result[max]==0)
    max--;
    for(int i=max;i>=0;i--){
        
        printf("%d",result[i]);
    }
    return 0;
}