#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *x, int *y) 
{ 
    int tmp = *x; 
    *x = *y; 
    *y = tmp; 
}
int partition(int *arr, int p, int r)
{
    srand(time(NULL));
    int rng = p + rand()%(r-p+1);
    swap(&arr[rng], &arr[r]);
    int pivot = arr[r], i = p - 1, j = p;
    for(j = p; j <= r-1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return i+1;
}

void quicksort(int *arr, int p, int r)
{
    if(p < r)
    {   
        int q = partition(arr, p, r);
        quicksort(arr, p, q-1);
        quicksort(arr, q+1, r);
    }
}

int main(void)
{
    int N;
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        scanf("%d", &data[i]);
    quicksort(data, 0, N-1);
    for(int i = 0; i < N; i++)
        printf("%d ", data[i]);
    free(data);
    return 0;
}
