#ifndef CL_APP_H
#define CL_APP_H
#include "Base.h"
#include <iostream>
class cl_app : public Base
{
public:
    //параметризированный конструктор
    cl_app(string _name, int _num);
    //конструктор по умолчанию
    cl_app();
    //метод запуска программы
    void exec();
};

#endif
