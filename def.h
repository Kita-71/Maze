#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<vector>
#include<queue>
#include <algorithm>
#include "acllib.h"
using namespace std;
#define edges 2
#define wall 1
#define route 0
#define player 3
#define ok 4
//


class Point
{
public:
    int li, lj;
};
class block
{
public:
    int state;
    int mark;
    int x;
    int y;
    Point root;

    void mode1_state_init(int x, int y, int n);
    void mode2_state_init(int x, int y, int n);
    void mode3_state_init(int x, int y, int n);
    void mark_init();
};

//�ݹ���ݺ���
void backtracker();
void make_route(int x, int y, int i);
//�ݹ�ָ��
void division();
void openwall();
void divide(int left, int right, int top, int bottom);
//prim����
void prim();
void find_root(Point* current);
void back(int nx, int ny);
//gui���
void paint_background();//������
void paint_map();//����ͼ
void choose(int x, int y, int button, int event);//ѡ�����׳̶�
void keyControl(int key, int event);//���̿���
void time_event(int TimeID);//ʤ���жϡ���ʱ�����Ʋ���
//�Զ�Ѱ·���
void dfs(int dx,int dy,int i);//�Զ�Ѱ·
void bfs();


