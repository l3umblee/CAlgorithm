#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N, pnum = 1;
typedef struct bnode {
    struct bnode *parent;
    struct bnode *left;
    int num;
    struct bnode *right;
} bstnode;
bstnode* root;

void PrintFunc(bstnode* t)
{
    bstnode* ptr;
    ptr = t;
    if(ptr != NULL)
    {
        printf("address : %p / left : %p / num : %d / right : %p\n", ptr, ptr->left, ptr->num, ptr->right);
        PrintFunc(ptr->left);
        PrintFunc(ptr->right);
    }
    else
        return;
}

void InsertFunc(bstnode* t, int tmp)
{
    bstnode* y = NULL; // x노드 보다 위에 있는 노드
    bstnode* x = t;
    bstnode* ins = malloc(sizeof(bstnode));
    ins->num = tmp;
    ins->left = NULL;
    ins->right = NULL;
    while(x != NULL) // 리프노드를 찾아감 -> 이 반복문을 나온다면 x는 리프노드에 도달한 상태... x는 NULL값을 가지고 있다
    {
        y = x;
        if(ins->num < x->num)
            x = x->left;
        else
            x = x->right;
    }
    ins->parent = y;
    if(y == NULL)  // 만약 tree가 비어있다면 -> while문을 그냥 빠져나왔기 때문
    {
        root->num = tmp;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if(ins->num < y->num)
            y->left = ins;
        else
            y->right = ins;
    }
}

bstnode* MinFunc(bstnode* p)
{
    bstnode* ptr = p;
    while(ptr->left != NULL)
        ptr = ptr->left;
    return ptr;
}

bstnode* SuccessorFunc(bstnode* cur)
{
    bstnode* x = cur;
    if(x->right != NULL)
        return MinFunc(x->right);
    bstnode* y = cur->parent;
    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

bstnode* SearchFunc(bstnode* t, int tmp)
{
    bstnode* ptr = t;
    if(ptr == NULL || ptr->num == tmp)
        return ptr;
    if(tmp < ptr->num)
        return SearchFunc(ptr->left, tmp);
    else
        return SearchFunc(ptr->right, tmp);
}

void DeleteFunc(bstnode* t, bstnode* cur, int tmp)
{
    bstnode* x;
    bstnode* y;
    bstnode* ptr = cur;
    if(ptr->left == NULL || ptr->right == NULL)
        y = ptr;
    else
        y = SuccessorFunc(ptr);

    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if(x != NULL)
        x->parent = y->parent;

    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
  
    if(y != ptr)
        ptr->num = y->num;
    free(y);
}
int MenuFunc(void)
{
    int m;
    printf("1. insert / 2. delete / 3. search / 4. quit\n");
    printf("> ");
    scanf("%d", &m);
    return m;
}

int main(void)
{
    int tmp, menu = 0;
    printf("first size : ");
    scanf("%d", &N);
    printf("insert root : ");
    scanf("%d", &tmp);
    root = (bstnode*)malloc(sizeof(bstnode));
    root->num = tmp;
    root->left = NULL;
    root->right = NULL;
    for(int i = 0; i < N-1; i++)
    {
        tmp = 0;
        printf("insert num : ");
        scanf("%d", &tmp);
        InsertFunc(root, tmp);
    }
    PrintFunc(root);
    while(1)
    {
        menu = MenuFunc();
        if(menu == 1)
        {
            printf("insert num : ");
            scanf("%d", &tmp);
            InsertFunc(root, tmp);
            PrintFunc(root);
        }
        else if(menu == 2)
        {
            printf("delete num : ");
            scanf("%d", &tmp);
            bstnode* cur;
            cur = SearchFunc(root, tmp);
            DeleteFunc(root, cur, tmp);
            PrintFunc(root);
        }
        else if(menu == 3)
        {
            bstnode* ptr;
            printf("search num : ");
            scanf("%d", &tmp);
            ptr = SearchFunc(root, tmp);
            if(ptr == NULL)
                printf("no value here!\n");
            else
                printf("address : %p / left : %p / num : %d / right : %p\n", ptr, ptr->left, ptr->num, ptr->right);
        }
        else
            break;
    }
    free(root);
}
