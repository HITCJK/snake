#include "linklist.hpp"

linklist::linklist(int x, int y)
{
    head = new node();
    head->x = x;
    head->y = y;
    head->next = nullptr;
    length = 1;
}

linklist::~linklist()
{
    node *p = head;
    while (p != nullptr)
    {
        node *q = p;
        p = p->next;
        delete q;
    }
}

// 设置节点的坐标
void linklist::setcoordinates(int index, int x, int y)
{
    node *p = head;
    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }
    p->x = x;
    p->y = y;
}

// 在链表末尾添加节点
void linklist::addnode(int x, int y)
{
    node *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    p->next = new node();
    p = p->next;
    p->x = x;
    p->y = y;
    p->next = nullptr;
    length++;
}

// 删除节点
void linklist::deletenode(int index)
{
    node *p = head;
    node *q;
    for (int i = 1; i < index; i++)
    {
        q = p;
        p = p->next;
    }
    q->next = p->next;
    delete p;
    length--;
}

// 获取节点的x坐标
int linklist::getx(int index)
{
    node *p = head;
    for (int i = 1; i < index; i++)
    {
        p = p->next;
    }
    return p->x;
}

// 获取节点的y坐标
int linklist::gety(int index)
{
    node *p = head;
    for (int i = 1; i < index; i++)
    {
        p = p->next;
    }
    return p->y;
}

// 获取链表长度
int linklist::getlength()
{
    return length;
}