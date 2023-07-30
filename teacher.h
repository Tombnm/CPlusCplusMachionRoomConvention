#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include <string>
#include "orderfile.h"
#include <vector>

class Teacher:public Identity{
public:
    //默认构造
    Teacher();

    //有参构造，编号、姓名和密码
    Teacher(int id,string name,string pwd);

    //操作菜单
    virtual void openmenu();

    //查看所有预约
    void showallorder();

    //审核预约
    void checkorder();

    //教师编号
    int m_teaid;
};