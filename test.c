// 숙제 : 미로찾기
#include <stdio.h>
#include <stdbool.h>
#define PATHWAY_COLOUR 0 // 통로 -> ALREADY
#define WALL_COLOUR 1 // 벽 -> ALREADY
#define BLOCKED_COLOUR 2
#define PATH_COLOUR 3


bool findPath(int maze[8][8], int x, int y)
{
    if(x < 0 || y < 0 || x >= 8 || y >= 8)
        return false;
    else if(maze[x][y] != PATHWAY_COLOUR) // 통로가 아니라면 중지
        return false;
    else if(x == 7 && y == 7) //위에서 걸러지지 않고 BOUNDARY에 도달했다면 갈 수 있는 통로다.
    {
        maze[x][y] = PATH_COLOUR; // 통로로 표시하고 TRUE 반환
        return true;
    }
    else
    {
        maze[x][y] = PATH_COLOUR;
        if(findPath(maze, x-1, y) || findPath(maze, x, y-1) 
        || findPath(maze, x+1, y) || findPath(maze, x, y+1))
            return true;
        maze[x][y] = BLOCKED_COLOUR;
        return false;
    }
}

int main(void)
{
    int i = 0, j = 0;
    bool can = false;
    int maze[8][8] = {
        { 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1 },
        { 0, 1, 0, 0, 1, 1, 0, 0 },
        { 0, 1, 1, 1, 0, 0, 1, 1 },
        { 0, 1, 0, 0, 0, 1, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1 },
        { 0, 1, 1, 1, 0, 1, 0, 0 }
    };
    can = findPath(maze, 0, 0);
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
            printf("%d ", maze[i][j]);

        printf("\n");
    }
    return 0;
}