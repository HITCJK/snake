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
void linklist::setcoordinates(node *p, int x, int y)
{
    p->x = x;
    p->y = y;
}

// 在链表末尾添加节点
void linklist::addnode(int x, int y)
{
    node *p = head;
    while (p->next != nullptr)
        ;
    p->next = new node();
    p = p->next;
    p->x = x;
    p->y = y;
    p->next = nullptr;
    length++;
}

// 删除节点
void linklist::deletenode(node *p)
{
    node *q = head;
    while (q->next != p)
        q = q->next;
    q->next = p->next;
    delete p;
    length--;
}

// 获取节点的x坐标
int linklist::getx(node *p)
{
    return p->x;
}

// 获取节点的y坐标
int linklist::gety(node *p)
{
    return p->y;
}

// 获取链表长度
int linklist::getlength()
{
    return length;
}

// 获取链表头节点指针
node *linklist::gethead()
{
    return head;
}

// 获取链表尾节点指针
node *linklist::gettail()
{
    node *p = head;
    while (p->next != nullptr)
        p = p->next;
    return p;
}

// 获取下一个节点指针
node *linklist::getnext(node *p)
{
    return p->next;
}

// 获取上一个节点指针
node *linklist::getprevious(node *p)
{
    node *q = head;
    while (q->next != p)
        q = q->next;
    return q;
}