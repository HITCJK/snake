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

// ���ýڵ������
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

// ������ĩβ��ӽڵ�
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

// ɾ���ڵ�
void linklist::deletenode(int index)
{
    node *p = head;
    node *q;
    if(index==1)
    {
        head=p->next;
    }
    else 
    {
    for (int i = 1; i < index; i++)
    {
        q = p;
        p = p->next;
    }
    q->next = p->next;
    }
    delete p;
    length--;
}

// ��ȡ�ڵ��x����
int linklist::getx(int index)
{
    node *p = head;
    for (int i = 1; i < index; i++)
    {
        p = p->next;
    }
    return p->x;
}

// ��ȡ�ڵ��y����
int linklist::gety(int index)
{
    node *p = head;
    for (int i = 1; i < index; i++)
    {
        p = p->next;
    }
    return p->y;
}

// ��ȡ������
int linklist::getlength()
{
    return length;
}