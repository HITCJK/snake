#include "field.hpp"
#include <easyx.h>

field::field()
{
    initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
    setbkcolor(LIGHTGRAY);
    cleardevice();
    BeginBatchDraw();
    setlinecolor(WHITE);
    for (int i = BLOCK_SIZE; i < WIDTH * BLOCK_SIZE; i += BLOCK_SIZE)
    {
        line(i, 0, i, HEIGHT * BLOCK_SIZE);
    }
    for (int i = BLOCK_SIZE; i < HEIGHT * BLOCK_SIZE; i += BLOCK_SIZE)
    {
        line(0, i, WIDTH * BLOCK_SIZE, i);
    }
    FlushBatchDraw();
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            map[i][j] = 0;
        }
    }
}

field::~field()
{
    EndBatchDraw();
    closegraph();
}

void field::draw()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (map[i][j] == 1)
            {
                // 画蛇
            }
            else if (map[i][j] == 2)
            {
                // 画食物
            }
            else if (map[i][j] == 3)
            {
                // 画障碍物
            }
        }
    }
}