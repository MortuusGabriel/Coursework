#ifndef CL_APP_H
#define CL_APP_H
#include "Base.h"
#include <iostream>
class cl_app : public Base
{
public:
    //������������������� �����������
    cl_app(string _name, int _num);
    //����������� �� ���������
    cl_app();
    //����� ������� ���������
    void exec();
};

#endif
