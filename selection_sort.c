#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N, temp;
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        scanf("%d", &data[i]);
    for(int i = 0; i < N-1; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            if(data[i] > data[j])
            {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    for(int i = 0; i < N; i++)
        printf("%d ", data[i]);
    printf("\n");
    free(data);
    return 0;
}
