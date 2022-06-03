#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N, tmp;
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        scanf("%d", &data[i]);

    for(int i = N - 1; i > 0; i--)
    {
        for(int j = 0; j < N-1; j++)
        {
            if(data[j] > data[j+1])
            {
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            } 
        }
    }

    for(int i = 0; i < N; i++)
        printf("%d ", data[i]);
    printf("\n");
    free(data);
    return 0;
}
