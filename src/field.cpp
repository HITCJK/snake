#include "field.hpp"
#include <easyx.h>
#include <time.h>

int GetRandomNumber()//生成随机数
{ 
int RandomNumber;
RandomNumber =rand()%100+1;//生成1-10随机数
return RandomNumber;
}

/*判断是否与蛇身体重合*/
int judge(snake *snake,int a,int b)
{
  int length,i,k=0;
  length=snake->getlength();
  for(i=1;i<=length;i++)
  {
    if(a==snake->getx(i)&&b==snake->gety(i))
    {
        k=1;
    }
  }
  return k;
}


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
    srand((unsigned)time(NULL));//time()用系统时间初始化种。为rand()生成不同的随机种子。 
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
    food = new class linklist(0,0);
    wall = new class linklist(0,0);
    int i,j;
    int m=0,n;
    for(i=0;i<WIDTH;i++)
    {
       for(j=0;j<HEIGHT;j++)
       {
        n=GetRandomNumber();
        m=judge(snake,i,j);
        if(m==0)
        {
          if(n<=1)//控制比例，建立链表确定食物坐标
          {
            food->addnode(i,j);
          }
          else if(n>99)//控制比例（难度可选？)，建立链表确定障碍坐标
          {
            wall->addnode(i,j);
          }
        }
       }
    }
}

 void field::check()
{
  int x,y,i,j,a;
  x=snake->getx(1);
  y=snake->gety(1);
  dir direction=snake->getdirection();
  switch (direction)
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
  int lengthfood =food->getlength();
  for(a=1;a<=lengthfood;a++)
  {
    if((x+i)==food->getx(a)&&(y+j)==food->gety(a))
    {
        food->deletenode(a);
        snake->grow();
    }
  }
}

void field::refresh()
{
    snake->changedirection();
    snake->move();
    int length = snake->getlength();
    int lengthfood =food->getlength();
    int lengthwall =wall->getlength();
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
    for (int i = 1; i <= lengthfood; i++)
    {
        map[food->getx(i)][food->gety(i)] = -1;
    }
    for (int i = 1; i <= lengthwall; i++)
    {
        map[wall->getx(i)][wall->gety(i)] = -2;
    }
}