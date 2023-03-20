#include "def.h"

extern block**map;
extern int n;
extern int x, y;
extern int last;
void block::mark_init()
{
    if (state == edges || state == route)
        mark = 1;
    else
        mark = 0;
}
void block::mode1_state_init(int x, int y, int n)
{
    if (x == 0 || y == 0 || x == n - 1 || y == n - 1)
        state = edges;
    else if (x == 1 && y == 1)
        state = route;
    else
        state = wall;
}
void block::mode2_state_init(int x, int y, int n)
{
    if (x == 0 || y == 0 || x == n - 1 || y == n - 1)
        state = edges;
    else
        state = route;

}
void block::mode3_state_init(int x, int y, int n)
{
    if (x == 0 || y == 0 || x == n - 1 || y == n - 1)
        state = edges;
    else if (x%2 == 0 || y%2 == 0)
        state = wall;
    else
        state = route;
}