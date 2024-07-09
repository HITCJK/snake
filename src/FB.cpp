#include "field.hpp"
#include "time.h"
#include "stdlib.h"
#include <consoleapi2.h>
#include <synchapi.h>
#include "snake.hpp"

int GetRandomNumber()//生成随机数
{ 
int RandomNumber;
srand((unsigned)time(NULL));//time()用系统时间初始化种。为rand()生成不同的随机种子。 
RandomNumber =rand()%10+1;//生成1-10随机数
return RandomNumber;
}

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
  int a,length1,length2;
  int i,j;
  int m=0;
  static int g=0,k=0;
  int x,y;/*蛇头坐标*/
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
        /*蛇的长度加一*/
       }
    }
    else
    {
      p=linklist1.getnext(p);
      if(x/*蛇头坐标*/==linklist1.getx(p)&&y/*蛇头坐标*/==linklist1.gety(p))
       {
        linklist1.deletenode(p);
        /*蛇的长度加一*/
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
        g++;
       }
    }
    else
    {
      pr=linklist2.getnext(pr);
      if(x/*蛇头坐标*/==linklist2.getx(pr)&&y/*蛇头坐标*/==linklist2.gety(pr))
       {
        /*游戏结束*/
        g++;
       }
    }
  }
  /*判断蛇头是否碰到边界*/
if(x<0||x>WIDTH||y<0||y>HEIGHT)
{
  /*游戏结束*/
  g++;
}
}
