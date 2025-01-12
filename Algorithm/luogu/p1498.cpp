//P1498 南蛮图腾
#include<stdio.h>
#include<math.h>
void printSpaces(int count) {  
    for (int i = 0; i < count; i++) {  
        printf(" ");  
    }  
} 
void printUp(){
    printf("/\\");
}
void printDown(){
    printf("/_\\");
}
void draw(int n){
        



    for(int i=1;i<=pow(2,n);i++){
        if(i/2!=0){
            printSpaces(pow(2,n)-i);
            printUp();
            printf("\n");
        }
    }
}
int main(){
    int n=scanf("%d");
    draw(n);
    return 0;
}