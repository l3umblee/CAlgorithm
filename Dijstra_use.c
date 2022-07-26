/* 다익스트라 알고리즘을 이용하여 둥지 상가에서 나가는 가장 빠른 출구 알아보기 */
#include <stdio.h>
#include <limits.h>

#define INF 999
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10

int weight[MAX_VERTICES][MAX_VERTICES] = {
    {0, 3, 6, INF, INF, INF, INF, INF, INF, INF}, //1번째 행
    {3 ,0, 5, INF, INF, INF, 3, INF, INF, INF}, // 2번째 행
    {6, 5, 0, 3, INF, INF, 2, INF, INF, INF}, // 3번째 행
    {INF, INF, 3, 0, 2, INF, 2, INF, INF, INF}, // 4번째 행
    {INF, INF, INF, 2, 0, INF, 1, INF, INF, INF}, // 5번째 행
    {INF, INF, INF, INF, INF, 0, 5, 4, INF, INF}, // 6번째 행
    {INF, 3, 2, 2, 1, 5, 0, INF, 5, INF}, // 7번째 행
    {INF, INF, INF, INF, INF, 4, INF, 0, 3, INF}, // 8번째 행
    {INF, INF, INF, INF, INF, INF, 5, 3, 0, INF}, // 9번째 행
    {INF, 2, INF, INF, INF, INF, INF, INF, 1, INF}, // 10번째 행 -> 여기서 2번째 인덱스와 9번째 인덱스는 계단에 해당
};
int distance[MAX_VERTICES];
int S[MAX_VERTICES];

int nextVertex(int n) {
    int i, min, minPos;
    min = INT_MAX;
    minPos = -1;
    for(i = 0; i < n; i++) {
        if((distance[i] < min) && !S[i]) {
            min = distance[i];
            minPos = i;
        }
    }
    return minPos;
}

int printStep(int step) {
    int i;
    printf("\n %3d th : S = { ", step);
    for(i = 0; i < MAX_VERTICES; i++) {
        if(S[i] == TRUE)
            printf("%3c", i+65);
    }
    if(step < 1) printf(" } \t\t\t");
    else if(step < 4) printf(" } \t\t");
    else printf(" } \t");
    printf(" distance : [");
    for(i = 0; i < MAX_VERTICES; i++) {
        if(distance[i] == INF)
            printf("%4c", '*');
        else printf("%4d", distance[i]);
    }
    printf("%4c", ']');
    return ++step;
}

void Dijkstra_shortestPath(int start, int n) {
    int i, u, w, step = 0;

    for(i = 0; i < n; i++) {
        distance[i] = weight[start-1][i];
        S[i] = FALSE;
    }

    S[start-1] = TRUE;
    distance[start-1] = 0;

    step = printStep(0);

    for(i = 0; i < n - 1; i++) {
        u = nextVertex(n);
        S[u] = TRUE;
        for(w = 0; w < n; w++) {
            if(!S[w])
                if(distance[u]+weight[u][w] < distance[w])
                    distance[w] = distance[u] + weight[u][w];
            step = printStep(step);
        }
    }
}

int main(void) {
    int i, j, min, cnt = 0, rem = 0, way_1, way_2, way_3;
    int array[10] = { 0 };
    printf("\n **************************************************\n\n");
    for(i = 0; i < MAX_VERTICES; i++) {
        for(j = 0; j < MAX_VERTICES; j++) {
            if(weight[i][j] == INF)
                printf("%4c", '*');
            else printf("%4d", weight[i][j]);
        }
        printf("\n\n");
    }
    printf("\n****************************************************\n\n");
    Dijkstra_shortestPath(10, MAX_VERTICES);
    way_1 = distance[0];
    way_2 = distance[4];
    way_3 = distance[7];
    printf("\nyour fastest way to out is...\n");
    if(way_1 < way_2 && way_1 < way_3) printf("\nway_1 : %d\n", distance[0]);
    else if(way_2 < way_3 && way_2 < way_1) printf("\nway_2 : %d\n", distance[4]);
    else printf("\nway_3 : %d\n", distance[7]);

    return 0;
}
