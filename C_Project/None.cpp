#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool A(int n){
      if(n<=0)
      return 0;
      else
      return 1;
}

int main() {
   bool result = A(-1);
   printf("%d",result);
   return 0;
}
