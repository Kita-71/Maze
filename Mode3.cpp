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
    //���鼯�ݹ��յ㣺Դ���Լ�
    if (map[current->li][current->lj].root.li == current->li && map[current->li][current->lj].root.lj == current->lj)
    {
        //p��¼���ڵ�
        p = &map[current->li][current->lj].root;
        return;
    }
    find_root(&map[current->li][current->lj].root);
    //��ѯ�Ż�
    current->li = p->li;
    current->lj = p->lj;
    return;
}
void prim()
{
    //���Թ�
    map = new block * [n];
    for (int i = 0; i < n; i++)
    {
        map[i] = new block[n];
    }
    //��ʼ���Թ�
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            map[i][j].mode3_state_init(i, j, n);
            map[i][j].root.li = i;
            map[i][j].root.lj = j;
            //�ɴ�ͨ��ǽ���
            if (map[i][j].state == wall&&!(i%2==0&&j%2==0))
                walls.push_back(map[i][j]);
        }
    //prim��ǽ
    openwall();
    x = 1;
    y = 1;
    map[x][y].state = player;
    //����յ�
    map[1][0].state = route;
    map[n - 2][n - 1].state = route;
    //��¼�յ�
    endx = n - 2;
    endy = n - 1;
    paint_map();
}
void openwall()
{
    //���ɴ�ͨ��ǽ�ڶ����е�˳�����
   random_shuffle(walls.begin(),walls.end());
   //�Կɴ�ͨ��ǽ���ж�
   while (walls.empty()==false)
   {
       //��ȡ������λ�õ�ǽ������
       int cx = walls.front().root.li;
       int cy = walls.front().root.lj;
       //��ȡǽ���ܸ��ӵ�Դͷ
       find_root(&map[cx][cy-1].root);
       Point* left = p;
       find_root(&map[cx][cy + 1].root);
       Point* right = p;
       find_root(&map[cx-1][cy ].root);
       Point* top = p;
       find_root(&map[cx + 1][cy].root);
       Point* bottom = p;
       //��ǽ���ܵ�ǽ���ж�
       //���Ҹ���
       if (map[cx][cy - 1].state == route && map[cx][cy + 1].state == route)
       {
           if (left->li != right->li || left->lj != right->lj)
           {   
               //����ͬһ���Ӵ�ͨ�����²��鼯
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
               //��ͬһ���ϣ���ǽ����ͨ
               walls.erase(walls.begin());
               continue;
           }
       }
       if (map[cx - 1][cy].state == route && map[cx + 1][cy].state == route)
       {
           if (top->li != bottom->li || top->lj != bottom->lj)
           {
               //����ͬһ���Ӵ�ͨ�����²��鼯
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
               //��ͬһ���ϣ���ǽ����ͨ
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