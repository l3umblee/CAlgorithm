#include <stdio.h>
#include <stdlib.h>
int N, heapsize;
void swap(int *x, int *y) { int tmp = *x; *x = *y; *y = tmp; }
int indMax(int *x, int xi, int *y, int yi) { return (*x > *y) ? xi : yi ; }

void MaxHeapify(int *data, int ind)
{
    int k;
    if(ind*2 > heapsize)    // 자식 노드가 없으면 여기서 걸러질 것임 
        return; 
    if(ind*2 == heapsize)   // 자식노드가 하나일 경우 여기서 (결국 마지막 노드) 
        k = 2*ind;
    else                    // 자식노드가 여러 개일 경우
        k = indMax(&data[ind*2], ind*2, &data[ind*2+1], ind*2+1);
    if(data[ind] >= data[k])  // heap 조건을 만족할 경우 여기서 걸러질 것임
        return;
    swap(&data[ind], &data[k]);   // heap 조건을 만족하지 못한다면 부모와 자식 노드를 교체
    MaxHeapify(data, k);
}
void BuildMax(int *data)
{
    for(int i = N/2; i >= 1; i--)
        MaxHeapify(data, i);        
}
void HeapSort(int *data)
{
    BuildMax(data);
    for(int i = heapsize; i >= 2; i--)
    {
        swap(&data[1], &data[i]);
        heapsize--; // heapsize를 줄여 뒤에 정렬된 것들은 없는 것으로 간주 (건드리면 안됨)
        MaxHeapify(data, 1);
    }
}
int main(void)
{
    int *data;
    printf("insert numbers : ");
    scanf("%d", &N);
    heapsize = N;
    data = (int*)malloc(sizeof(int)*N+1);
    for(int i = 1; i <= N; i++)
        scanf("%d", &data[i]);

    data[0] = 0;
    HeapSort(data);
    for(int i = 1; i <= N; i++)
        printf("%d ", data[i]);
    free(data);
    return 0;
}
