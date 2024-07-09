#include "linklist.hpp"
#include <easyx.h>

enum dir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class snake
{
  public:
    snake(int x, int y,dir dir1);
    ~snake();
    void move();
    void grow();
    void changedirection(bool player = 0);
    dir getdirection();
    int getlength();
    int getx(node *p);
    int gety(node *p);
    node *gethead();
    node *getnext(node *p);
  private:
    dir direction;
    linklist *snakedata;
};