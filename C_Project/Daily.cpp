#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000
int main()
{
    srand(time(NULL));
    int add =0;
    int sum=0;
    for(int i=0;i<MAX;i++){
        sum+=add;
        add =(rand()%2==0)?1:-1;
    }
    printf("%d",sum);
    return 0;
}