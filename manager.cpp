#pragma once
#include "manager.h"
#include <fstream>
#include "macroom.h"

    //默认构造
    Manager::Manager(){}

    //有参构造，姓名和密码
    Manager::Manager(string name,string pwd){
        this->m_name = name;
        this->m_pwd = pwd;

        //获取机房信息
        ifstream ifs;
        ifs.open("macroomfile.txt",ios::in);

        Macroom mac;
        while(ifs>>mac.m_macroomid && ifs>>mac.m_macmaxnum){
            vmacroom.push_back(mac);
        }
        ifs.close();

    }

    //打开菜单
    void Manager::openmenu(){
        cout<<"Admin: "<<this->m_name<<" login"<<endl;
        cout<<endl;
        cout<<"\t\t--------------------------------\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         1. Add account       |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         2. Check account     |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         3. Chenck Macroom    |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         4. Clean order       |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         0. Log out           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t--------------------------------\n";
        cout<<endl;
        cout<<"Input your choice"<<endl;
    }

    //添加账号
    void Manager::addaccount(){
        cout<<"Input type of account"<<endl;
        cout<<"1. Add student"<<endl;
        cout<<"2. Add teacher"<<endl;

        //更新检测容器
        this->initvector();

        int select = 0;
        cin>>select;

        string filename;
        string tip;
        ofstream ofs;

        //重复错误提示
        string errortip;

        if(select == 1){
            filename = "stufile.txt";
            tip = "Input student id";
            errortip = "Student id repeat, try again";
        }
        else if(select == 2){
            filename = "teafile.txt";
            tip = "Input teacher id";
            errortip = "Teacher id repeat, try again";
        }

        ofs.open(filename,ios::out | ios::app);
        int id;
        string name;
        string pwd;
        cout<<tip<<endl;

        //检测是否重复
        while(true){
            cin>>id;
            bool ret = this->checkrepeat(id,select);
            //有id重复
            if(ret){
                cout<<errortip<<endl;
            }
            //无id重复
            else{
                break;
            }
        }

        cout<<"Input name"<<endl;
        cin>>name;
        cout<<"Input password"<<endl;
        cin>>pwd;

        ofs<<id<<" "<<name<<" "<<pwd<<" "<<endl;
        ofs.close();

        cout<<"Add successful"<<endl;
        system("pause");
        system("cls");
    }

    void printstudent(Student &s){
        cout<<"Student id : "<<s.m_stuid<<" name : "<<s.m_name<<" password : "<<s.m_pwd<<endl;
    }
    void printteacher(Teacher &t){
        cout<<"Teacher id : "<<t.m_teaid<<" name : "<<t.m_name<<" password : "<<t.m_pwd<<endl;
    }
    //查看账号
    void Manager::showaccount(){

        //更新检测容器
        this->initvector();

        cout<<"The information you want to show : "<<endl;
        cout<<"1. Show all students"<<endl;
        cout<<"2. Show all teachers"<<endl;

        int select = 0;
        cin>>select;

        if(select == 1){
            cout<<"The information of all students : "<<endl;
            for_each(vecstu.begin(),vecstu.end(),printstudent);
        }
        else if(select == 2){
            cout<<"The information of all teachers : "<<endl;
            for_each(vectea.begin(),vectea.end(),printteacher);
        }
        system("pause");
        system("cls");
    }

    //查看机房信息
    void Manager::machineroom(){
        cout<<"The information of machine room : "<<endl;
        for(vector<Macroom>::iterator it = vmacroom.begin();it != vmacroom.end();it++){
            cout<<"Id of machine room : "<<it->m_macroomid<<" Number of computer : "<<it->m_macmaxnum<<endl;
        }
        system("pause");
        system("cls");
    }

    //清空预约记录
    void Manager::cleanorder(){
        ofstream ofs;
        ofs.open("orderfile.txt",ios::trunc);
        ofs.close();

        cout<<"Clean order successful"<<endl;
        system("pause");
        system("cls");
    }

    //初始化容器
    void Manager::initvector(){

        this->vecstu.clear();
        this->vectea.clear();
        
        //读取学生文件的信息
        ifstream ifs;
        ifs.open("stufile.txt",ios::in);

        if(!ifs.is_open()){
            cout<<"Open Student.txt failed"<<endl;
            return;
        }

        //创建学生对象
        Student s;
        while(ifs>>s.m_stuid && ifs>>s.m_name && ifs>>s.m_pwd){
            this->vecstu.push_back(s);
        }
        ifs.close();
        //cout<<"The number of student : "<<this->vecstu.size()<<endl;

        //读取老师文件信息
        ifs.open("teafile.txt",ios::in);

        if(!ifs.is_open()){
            cout<<"Open Teacher.txt failed"<<endl;
            return;
        }

        //创建老师对象
        Teacher t;
        while(ifs>>t.m_teaid && ifs>>t.m_name && ifs>>t.m_pwd){
            vectea.push_back(t);
        }
        ifs.close();
        //cout<<"The number of teacher : "<<this->vectea.size()<<endl;
    }

    //去除重复数据
    bool Manager::checkrepeat(int id,int type){
        //检测学生
        if(type == 1){
            for(vector<Student>::iterator it = vecstu.begin();it != vecstu.end();it++){
                if(id == it->m_stuid){
                    return true;
                }
            }
        }

        //检测老师
        else if(type == 2){
            for(vector<Teacher>::iterator it = vectea.begin();it != vectea.end();it++){
                if(id == it->m_teaid){
                    return true;
                }
            }
        }
        return false;
    }