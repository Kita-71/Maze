#include "def.h"
block** map;
//һЩ��������
int Times;
int Steps;
int n;
int x, y;
int a = 0;
int endx, endy;

int Setup()
{
    initWindow("Kita���Թ�", DEFAULT, DEFAULT, 1120, 630);
    paint_background();
    registerMouseEvent(choose);
    registerKeyboardEvent(keyControl);
    registerTimerEvent(time_event);
    srand(time(NULL));
    startTimer(0, 100);
    startTimer(4, 10);
    startTimer(2, 1000);
    return 0;
}

