#include "def.h"

extern block**map;
extern int n;
extern int x, y;
extern int last;
extern int a;
extern int Times;
extern int Steps;
extern int endx, endy;
int mode=0;
void paint_background()
{
    ACL_Image *float_icon = new ACL_Image;
    loadImage("float.jpg", float_icon);
    beginPaint();
    putImageScale(float_icon, 0, 0, 1120, 630);
    endPaint();
}
void paint_map()
{
    ACL_Image* ok_icon = new ACL_Image;
    loadImage("wall.jpg", ok_icon);
    ACL_Image *wall_icon = new ACL_Image;
    loadImage("wall2.jpg", wall_icon);
    ACL_Image *start_icon = new ACL_Image;
    loadImage("start.jpg", start_icon);
    ACL_Image *end_icon = new ACL_Image;
    loadImage("end.jpg", end_icon);
    ACL_Image *player_icon = new ACL_Image;
    loadImage("player.gif", player_icon);

    int wideth = (getHeight() - 60) / n;

    beginPaint();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (map[i][j].state == edges || map[i][j].state == wall)
                putImageScale(wall_icon, (100 + j * wideth), (30 + i * wideth), wideth, wideth);
            if (i == 1 && j == 0)
                putImageScale(start_icon, (100 + j * wideth), (30 + i * wideth), wideth, wideth);
            if (map[i][j].state == route && j == n - 1)
                putImageScale(end_icon, (100 + j * wideth), (30 + i* wideth), wideth, wideth);
            if (map[i][j].state == player)
                putImageScale(player_icon, (100 + j * wideth), (30 + i * wideth), wideth, wideth);
            if(map[i][j].state==ok)
                putImageScale(ok_icon, (100 + j * wideth), (30 + i* wideth), wideth, wideth);
        }

    endPaint();
}
void choose(int wx, int wy, int button, int event)
{

    if (button == LEFT_BUTTON && event == BUTTON_DOWN)
    {

        if (wx > 815 && wx < 1017 && wy > 125 && wy < 245)
        {
            mode = 0;
            a = 0;
            beginPaint();
            clearDevice();
            endPaint();
            paint_background();
            n =35;
            Times = 0;
            Steps = 0;
            division();
        }
        if (wx > 710 && wx < 915 && wy > 287 && wy < 425)
        {
            mode = 1;
            a = 0;
            beginPaint();
            clearDevice();
            endPaint();
            paint_background();
            n = 35;
            Times = 0;
            Steps = 0;
            backtracker();
        }
        if (wx > 915 && wx < 1116 && wy > 287 && wy < 425)
        {
            mode = 1;
            a= 0;
            beginPaint();
            clearDevice();
            endPaint();
            paint_background();
            n = 35;
            Times = 0;
            Steps = 0;
            prim();
        }
        if (wx > 0 && wx < 100 && wy>0 && wy < 100)
        {
            if (mode == 1)
            {
                map[x][y].state = route;
                x = 1;
                y = 0;
                dfs(1, 0, 3);
            }
            else
                bfs();
            beginPaint();
            clearDevice();
            endPaint();
            paint_background();
            paint_map();

        }
    }
}
void keyControl(int key, int event)
{
    if (key == 0x25 && event == BUTTON_DOWN && map[x][y - 1].state == route)
    { //按键 ↑
        map[x][y].state = route;
        map[x][y - 1].state = player;
        y = y - 1;
        Steps++;
        beginPaint();
        clearDevice();
        endPaint();
        paint_background();
        paint_map();
    }
    if (key == 0x27 && event == BUTTON_DOWN && map[x][y + 1].state == route)
    { //按键 ↓
        map[x][y].state = route;
        map[x][y + 1].state = player;
        y = y + 1;
        Steps++;
        beginPaint();
        clearDevice();
        endPaint();
        paint_background();
        paint_map();
    }
    if (key == 0x26 && event == BUTTON_DOWN && map[x - 1][y].state == route)
    { //按键 ←
        map[x][y].state = route;
        map[x - 1][y].state = player;
        x = x - 1;
        Steps++;
        beginPaint();
        clearDevice();
        endPaint();
        paint_background();
        paint_map();
    }
    if (key == 0x28 && event == BUTTON_DOWN && map[x + 1][y].state == route)
    { //按键 →
        map[x][y].state = route;
        map[x + 1][y].state = player;
        x = x + 1;
        Steps++;
        beginPaint();
        clearDevice();
        endPaint();
        paint_background();
        paint_map();
    }
}
void time_event(int TimeID)
{
    //胜利判断
    if (TimeID == 0)
    {
        char* tip = new char[100];
        strcpy(tip, "You win!");
        if (map != NULL)
        {
            if (map[endx][endy].state == player)
            {
                beginPaint();
                setTextColor(WHITE);
                setTextBkColor(BLACK);
                setTextSize(50);
                paintText(752, 20, tip);
                endPaint();
            }
        }
        delete[] tip;
    }
    //时间计算
    if (TimeID == 2)
    {
        Times++;
    }
    //步数计算
    if (TimeID == 4)
    {
        char* s = new char[100];
        char* t = new char[100];
        _itoa(Times, t, 10);
        _itoa(Steps, s, 10);
        beginPaint();
        setTextColor(WHITE);
        setTextBkColor(BLACK);
        setTextSize(20);
        paintText(752, 155, s);
        paintText(752, 212, t);
        endPaint();
        delete[] s;
        delete[] t;
    }

}