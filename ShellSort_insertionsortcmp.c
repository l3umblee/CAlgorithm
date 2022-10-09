#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
<Shell Sorting>
Shell Sorting은 Insertion Sorting에서 착안
Shell 변수만큼 gap을 가지면서 Insertion Sorting을 수행

쉽게 생각해서 기존의 InsertionSorting은 1씩 key값을 선정하고 비교하며 바꿔갔다면
Shell Sorting은 shell변수만큼 key값을 선정하고 비교하며 바꿔가는 것!
*/
void InsertionSortingforShellSorting(int *data, int size, int first, int shell) {
    int key, tmp;
    for(int i = first + shell; i < size; i=i+shell) {
        key = i;
        for(int j = 0; j < i; j+=shell) {
            if(*(data+j) > *(data+key)) {
                tmp =  *(data+j);
                *(data+j) = *(data+key);
                *(data+key) = tmp;
            }
        }
    }
}

double ShellSorting(int *data, int size) {
    double start, end;
    start = (double)clock() / CLOCKS_PER_SEC;
    int shell = size/2; 
    int ind = 0, tmp;
    while(shell >= 1) {
        for(int i = 0; i < shell; i++) {
            InsertionSortingforShellSorting(data, size, i, shell); 
        }
        shell /= 2;
    }
    end = (((double)clock())/CLOCKS_PER_SEC);
    return (end-start);
}

double InsertionSorting(int* data, int size) {
    double start, end;
    start = (double)clock() / CLOCKS_PER_SEC;
    int key, tmp;
    for(int i = 1; i < size; i++) {
        key = i;
        for(int j = 0; j < i; j++) {
            if(*(data+j) > *(data+key)) {
                tmp = *(data+j);
                *(data+j) = *(data+key);
                *(data+key) = tmp;
            }
        }
    }
    end = (((double)clock())/CLOCKS_PER_SEC);
    return (end-start);
}

int CheckFunc(int* sdata, int* idata, int size) {
    for(int i = 0; i < size; i++) {
        if(*(sdata+i) != *(idata+i))
            return 0; 
    }
}

int main(void) {
    srand(time(NULL));
    int size = 60000;
    int *data = (int*)malloc(sizeof(int)*size);
    int *copy = (int*)malloc(sizeof(int)*size);
    double stime, itime;
    for(int i = 0; i < size; i++) {
        *(data+i) = rand()%21;
        *(copy+i) = *(data+i);
    }

    printf("\n");
    stime = ShellSorting(data, size);
    itime = InsertionSorting(copy, size);

    printf("\n");
    printf("size : %d\n", size);
    printf("shell sorting time : %lf\n", stime);
    printf("insertion sorting time : %lf\n", itime);
    if(CheckFunc(data, copy, size) == 0)
        printf("wrong!\n");
    else   
        printf("correct!\n");
    free(data);
    return 0;
}
