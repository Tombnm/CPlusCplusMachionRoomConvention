#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include <string>
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "macroom.h"

class Manager:public Identity{
public:
    //默认构造
    Manager();

    //有参构造，姓名和密码
    Manager(string name,string pwd);

    //打开菜单
    virtual void openmenu();

    //添加账号
    void addaccount();

    //查看账号
    void showaccount();

    //查看机房信息
    void machineroom();

    //清空预约记录
    void cleanorder();

    //初始化容器
    void initvector();

    //机房容器
    vector<Macroom> vmacroom;

    //去除重复数据
    bool checkrepeat(int id,int type);

    //学生容器
    vector<Student> vecstu;

    //老师容器
    vector<Teacher> vectea;

    //析构函数
    ~Manager();

};