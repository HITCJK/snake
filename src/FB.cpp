#include "field.hpp"
#include "time.h"
#include "stdlib.h"
#include <stdio.h>
#include <conio.h>
#include <consoleapi2.h>
#include <synchapi.h>
#include "snake.hpp"

int isFailure=0;/*是否失败*/

int GetRandomNumber()//生成随机数
{ 
int RandomNumber;
srand((unsigned)time(NULL));//time()用系统时间初始化种。为rand()生成不同的随机种子。 
RandomNumber =rand()%10+1;//生成1-10随机数
return RandomNumber;
}

void updateWithoutInput(snake snake) // 蛇的运动
{
	if (isFailure) //  如果游戏失败，函数返回
		return;
	static int waitIndex = 1; // 静态局部变量，初始化时为1
	waitIndex++; // 每一帧+1
	if (waitIndex==10) // 如果等于10才执行，这样小蛇每隔10帧移动一次
	{
    snake.changedirection(0);
		snake.move(); //  调用小蛇移动函数
		waitIndex = 1; // 再变成1
	}
}

/*void updateWithInput(snake snake)  // 蛇的方向改变
{
	if(_kbhit() && isFailure==0)  //  如果有按键输入，并且不失败
	{
		char input =getchar(); //  获得按键输入
		if (input=='a' || input=='s' || input=='d' || input=='w') // 如果是asdw 
		{
			snake.changedirection(0)=input;  // 设定移动方向
			snake.move(); // 调用小蛇移动函数
		}
	}
}*/

/*判断是否与蛇身体重合*/
int judge(snake snake,int a,int b)
{
  struct node*body=NULL;
  int length,i,k=0;
  length=snake.getlength();
  for(i=0;i<length;i++)
  {
    if(i==0)
    {
      body=snake.gethead();
      if(a==body->x&&b==body->y)
      {
        k=1;
      }
    }
    else
    {
      body=snake.getnext(body);
      if(a==body->x&&b==body->y)
      {
        k=1;
      }
    }
  }
  return k;
}

int getx(snake snake)
{
  struct node*p=NULL;
  int i;
  p=snake.gethead();
  for(i=0;i<snake.getlength();i++)
  {
    p=snake.getnext(p);
  }
  return p->x;
}

int gety(snake snake)
{
  struct node*p=NULL;
  int i;
  p=snake.gethead();
  for(i=0;i<snake.getlength();i++)
  {
    p=snake.getnext(p);
  }
  return p->y;
}


/*功能：
 1.每隔30s生成一次食物和障碍
 2.判断蛇头是否吃到食物
 3.游戏结束判断（碰到障碍或者碰到边界）
 */
void position()
{
  linklist linklist1;//设置对象1：面向食物
  linklist linklist2;//设置对象2：面向障碍
  snake snake(15,20,RIGHT);
  field field;
  int length1,length2;
  int i,j;/*遍历*/
  int m=0;/*判断食物或者障碍是否与蛇身重合*/
  static int g=0,k=0,a=0;/*判断是否第一次进入系统+进入次数*/
  int x,y;/*蛇头坐标*/
  x=getx(snake);
  y=gety(snake);
  Sleep(50);
  if(g!=k)
  {
    k=0;
  }
  if(k==0)/*第一次进入程序时即执行一次*/
  {
    for(i=WIDTH-1;i>=0;i--)
    {
       for(j=HEIGHT-1;j>=0;j--)
       {
        m=judge(snake,i,j);
        if(m==0)
        {
          if(GetRandomNumber()<=5)//控制比例，建立链表确定食物坐标
          {
            linklist1.addnode(i,j);
            /*画出食物*/
          }
          else if(GetRandomNumber()>8)//控制比例（难度可选？)，建立链表确定障碍坐标
          {
            linklist2.addnode(i,j);
            /*画出障碍*/
          }
        }
       }
    }
    a=0;
    k++;
    g=k;
  }
  else if(k!=0&&a==60)/*刷新*/
  {
    for(i=WIDTH-1;i>=0;i--)
    {
       for(j=HEIGHT-1;j>=0;j--)
       {
        m=judge(snake,i,j);
        if(m==0)
        {
          if(GetRandomNumber()<=5)//控制比例，建立链表确定食物坐标
          {
            linklist1.addnode(i,j);
            /*画出食物*/
          }
          else if(GetRandomNumber()>8)//控制比例（难度可选？)，建立链表确定障碍坐标
          {
            linklist2.addnode(i,j);
            /*画出障碍*/
          }
        }
       }
    }
    a=0;
    k++;
    g=k;
  }
  a++;
    /*判断蛇是否吃到食物,蛇每移动一次刷新一次*/
  length1=linklist1.getlength();
  length2=linklist2.getlength();
  for(i=0;i<length1;i++)
  {
    struct node*p=NULL;
    if(i==0)
    {
       p=linklist1.gethead();
       if(x/*蛇头坐标*/==linklist1.getx(p)&&y/*蛇头坐标*/==linklist1.gety(p))
       {
        linklist1.deletenode(p);
        snake.grow();
       }
    }
    else
    {
      p=linklist1.getnext(p);
      if(x/*蛇头坐标*/==linklist1.getx(p)&&y/*蛇头坐标*/==linklist1.gety(p))
       {
        linklist1.deletenode(p);
        snake.grow();
       }
    }
  }
  /*对新建立的链表重新绘图（食物）*/

/*判断蛇是否碰到障碍，蛇每移动一次刷新一次*/
for(i=0;i<length2;i++)
  {
    struct node*pr=NULL;
    if(i==0)
    {
       pr=linklist2.gethead();
       if(x/*蛇头坐标*/==linklist2.getx(pr)&&y/*蛇头坐标*/==linklist2.gety(pr))
       {
        /*游戏结束*/
        isFailure=1;
        g++;
       }
    }
    else
    {
      pr=linklist2.getnext(pr);
      if(x/*蛇头坐标*/==linklist2.getx(pr)&&y/*蛇头坐标*/==linklist2.gety(pr))
       {
        /*游戏结束*/
        isFailure=1;
        g++;
       }
    }
  }
  /*判断蛇头是否碰到边界*/
if(x<0||x>WIDTH||y<0||y>HEIGHT)
{
  /*游戏结束*/
  isFailure=1;
  g++;
}
updateWithoutInput(snake);
}
