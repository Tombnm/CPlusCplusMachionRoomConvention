#pragma once
#include <iostream>
using namespace std;
#include <string>

//学生、老师和管理员身份抽象基类
class Identity{
public:
    //操作菜单
    virtual void openmenu() = 0;

    //用户名
    string m_name;
    //密码
    string m_pwd;
};