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
void MaxHeapInsert(int* data, int key)
{
    data[heapsize] = key;
    int i = heapsize;
    while(i > 1 && data[i/2] < data[i])
    {
        swap(&data[i], &data[i/2]);
        i /= 2;
    }
}
int ExtractMax(int* data)
{
    if(heapsize < 1)
        printf("heap underflow\n");
    int max = data[1];
    data[1] = data[heapsize];
    free(&data[heapsize]);
    heapsize--; N--;
//  data = (int*)realloc(data, sizeof(int)*N+1);        // 둘 다 가능
    MaxHeapify(data, 1);
    return max;
}
void Printfunc(int* data)
{
    for(int i = 1; i <= N; i++)
        printf("%d ", data[i]);
    printf("\n");
}

int main(void)
{
    int choice = 1, num;
    int *data;
    printf("how many? : ");
    scanf("%d", &N);
    heapsize = N;
    data = (int*)malloc(sizeof(int)*N+1);
    printf("insert numbers\n");
    for(int i = 1; i <= N; i++)
        scanf("%d", &data[i]);

    data[0] = 0;
//  HeapSort(data); 
//  우선 순위 큐를 진행할 때 heapsort를 진행시켜주면 이미 오름차순으로 배열이 정렬되기 때문에 extractmax를 보기 어려움
    Printfunc(data);
    
    do {
        printf("you want more numbers? (1. yes / 2. no) : ");
        scanf("%d", &choice);
        if(choice == 2)
            break;
        int max;
        printf("insert numbers\n");
        scanf("%d", &num);
        N++;    heapsize = N;
        data = (int*)realloc(data, sizeof(int)*N+1);
        MaxHeapInsert(data, num);
        printf("insert result\n");
        Printfunc(data);
        max = ExtractMax(data);
        printf("extract max : result : %d\n", max);
        HeapSort(data);
        printf("heap sorted\n");
        Printfunc(data);
    } while(choice != 2);
    free(data);
    return 0;
}
