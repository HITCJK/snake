/*
xmake版本：2.9.3
EasyX版本：20240601
编译环境：Visual C++ 2022
*/
// 编译环境：Visual C++ 6.0~2022，EasyX_2023大暑版
// https://easyx.cn
//
#include "field.hpp"
#include <easyx.h>
#include <synchapi.h>
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    field *field = new class field();
    field->init();
    while (1)
    {
        field->refresh();
        field->draw();
        Sleep(50);
    }
    return 0;
}
