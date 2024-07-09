#include "snake.hpp"

snake::snake(int x, int y, dir dir1)
{
    snakedata = new linklist(x, y);
    int i, j;
    switch (dir1)
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
    node *q = snakedata->gettail();
    node *p;
    for (int i = 0; i < snakedata->getlength() - 2; i++)
    {
        p = q;
        q = snakedata->getprevious(p);
        snakedata->setcoordinates(p, snakedata->getx(q), snakedata->gety(q));
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
    snakedata->setcoordinates(q, snakedata->getx(q) + i, snakedata->gety(q) + j);
}

// 蛇增长一格
void snake::grow()
{
    snakedata->addnode(
        2 * snakedata->getx(snakedata->gettail()) - snakedata->getx(snakedata->getprevious(snakedata->gettail())),
        2 * snakedata->gety(snakedata->gettail()) - snakedata->gety(snakedata->getprevious(snakedata->gettail())));
}

// 蛇改变方向
void snake::changedirection()
{

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
int snake::getx(node *p)
{
    return snakedata->getx(p);
}

// 获取某节的y坐标
int snake::gety(node *p)
{
    return snakedata->gety(p);
}

// 获取蛇的头节点
node *snake::gethead()
{
    return snakedata->gethead();
}

// 获取蛇的下一节
node *snake::getnext(node *p)
{
    return snakedata->getnext(p);
}