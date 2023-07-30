#include "identity.h"
#pragma once;
#include <iostream>
using namespace std;
#include <string>
#include "macroom.h"
#include <fstream>
#include <vector>
#include "orderfile.h"

class Student : public Identity{
public:
    //默认构造
    Student();

    //有参构造，学号、姓名和密码
    Student(int id,string name,string pwd);

    //操作菜单
    virtual void openmenu();

    //申请预约
    void applyorder();

    //查看我的预约
    void showmyorder();

    //查看所有预约
    void showallorder();

    //取消预约
    void cancelorder();

    //获取机房信息容器
    vector<Macroom> vsturoom;

    //学生学号
    int m_stuid;

    //析构函数
    ~Student();
};