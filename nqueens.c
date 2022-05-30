#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#include <stdbool.h>
int N;
int *col;
bool promising(int level)
{
    int i = 1;
    for(i = 1; i < level; i++)
    {
        if(col[i] == col[level])
            return false;
        else if(abs(col[i]-col[level]) == level-i)
            return false;
    }
    return true;
}

bool queens(int level)
{
    int i = 1;
    if(!promising(level))
        return false;
    else if(level == N)
    {
        for(i = 1; i <= N; i++)
            printf("( %d , %d ) ", i, col[i]);
        return true;
    }
    for(i = 1; i <= N; i++)
    {
        col[level+1] = i;
        if(queens(level+1))
            return true;
    }
    return false;
}

int main(void)
{
    int i;
    printf("scale : ");
    scanf("%d", &N);
    col = (int*)malloc(sizeof(int)*(N+1));

    if(queens(0))
        printf("\ndone with success\n");
    else   
        printf("\ndone with failure\n");

    return 0;
}