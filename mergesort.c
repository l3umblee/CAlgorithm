#include <stdio.h>
#include <stdlib.h>
int *tmp;
void merge(int *arr, int p, int q, int r)
{
    int i = p, j = q+1, k = p;
    while(i <= q && j <= r)
    {
        if(arr[i] <= arr[j])   tmp[k++] = arr[i++];
        else    tmp[k++] = arr[j++];
    }
    while(i <= q)   tmp[k++] = arr[i++];
    while(j <= r)   tmp[k++] = arr[j++];

    for(int i = p; i <= r; i++)
        arr[i] = tmp[i];
}
void mergesort(int *arr, int p, int r)
{
    if(p < r)
    {
        int q = (p+r)/2;
        mergesort(arr, p, q);
        mergesort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

int main(void)
{
    int N;
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    tmp = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        scanf("%d", &data[i]);

    mergesort(data, 0, N-1);

    for(int i = 0; i < N; i++)
        printf("%d ", data[i]);
    printf("\n");
    free(data);
    return 0;
}
