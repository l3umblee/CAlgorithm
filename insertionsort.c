#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N, key, ind;
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        scanf("%d", &data[i]);

    for(int i = 1; i < N; i++)
    {
        key = data[i];
        for(int j = i - 1; data[j] > key && j >= 0; j--)
        {
            data[j+1] = data[j];
            ind = j;
        }
        data[ind] = key;
    }
    
    for(int i = 0; i < N; i++)
        printf("%d ", data[i]);
    printf("\n");
    free(data);
    return 0;
}
