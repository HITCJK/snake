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
    // 屏蔽输入法
    ImmAssociateContext(GetHWnd(), NULL);
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
            if (map[i][j] == 0)
            {
                // 清空
                setfillcolor(LIGHTGRAY);
                fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
            }
            if (map[i][j] > 0)
            {
                // 画蛇
                setfillcolor(BLUE);
                fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
            }
            else if (map[i][j] == -1)
            {
                // 画食物
                setfillcolor(RED);
                fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
            }
            else if (map[i][j] == -2)
            {
                // 画障碍物
                setfillcolor(BLACK);
                fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
            }
        }
    }
    FlushBatchDraw();
}

void field::init()
{
    snake = new class snake(15, 20, RIGHT);
}

// void field::check()
// {

// }

void field::refresh()
{
    snake->changedirection();
    snake->move();
    int length = snake->getlength();
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            map[i][j] = 0;
        }
    }
    for (int i = 1; i <= length; i++)
    {
        map[snake->getx(i)][snake->gety(i)] = i;
    }
}