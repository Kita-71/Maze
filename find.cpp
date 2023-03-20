#include"def.h"
extern block** map;
extern int n;
extern int a;
extern int x, y;
extern int last;
extern int endx, endy;


void bfs()
{
    int dir[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0} }; //选定搜索的四个方向
    int cx = 1, cy =1;//当前访问点所在位置
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
            map[i][j].root.li = i;
            map[i][j].root.lj = j;
        }

    queue<block> walls;
    walls.push(map[1][1]);
    map[1][0].mark = 2;
    block current;
    while (!walls.empty())
    {
        if (cx != n - 2 || cy != n - 1)
        {
            for (int j = 0; j < 4; j++)
            {
                cx = walls.front().x + dir[j][0];
                cy = walls.front().y + dir[j][1];
                if (map[cx][cy].state == route && map[cx][cy].mark != 2)
                {
                    map[cx][cy].mark = 2;
                    walls.push(map[cx][cy]);
                    map[cx][cy].root.li = map[walls.front().x][walls.front().y].x;
                    map[cx][cy].root.lj = map[walls.front().x][walls.front().y].y;
                }
                if (cx == n - 2 && cy == n - 1)
                    break;
            }
            walls.pop();
        }
        else
        {
            while (!walls.empty())
            {
                walls.pop();
            }
            back(n - 2, n - 1);
        }
    }
}
void back(int nx, int ny)
{
    if (nx == 1 && ny == 1)
        return;
    map[nx][ny].state = ok;
    back(map[nx][ny].root.li, map[nx][ny].root.lj);
    return;
}
void dfs(int dx, int dy, int come_dir)
{
    int dir[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0} }; //选定搜索的四个方向
    if (map == NULL)
        return;
    map[dx][dy].state = ok;
    if (dx == endx && dy == endy)
    {
        a = 1;
        return;
    }//找到终点 回退

    for (int j = 0; j < 4; j++)
    {
        if (j != 3 - come_dir)
        {
            if (map[dx + dir[j][0]][dy + dir[j][1]].state == route)
            {
                dfs(dx + dir[j][0], dy + dir[j][1], j);
                if (a == 1)
                    return;
            }
        }
    }
    map[dx][dy].state = route;
    return;
}
