#include "def.h"

extern block**map;
extern int n;
extern int a;
extern int x, y;
extern int endx, endy;
void backtracker()
{
    
    //创迷宫
    map = new block *[n];
    for (int i = 0; i < n; i++)
    {
        map[i] = new block[n];
    }
    //初始化迷宫
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            map[i][j].mode1_state_init(i, j, n);
            map[i][j].mark_init();
        }
    //挖路
    make_route(1, 1, 0);
    //打印迷宫
    x = 1;
    y = 0;
    map[x][y].state = player;
    //起点终点
    map[1][0].state = route;
    for (int last = n - 2;; last--)
    {
        if (map[n - 2][last].state == route)
        {
            map[last][n - 1].state = route;
            endx = last;
            endy = n - 1;
            break;
        }
    }
    paint_map();
    return;
}
void make_route(int x, int y, int come_dir)
{
    int dir[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}}; //选定搜索的四个方向
    for (int j = 0; j < 4; j++)
    {
        if (j != 3 - come_dir)
        {
            if (map[x + dir[j][0]][y + dir[j][1]].state == route)
                return;
        }
    }
    map[x][y].state = route;
    int dx = x, dy = y;
    while (1)
    {
        come_dir = rand() % 4;
        dx = x + dir[come_dir][0];
        dy = y + dir[come_dir][1];
        if (map[dx][dy].mark != 1 && map[dx][dy].state != edges)
        {
            map[dx][dy].mark = 1;
            make_route(dx, dy, come_dir);
        }
        for (int j = 0; j < 4; j++)
        {
            if (map[x + dir[j][0]][y + dir[j][1]].mark == 0)
                break;
            else if (j == 3)
                return;
        }
    }
}

