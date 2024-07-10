#include "snake.hpp"
#include <winuser.h>

snake::snake(int x, int y, dir dir1)
{
    snakedata = new linklist(x, y);
    int i, j;
    switch (dir1)
    {
    case UP:
        i = 0;
        j = -1;
        break;
    case DOWN:
        i = 0;
        j = 1;
        break;
    case LEFT:
        i = -1;
        j = 0;
        break;
    case RIGHT:
        i = 1;
        j = 0;
        break;
    }
    snakedata->addnode(x - i, y - j);
    snakedata->addnode(x - 2 * i, y - 2 * j);
}

snake::~snake()
{
    delete snakedata;
}

// 蛇朝当前方向运动一格
void snake::move()
{
    for (int i = snakedata->getlength(); i > 1; i--)
    {
        snakedata->setcoordinates(i, snakedata->getx(i - 1), snakedata->gety(i - 1));
    }
    int i, j;
    switch (direction)
    {
    case UP:
        i = 0;
        j = 1;
        break;
    case DOWN:
        i = 0;
        j = -1;
        break;
    case LEFT:
        i = -1;
        j = 0;
        break;
    case RIGHT:
        i = 1;
        j = 0;
        break;
    }
    snakedata->setcoordinates(1, snakedata->getx(1) + i, snakedata->gety(1) + j);
}

// 蛇增长一格
void snake::grow()
{
    snakedata->addnode(2 * snakedata->getx(snakedata->getlength()) - snakedata->getx(snakedata->getlength() - 1),
                       2 * snakedata->gety(snakedata->getlength()) - snakedata->gety(snakedata->getlength() - 1));
}

// 蛇改变方向
void snake::changedirection(bool player)
{
    ExMessage m;
    peekmessage(&m, EX_KEY);
    if (m.message == WM_KEYDOWN)
    {
        if (((m.vkcode == 0x57 && ~player) || (m.vkcode == VK_UP && player)) && direction != DOWN)
        {
            direction = UP;
        }
        if (((m.vkcode == 0x53 && ~player) || (m.vkcode == VK_DOWN && player)) && direction != UP)
        {
            direction = DOWN;
        }
        if (((m.vkcode == 0x41 && ~player) || (m.vkcode == VK_LEFT && player)) && direction != RIGHT)
        {
            direction = LEFT;
        }
        if (((m.vkcode == 0x44 && ~player) || (m.vkcode == VK_RIGHT && player)) && direction != LEFT)
        {
            direction = RIGHT;
        }
    }
}

// 获取蛇的方向
dir snake::getdirection()
{
    return direction;
}

// 获取蛇的长度
int snake::getlength()
{
    return snakedata->getlength();
}

// 获取某节的x坐标
int snake::getx(int index)
{
    return snakedata->getx(index);
}

// 获取某节的y坐标
int snake::gety(int index)
{
    return snakedata->gety(index);
}