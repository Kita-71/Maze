#include "def.h"

extern block** map;
extern int n;
extern int x, y;
extern int last;
extern int endx, endy;
void division()
{
    //创迷宫
    map = new block * [n];
    for (int i = 0; i < n; i++)
    {
        map[i] = new block[n];
    }
    //初始化迷宫
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            map[i][j].mode2_state_init(i, j, n);
            map[i][j].mark_init();
        }
    //递归分割
    divide(0, n - 1, 0, n - 1);
    //角色位置初始化
    x = 1;
    y = 1;
    map[x][y].state = player;
    //起点终点
    map[1][0].state = route;
    map[n - 2][n - 1].state = route;
    endx = n - 2;
    endy = n - 1;
    paint_map();
    

}
void divide(int left, int right, int top, int bottom)
{
    //不可再分割，递归终点
    if (right - left == 2 || bottom - top == 2)
        return;
    //选取十字墙的中心点
    int ax,ay;
    ax = left+2*((rand() % ((right - left-2) / 2))+1);
    ay = top+2*((rand() % ((bottom - top-2) / 2))+1);
    //建墙
    for (int i = left+1; i <=right-1; i++)
        map[i][ay].state = wall;
    for (int j = top + 1; j <= bottom - 1; j++)
        map[ax][j].state = wall;
    //在中心点的四个方向选三个墙打通
    int bx1,bx2,by1, by2;
    bx1= left + 2 * (rand() % ((ax - left) / 2))+1;
    by1= top + 2 * (rand() % ((ay - top) / 2))+1;
    bx2 = ax + 2 * (rand() % ((right - ax) / 2)) + 1;
    by2 = ay + 2 * (rand() % ((bottom - ay) / 2)) + 1;
    int where,times=1;
    int witch[4] = {0};
    while (times <= 3)
    {
        where = rand() % 4;
        if (witch[where] == 0)
        {
            switch (where)
            {
            case 0:
                    map[ax][by1].state = route;
                    break;
            case 1:
                    map[ax][by2].state = route;
                    break;
            case 2:
                    map[bx1][ay].state = route;
                    break;
            case 3:
                    map[bx2][ay].state = route;
                    break;
            }
            witch[where] = 1;
            times++;
        }
    }
    //对四个区域作递归分割
    divide(left, ax, top, ay);
    divide(left, ax, ay, bottom);
    divide(ax, right, top, ay);
    divide(ax, right, ay, bottom);
}