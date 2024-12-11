#include "field.hpp"
#include <consoleapi2.h>
#include <easyx.h>
#include <minwindef.h>
#include <processenv.h>
#include <time.h>
#include <winbase.h>
#include <windows.h>
#include <stdio.h>

void gotoxy(short i, short j) /*移动光标*/
{
    COORD position = {i, j};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int GetRandomNumber() // 生成随机数
{
    int RandomNumber;
    RandomNumber = rand() % 100 + 1; // 生成1-100随机数
    return RandomNumber;
}

int GetRandomNumber1() // 生成随机数
{
    int RandomNumber;
    RandomNumber = rand() % 40; // 生成0-39随机数
    return RandomNumber;
}

int GetRandomNumber2() // 生成随机数
{
    int RandomNumber;
    RandomNumber = rand() % 30; // 生成0-29随机数
    return RandomNumber;
}
/*判断是否与蛇身体重合*/
int judge(snake *snake, int a, int b)
{
    int length, i, k = 0;
    length = snake->getlength();
    for (i = 1; i <= length; i++)
    {
        if (a == snake->getx(i) && b == snake->gety(i))
        {
            k = 1;
        }
    }
    return k;
}
/*判断是否与食物重合*/
int judgefood(linklist *food, int a, int b)
{
    int length, i, k = 0;
    length = food->getlength();
    for (i = 1; i <= length; i++)
    {
        if (a == food->getx(i) && b == food->gety(i))
        {
            k = 1;
        }
    }
    return k;
}

/*判断是否与障碍重合*/
int judgewall(linklist *wall, int a, int b)
{
    int length, i, k = 0;
    length = wall->getlength();
    for (i = 1; i <= length; i++)
    {
        if (a == wall->getx(i) && b == wall->gety(i))
        {
            k = 1;
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
    srand((unsigned)time(NULL)); // time()用系统时间初始化种。为rand()生成不同的随机种子。
}

field::~field()
{
    EndBatchDraw();
    closegraph();
}

void field::draw()
{
    if (isfailure == FALSE)
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
        TCHAR s[4], k[4];
        int length = snake->getlength();
        static int n = 0;
        static int seconds = 0;/*注意静态变量*/
        if (n < 10)
        {
            n++;
            _stprintf(s, _T("%d"), length);
            _stprintf(k, _T("%d"), seconds);
            setbkmode(TRANSPARENT);           // 文字字体透明
            settextcolor(RGB(255, 40, 26));   // 设定文字颜色
            settextstyle(20, 0, _T("宋体"));  //  设定文字大小、样式
            outtextxy(700, 0, _T("长度: "));  //  输出文字内容
            outtextxy(760, 0, s);             //  输出文字内容
            outtextxy(700, 20, _T("时间: ")); //  输出文字内容
            outtextxy(760, 20, k);            //  输出文字内容
            outtextxy(780, 20, _T("秒 "));
            FlushBatchDraw();
        }
        else
        {
            n = 0;
            seconds++;
            _stprintf(s, _T("%d"), length);
            _stprintf(k, _T("%d"), seconds);
            setbkmode(TRANSPARENT);           // 文字字体透明
            settextcolor(RGB(255, 40, 26));   // 设定文字颜色
            settextstyle(20, 0, _T("宋体"));  //  设定文字大小、样式
            outtextxy(700, 0, _T("长度: "));  //  输出文字内容
            outtextxy(760, 0, s);             //  输出文字内容
            outtextxy(700, 20, _T("时间: ")); //  输出文字内容
            outtextxy(760, 20, k);            //  输出文字内容
            outtextxy(780, 20, _T("秒 "));
            FlushBatchDraw();
        }
    }
}

void field::init()
{
    isfailure = FALSE;
    snake = new class snake(15, 20, RIGHT);
    food = new class linklist(0, 0);
    wall = new class linklist(0, 0);
    int i, j;
    int m = 0, n;
    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            n = GetRandomNumber();
            m = judge(snake, i, j);
            if (m == 0)
            {
                if (n <= 1) // 控制比例，建立链表确定食物坐标
                {
                    food->addnode(i, j);
                }
                else if (n > 99) // 控制比例（难度可选？)，建立链表确定障碍坐标
                {
                    wall->addnode(i, j);
                }
            }
        }
    }
    num = 0;
}

