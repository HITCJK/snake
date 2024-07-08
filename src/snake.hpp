#include "linklist.hpp"

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
    void changedirection();
    int getlength();
    dir getdirection();

  private:
    dir direction;
    linklist *snakedata;
};