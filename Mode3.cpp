#include "def.h"

extern block** map;
extern int n;
extern int a;
extern int x, y;
extern int last;
extern int endx, endy;
Point* p;
vector<block> walls;
void find_root(Point* current)
{
    //并查集递归终点：源自自己
    if (map[current->li][current->lj].root.li == current->li && map[current->li][current->lj].root.lj == current->lj)
    {
        //p记录根节点
        p = &map[current->li][current->lj].root;
        return;
    }
    find_root(&map[current->li][current->lj].root);
    //查询优化
    current->li = p->li;
    current->lj = p->lj;
    return;
}
void prim()
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
            map[i][j].mode3_state_init(i, j, n);
            map[i][j].root.li = i;
            map[i][j].root.lj = j;
            //可打通的墙入队
            if (map[i][j].state == wall&&!(i%2==0&&j%2==0))
                walls.push_back(map[i][j]);
        }
    //prim打墙
    openwall();
    x = 1;
    y = 1;
    map[x][y].state = player;
    //起点终点
    map[1][0].state = route;
    map[n - 2][n - 1].state = route;
    //记录终点
    endx = n - 2;
    endy = n - 1;
    paint_map();
}
void openwall()
{
    //将可打通的墙在队列中的顺序打乱
   random_shuffle(walls.begin(),walls.end());
   //对可打通的墙作判断
   while (walls.empty()==false)
   {
       //获取队列首位置的墙的坐标
       int cx = walls.front().root.li;
       int cy = walls.front().root.lj;
       //获取墙四周格子的源头
       find_root(&map[cx][cy-1].root);
       Point* left = p;
       find_root(&map[cx][cy + 1].root);
       Point* right = p;
       find_root(&map[cx-1][cy ].root);
       Point* top = p;
       find_root(&map[cx + 1][cy].root);
       Point* bottom = p;
       //对墙四周的墙作判断
       //左右格子
       if (map[cx][cy - 1].state == route && map[cx][cy + 1].state == route)
       {
           if (left->li != right->li || left->lj != right->lj)
           {   
               //不在同一格子打通，更新并查集
               map[cx][cy].state = route;
               left->li = right->li;
               left->lj = right->lj;
               map[cx][cy].root.li = right->li;
               map[cx][cy].root.lj = right->lj;
               walls.erase(walls.begin());
               continue;
           }
           else
           {
               //在同一集合，此墙不可通
               walls.erase(walls.begin());
               continue;
           }
       }
       if (map[cx - 1][cy].state == route && map[cx + 1][cy].state == route)
       {
           if (top->li != bottom->li || top->lj != bottom->lj)
           {
               //不在同一格子打通，更新并查集
               map[cx][cy].state = route;
               top->li = bottom->li;
               top->lj = bottom->lj;
               map[cx][cy].root.li = bottom->li;
               map[cx][cy].root.lj = bottom->lj;
               walls.erase(walls.begin());
               continue;
           }
           else
           {
               //在同一集合，此墙不可通
               walls.erase(walls.begin());
               continue;
           }
       }
       else
       {
           walls.push_back(walls.front());
           walls.erase(walls.begin());
       }
   }
   
}