#include <graphics.h>
#include "snake.hpp"
#define BLOCK_SIZE 20 // 每个小格子的长宽大小 
#define HEIGHT 30 // 高度上一共30个小格子
#define WIDTH 40 //  宽度上一共40个小格子 

/*
此类负责整个游戏区域的处理，功能有：
1.初始化区域
2.刷新区域
3.逻辑处理
4.绘制区域
5.关闭区域
*/
class field
{
    public:
        field();
        ~field();
        void init();
        void check();
        void refresh();
        void draw();
    private:
        snake *snake;
        linklist *food;
        linklist *wall;
        int map[WIDTH][HEIGHT];
};