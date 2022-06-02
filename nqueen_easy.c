// nqueens 문제를 제한적이지만 좀 더 간단하게 해결할 수 있다.
#include <stdio.h>
#include <stdbool.h>
int main(void)
{
    int N, i;
    bool isOdd = false;
    scanf("%d", &N);
    if(N%2 != 0) 
        isOdd = true;
    if(N%6 == 2)
    {
        for(i = 1; i <= N/2; i++)
            printf("%d\n", i*2);
        printf("%d\n%d\n", 3, 1);
        for(i = 3; i <= N/2 - 1; i++)
            printf("%d\n", 2*i + 1);
        printf("%d", 5);
    }
    else if(N%6 == 3)
    {
        for(i = 2; i <= N/2; i++)
            printf("%d\n", i*2);
        printf("%d\n", 2);
        for(i = 3; i <= N/2; i++)
            printf("%d\n",2*i - 1);
        printf("%d\n%d\n", 1, 3);
    }
    else if(N%6 != 2 && N%6 != 3)
    {
        for(i = 1; i <= N/2; i++)
            printf("%d\n", i*2);
        for(i = 1; i <= N/2; i++)
            printf("%d\n", 2*i - 1);
        if(isOdd) printf("%d", N);
    }
    return 0;
}
