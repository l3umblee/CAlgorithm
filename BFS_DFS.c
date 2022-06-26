#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct graphNode {
    int vertex;
    struct graphNode* link;
} graphNode; // 노드 한 개

typedef struct graphType {
    int n;
    graphNode** adjList_h;
    int* visited;
} graphType; // 노드들을 리스트에다가 저장해두기 위한 구조체

typedef struct QNode {
    int data;
    struct QNode *link;
} QNode; // 큐를 위한 노드

typedef struct {
    QNode *front, *rear;
} LQueueType; // 상자라고 생각

typedef struct stackNode {
    int data;
    struct stackNode *link;
} stackNode;

stackNode* top;

LQueueType *createLinkedQueue(void)  // 처음 공백의 큐를 생성 -> 당연히 front와 rear 모두 NULL
{
    LQueueType *LQ;
    LQ = (LQueueType*)malloc(sizeof(LQueueType));
    LQ->front = NULL;
    LQ->rear = NULL;
    return LQ;
}

int isEmptyS()
{
    if(top == NULL) return 1;
    else return 0;
}

int isEmptyQ(LQueueType *LQ)
{
    if(LQ->front == NULL)
    {
        printf("\nLinked Queue is empty!\n");
        return 1;
    }
    else return 0;
}

void push(int item)
{
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    temp->data = item;
    temp->link = top;
    top = temp;
}

int pop()
{
    int item;
    stackNode* temp = top;
    if(isEmptyS())
    {
        printf("\nStack is empty!\n");
        return 0;
    }
    else
    {
        item = temp->data;
        top = temp->link;
        free(temp);
        return item;
    }
}

void enQueue(LQueueType *LQ, int item)
{
    QNode *newNode = (QNode*)malloc(sizeof(QNode));
    newNode->data = item;
    newNode->link = NULL;
    if(LQ->front == NULL) // 처음 들어가는 노드 또는 큐 상자에 아무것도 없다면 새로 추가한 newNode를 front이자 rear로 등록
    {
        LQ->front = newNode;
        LQ->rear = newNode;
    }
    else // 그것이 아니라면 rear에 있던 node의 link를 newNode로 가리키게 하고, rear은 newNode로 등록
    {
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
}

int deQueue(LQueueType *LQ)
{
    QNode *old = LQ->front;
    int item;
    if(isEmptyQ(LQ)) return 0;
    else
    {
        item = old->data;
        LQ->front = LQ->front->link; // front는 front가 link하던 node로 다시 등록
        if(LQ->front == NULL) // 비어있는 상자 였다면...
            LQ->rear = NULL;
        free(old);
        return item;
    }
}

void createGraph(graphType* g, int N) // 처음 공백 그래프 구현 -> N은 동적할당을 위한 변수
{
    g->n = 0; // 정점 개수 0으로 초기화
    g->adjList_h = (graphNode**)malloc(sizeof(graphNode*)*N);
    g->visited = (int*)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
        g->adjList_h[i] = (graphNode*)malloc(sizeof(graphNode));
    for(int i = 0; i < N; i++)
    {
        g->adjList_h[i] = NULL; // 그래프의 정점에 대한 헤드 포인터 배열을 NULL로 초기화
        g->visited[i] = 0;
    }
}

void insertVertex(graphType* g, int v, int N) // 정점 삽입 -> 초기에 createGraph와 함께 쓰이고 다시는 안쓰일 듯.
{
    if(((g->n)+1) > N)
    {
        printf("\n the number of node is overload!\n");
        return;
    }
    g->n++;
}

void insertEdge(graphType* g, int u, int v) // 간선 삽입 -> 노드 간의 간선 삽입.
{
    graphNode* node;
    if(u >= g->n || v >= g->n)
    {
        printf("u : %d, v : %d, g->n : %d\n", u, v, g->n);
        printf("that node is not in this graph!\n");
        return;
    }
    node = (graphNode*)malloc(sizeof(graphNode));
    node->vertex = v;
    node->link = g->adjList_h[u]; // 삽입 간선에 대한 노드를 리스트의 첫번째 노드로 연결
    g->adjList_h[u] = node;
}

void BfsFunc(graphType* g, int v) // 정점 v에 대한 너비 우선 탐색 연산
{
    graphNode* w;
    LQueueType* Q;
    Q = createLinkedQueue();
    g->visited[v] = 1;
    printf(" %c ", v+65);
    enQueue(Q, v);

    while(!isEmptyQ(Q))
    {
        v = deQueue(Q);
        for(w = g->adjList_h[v]; w; w = w->link) // 인접 정점이 있는 동안 수행
        {
            if(!g->visited[w->vertex]) // 정점 w가 방문하지 않은 정점인 경우
            {
                g->visited[w->vertex] = 1;
                printf(" %c ", w->vertex+65);
                enQueue(Q, w->vertex);
            }
        }
    } // 큐가 공백이면 너비 우선탐색 종료
}

void DfsFunc(graphType* g, int v) // 정점 v에 대한 깊이 우선 탐색 연산
{
    graphNode* w;
    top = NULL;
    push(v);
    g->visited[v] = 1;
    printf(" %c ", v+65);

    while(!isEmptyS())
    {
        v = pop();
        w = g->adjList_h[v];
        while(w)
        {
            if(!g->visited[w->vertex])
            {
                if(isEmptyS())  push(v);
                push(w->vertex);
                g->visited[w->vertex] = 1;
                printf(" %c ", w->vertex+65);
                v = w->vertex;
                w = g->adjList_h[v];
            }
            else    w = w->link; // 현재 정점 w가 이미 방문된 경우
        }
    } // 스택이 공백이면 깊이 우선 탐색 종료
}

void PrintFunc(graphType* g)
{
    int i;
    graphNode* p;
    printf("\nPrintFunc loaded!");
    for(i = 0; i < g->n; i++)
    {
        printf("\n\t\tnode %c's neighbour list", i+65);
        p = g->adjList_h[i];
        while(p)
        {
            printf("->%c", p->vertex+65);
            p = p->link;
        }
    }
    printf("\n");
}

int MenuFunc(void)
{
    int m;
    printf("1. link / 2. BFS / 3. DFS / 4. quit\n");
    printf("> ");
    scanf("%d", &m);
    return m;
}

int main(void)
{
    int N, menu = 0;
    graphType *g;

    printf("insert the number of first graph : ");
    scanf("%d", &N);
    g = (graphType*)malloc(sizeof(graphType));
    createGraph(g, N);
    for(int i = 0; i < N; i++)
        insertVertex(g, i, N); // 그래프의 정점 개수 바꿔줌
     
    menu = MenuFunc();
    while(1)
    {
        if(menu == 1)
        {
            int a = 0, u = 0, v = 0;
            printf("linkFunc loaded!\n");
            printf("the number of inserting node's adj node : ");
            scanf("%d", &a);
            for(int i  =0; i < a; i++)
            {
                printf("u: ");  scanf("%d", &u);
                printf("v: ");  scanf("%d", &v);
                insertEdge(g, u, v);   
            }
        }
        else if(menu == 2)
        {
            printf("BFS func loaded\n");
            BfsFunc(g, 0);
        }
        else if(menu == 3)
        {
            printf("DFS func loaded\n");
            DfsFunc(g, 0);
            
        }
        else
            break;
            
        PrintFunc(g);
        menu = MenuFunc();
        for(int j = 0; j < N; j++)
            g->visited[j] = 0;
    }

    free(g);
    return 0;
}
