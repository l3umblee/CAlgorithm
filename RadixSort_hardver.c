#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N, d;
void PrintFunc(char **data, int num)
{
    for(int i = 0; i < num; i++)
        printf("%s", data[i]);
}

void CountingSort(char **data, char **result, int num) // num은 자릿수 의미
{
    int tempo, tempt;
    int *cnt;
    cnt = (int*)malloc(sizeof(int)*10);
    for(int i = 0; i < 10; i++)
        cnt[i] = 0;
    for(int i = 0; i < N; i++)
    {
        tempo = data[i][num-1] - 48;
        cnt[tempo] += 1;
    }
    for(int j = 1; j < 10; j++)
        cnt[j] += cnt[j - 1];
    for(int j = N-1; j >= 0; j--)
    {
        tempt = data[j][num-1] - 48;
        int c = cnt[tempt], d = tempt;
        strcpy(result[c-1], data[j]);
        cnt[d] = c-1;
    }
    for(int j = 0; j < N; j++)
        strcpy(data[j], result[j]);
    free(cnt);
}

void RadixSort(char **data, char **result, int d)
{
    for(int i = d; i > 0; i--)
        CountingSort(data, result, i);
}

int main(void)
{
    char **data, **result;
    printf("degree : " );
    scanf("%d", &d);
    printf("size : " );
    scanf("%d", &N);
    data = (char**)malloc(sizeof(char*)*N);
    result = (char**)malloc(sizeof(char*)*N);
    for(int i = 0; i < N; i++)
    {
        data[i] = (char*)malloc(sizeof(char)*d);
        result[i] = (char*)malloc(sizeof(char)*d);
    }
    for(int i = 0; i < N; i++)
        scanf("%s", data[i]);

    RadixSort(data, result, d);

    for(int i = 0; i < N; i++)
        printf("%s ", result[i]);

    for(int i = 0; i < N; i++)
    {
        free(data[i]);
        free(result[i]);
    }
    free(data);
    free(result);
    return 0;
}
