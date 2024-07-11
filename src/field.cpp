#include "field.hpp"
#include <easyx.h>
#include <minwindef.h>
#include <time.h>

int GetRandomNumber() // ���������
{
    int RandomNumber;
    RandomNumber = rand() % 100 + 1; // ����1-10�����
    return RandomNumber;
}

/*�ж��Ƿ����������غ�*/
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
    srand((unsigned)time(NULL)); // time()��ϵͳʱ���ʼ���֡�Ϊrand()���ɲ�ͬ��������ӡ�
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
                    // ���
                    setfillcolor(LIGHTGRAY);
                    fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
                }
                if (map[i][j] > 0)
                {
                    // ����
                    setfillcolor(BLUE);
                    fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
                }
                else if (map[i][j] == -1)
                {
                    // ��ʳ��
                    setfillcolor(RED);
                    fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
                }
                else if (map[i][j] == -2)
                {
                    // ���ϰ���
                    setfillcolor(BLACK);
                    fillrectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE);
                }
            }
        }
        FlushBatchDraw();
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
                if (n <= 1) // ���Ʊ�������������ȷ��ʳ������
                {
                    food->addnode(i, j);
                }
                else if (n > 99) // ���Ʊ������Ѷȿ�ѡ��)����������ȷ���ϰ�����
                {
                    wall->addnode(i, j);
                }
            }
        }
    }
}

void field::dataprocessing() // �Ե�ʳ������ϰ��������߽���Ϸ����
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
    if (map[x + i][y + j] > 0 || map[x + i][y + j] == -2)
    {
        /*��Ϸʧ��*/
        isfailure = TRUE;
        setbkmode(TRANSPARENT);              // ��������͸��
        settextcolor(RGB(255, 0, 0));        // �趨������ɫ
        settextstyle(80, 0, _T("����"));     //  �趨���ִ�С����ʽ
        outtextxy(240, 220, _T("��Ϸʧ��")); //  �����������
    }
    FlushBatchDraw(); /*����*/
    snake->move();
}

void field::maprefresh() /*ˢ�µ�ͼ*/
{
    if (isfailure == FALSE)
    {
        int length = snake->getlength();
        int lengthfood = food->getlength();
        int lengthwall = wall->getlength();
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