void field::dataprocessing() // 吃到食物，碰到障碍，自身，边界游戏结束
{
    int x, y, i, j, a;
    x = snake->getx(1);
    y = snake->gety(1);
    snake->changedirection();
    dir direction = snake->getdirection();
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
    int lengthfood = food->getlength();
    for (a = 1; a <= lengthfood; a++)
    {
        if ((x + i) == food->getx(a) && (y + j) == food->gety(a))
        {
            food->deletenode(a);
            lengthfood = food->getlength();
            snake->grow();
            a--;
        }
    }
    if (map[x + i][y + j] > 0 || map[x + i][y + j] == -2 || (x + i) < 0 || (x + i) >= WIDTH || (y + j) < 0 || (y + j) >= HEIGHT)
    {
        /*游戏失败*/
        isfailure = TRUE;
        setbkmode(TRANSPARENT);              // 文字字体透明
        settextcolor(RGB(255, 0, 0));        // 设定文字颜色
        settextstyle(80, 0, _T("宋体"));     //  设定文字大小、样式
        outtextxy(240, 220, _T("游戏失败")); //  输出文字内容
    }
    FlushBatchDraw(); /*绘制*/
    snake->move();
}

void field::maprefresh() /*刷新地图*/
{
    if (isfailure == FALSE)
    {
        num++;
        int p = 0;
        int length = snake->getlength();
        int lengthfood = food->getlength();
        int lengthwall = wall->getlength();
        if (lengthfood == 1) /*食物全被吃完时自动刷新*/
        {
            while (lengthfood != 0)
            {
                food->deletenode(1);
                lengthfood = food->getlength();
            }
            food = new class linklist(0, 0);
            for (int i = 0; i < WIDTH; i++)
            {
                for (int j = 0; j < HEIGHT; j++)
                {
                    int n = GetRandomNumber();
                    int m = judge(snake, i, j);
                    int p = judgewall(wall, i, j);
                    if (m == 0 && p == 0)
                    {
                        if (n <= 1) // 控制比例，建立链表确定食物坐标
                        {
                            food->addnode(i, j);
                        }
                    }
                }
            }
            int g = 0; /*生成一个障碍*/
            while (g != 1)
            {
                int n = GetRandomNumber1();
                int m = GetRandomNumber2();
                if (judge(snake, n, m) == 0 && judgefood(food, n, m) == 0 && judgewall(wall, n, m) == 0)
                {
                    wall->addnode(n, m);
                    g = 1;
                }
            }
            num = 0;
            num = 0;
        }
        else
        {
            if (num == 300) /*如果食物还未吃完，一定时间后清除剩余的食物，重新生成食物，同时增加一个障碍*/
            {
                while (lengthfood != 0)
                {
                    food->deletenode(1);
                    lengthfood = food->getlength();
                }
                food = new class linklist(0, 0);
                for (int i = 0; i < WIDTH; i++)
                {
                    for (int j = 0; j < HEIGHT; j++)
                    {
                        int n = GetRandomNumber();
                        int m = judge(snake, i, j);
                        int p = judgewall(wall, i, j);
                        if (m == 0 && p == 0)
                        {
                            if (n <= 1) // 控制比例，建立链表确定食物坐标
                            {
                                food->addnode(i, j);
                            }
                        }
                    }
                } // 重新生成食物
                int g = 0; /*生成一个障碍*/
                while (g != 1)
                {
                    int n = GetRandomNumber1();
                    int m = GetRandomNumber2();
                    if (judge(snake, n, m) == 0 && judgefood(food, n, m) == 0 && judgewall(wall, n, m) == 0)
                    {
                        wall->addnode(n, m);
                        g = 1;
                    }
                }
                num = 0;
            }
        }
        gotoxy(1, 1);
        printf(" 长度：%d", length);
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
}