#include "teacher.h"

    //默认构造
    Teacher::Teacher(){}

    //有参构造，编号、姓名和密码
    Teacher::Teacher(int id,string name,string pwd){

        //初始化属性
        this->m_teaid = id;
        this->m_name = name;
        this->m_pwd = pwd;
    }

    //操作菜单
    void Teacher::openmenu(){
        cout<<"Teacher: "<<this->m_name<<" login"<<endl;
        cout<<endl;
        cout<<"\t\t--------------------------------\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         1. Show all order    |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         2. Check all order   |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         0. Log out           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t--------------------------------\n";
        cout<<endl;
        cout<<"Input your choice"<<endl;
    }

    //查看所有预约
    void Teacher::showallorder(){
        Orderfile of;
        if(of.m_size == 0){
            cout<<"No application"<<endl;
            system("pause");
            system("cls");
            return;
        }
        for(int i = 0;i < of.m_size;i++){
            cout<<i+1<<". ";

            cout<<"Date : "<<of.m_orderdata[i]["date"];
            cout<<" Time : "<<of.m_orderdata[i]["time"];
            cout<<" StuID : "<<of.m_orderdata[i]["stuID"];
            cout<<" StuName : "<<of.m_orderdata[i]["stuName"];
            cout<<" Machine room : "<<of.m_orderdata[i]["roomID"];
            
            //0 取消预约， 1 审核中，2 已预约， -1 预约失败
            string status = " Status : ";
            if(of.m_orderdata[i]["status"] == "1"){
                status += "Application checking";
            }
            else if(of.m_orderdata[i]["status"] == "2"){
                status += "Application successful";
            }
            else if(of.m_orderdata[i]["status"] == "-1"){
                status += "Application failed";
            }
            else{
                status += "Application cancel";
            }
            cout<<status<<endl;
        }

        system("pause");
        system("cls");
    }

    //审核预约
    void Teacher::checkorder(){
        Orderfile of;
        if(of.m_size == 0){
            cout<<"No application"<<endl;
            system("pause");
            system("cls");
            return;
        }

        cout<<"Application need to check"<<endl;

        vector<int> v;
        int index = 1;
        for(int i = 0; i < of.m_size;i++){
            if(of.m_orderdata[i]["status"] == "1"){
                v.push_back(i);
                cout<<index<<". ";
                cout<<"Date: "<<of.m_orderdata[i]["date"];
                cout<<" Time: "<<(of.m_orderdata[i]["time"] == "1" ? "Morning" : "Afternoon");
                cout<<" Machineroom: "<<of.m_orderdata[i]["roomID"];
                //0 取消预约， 1 审核中， 2 预约成功， -1 预约失败
                string status = " Status: ";
                if(of.m_orderdata[i]["status"] == "1"){
                    status += "Application checking";
                }
                cout<<status<<endl;
                index++;
            }
        }
        
        cout<<"Input number of application need to check"<<endl;
        int select = 0;
        int ret = 0;
        while(true){
            cin>>select;
            if(select > 0 && select <= v.size()){
                cout<<"Input result of checking"<<endl;
                cout<<"1. Pass application"<<endl;
                cout<<"2. No pass application"<<endl;
                cin>>ret;
                if(ret == 1){
                    of.m_orderdata[select-1]["status"] = "2";
                }
                else{
                    of.m_orderdata[select-1]["status"] = "-1";
                }
                of.updataorder();
                cout<<"Checking successful"<<endl;
                break;
            }
            cout<<"Input error, try again"<<endl;
        }
        system("pause");
        system("cls");
    }