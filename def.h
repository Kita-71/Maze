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

//递归回溯函数
void backtracker();
void make_route(int x, int y, int i);
//递归分割函数
void division();
void openwall();
void divide(int left, int right, int top, int bottom);
//prim函数
void prim();
void find_root(Point* current);
void back(int nx, int ny);
//gui相关
void paint_background();//画背景
void paint_map();//画地图
void choose(int x, int y, int button, int event);//选择难易程度
void keyControl(int key, int event);//键盘控制
void time_event(int TimeID);//胜利判断、计时器、计步器
//自动寻路相关
void dfs(int dx,int dy,int i);//自动寻路
void bfs();


