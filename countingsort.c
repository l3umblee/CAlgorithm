#include <stdio.h>
#include <stdlib.h>
int N;
void swap(int *x, int *y) { int tmp = *x; *x = *y; *y = tmp; }
int indMax(int *x, int xi, int *y, int yi) { return (*x > *y) ? xi : yi ; }

void Printfunc(int* data, int num)
{
    for(int i = 0; i < num; i++)
        printf("%d ", data[i]);
    printf("\n");
}

void Countingsort(int* data, int* result, int k)
{
    int *cnt;
    int d, c, r;
    cnt = (int*)malloc(sizeof(int)*k);
    for(int i = 0; i < k; i++)
        cnt[i] = 0;
    for(int i = 0; i < N; i++)
        cnt[data[i]] += 1;
    for(int i = 1; i < k; i++)
        cnt[i] += cnt[i-1];
    for(int j = N - 1; j >= 0; j--)
    {
        int c = cnt[data[j]], d = data[j];
        result[c-1] = d;
        cnt[d] = c-1;
    }
    free(cnt);
}

int main(void)
{
    int *data, *result;
    int k;
    printf("degree : ");
    scanf("%d", &k);
    printf("size : ");
    scanf("%d", &N);
    data = (int*)malloc(sizeof(int)*N);
    result = (int*)malloc(sizeof(int)*N);
    printf("insert numbers\n");
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &data[i]);
        result[i] = 0;
    }
    k++;
    Countingsort(data, result, k);
    Printfunc(data, N);
    Printfunc(result, N);
    free(data);
    free(result);
    return 0;
}
