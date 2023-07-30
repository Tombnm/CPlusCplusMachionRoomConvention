#include "student.h"

    //默认构造
    Student::Student(){}

    //有参构造，学号、姓名和密码
    Student::Student(int id,string name,string pwd){
        this->m_stuid = id;
        this->m_name = name;
        this->m_pwd = pwd;
    }

    //操作菜单
    void Student::openmenu(){
        cout<<"Student: "<<this->m_name<<" login"<<endl;
        cout<<endl;
        cout<<"\t\t--------------------------------\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         1. Apply order       |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         2. Check my order    |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         3. Chenck all order  |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         4. Cancel order      |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         0. Log out           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t--------------------------------\n";
        cout<<endl;
        cout<<"Input your choice"<<endl;
    }

    //申请预约
    void Student::applyorder(){
        cout<<"Time of machineroom : Monday to friday"<<endl;
        cout<<"Input time you want to apply"<<endl;
        cout<<"1. Monday"<<endl;
        cout<<"2. Tuesday"<<endl;
        cout<<"3. Wednesday"<<endl;
        cout<<"4. Thursday"<<endl;
        cout<<"5. Friday"<<endl;
        
        int data = 0;
        int time = 0;
        int room = 0;

        while(true){
            cin>>data;
            if(data >= 1 && data <= 5){
                break;
            }
            else{
                cout<<"Input error, try again"<<endl;
            }
        }

        cout<<"Time of machineroom : Mornning or afternoon"<<endl;
        cout<<"1. Mornning"<<endl;
        cout<<"2. Afternoon"<<endl;

        while(true){
            cin>>time;
            if(time == 1 || time == 2){
                break;
            }
            else{
                cout<<"Input error, try again"<<endl;
            }
        }

        //获取机房信息
        ifstream ifs;
        ifs.open("macroomfile.txt",ios::in);

        Macroom mac;
        while(ifs>>mac.m_macroomid && ifs>>mac.m_macmaxnum){
            vsturoom.push_back(mac);
        }
        ifs.close();

        cout<<"Machineroom you want to chose : "<<endl;
        cout<<"Room 1: Number of computer "<<vsturoom[0].m_macmaxnum<<endl;
        cout<<"Room 2: Number of computer "<<vsturoom[1].m_macmaxnum<<endl;
        cout<<"Room 3: Number of computer "<<vsturoom[2].m_macmaxnum<<endl;

        while(true){
            cin>>room;
            if(room ==1 || room ==2 || room ==3){
                break;
            }
            else{
                cout<<"Input error, try again"<<endl;
            }
        }

        cout<<"Apply successful, waiting for check it"<<endl;

        ofstream ofs("orderfile.txt",ios::app);
        ofs<<"data:"<<data<<" ";
        ofs<<"time:"<<time<<" ";
        ofs<<"stuID:"<<this->m_stuid<<" ";
        ofs<<"stuName:"<<this->m_name<<" ";
        ofs<<"room:"<<room<<" ";
        ofs<<"status:"<<1<<endl;
        ofs.close();

        system("pause");
        system("cls");
    }

    //查看我的预约
    void Student::showmyorder(){
        Orderfile of;
        
        if(of.m_size == 0){
            cout<<"No application"<<endl;
            system("pause");
            system("cls");
            return;
        }

        for(int i = 0;i < of.m_size;i++){
            if(atoi(of.m_orderdata[i]["stuID"].c_str()) == this->m_stuid){
                cout<<"Date : "<<of.m_orderdata[i]["date"]<<" | ";
                cout<<"Time : "<<of.m_orderdata[i]["time"]<<" | ";
                cout<<"Machine room : "<<of.m_orderdata[i]["roomID"]<<" | ";
                //审核状态，0 取消预约， 1 审核中， 2 已预约， -1 预约失败
                string status = "status : ";
                if(of.m_orderdata[i]["status"] == "1"){
                    status += "Application checking";
                }
                else if(of.m_orderdata[i]["status"] == "2"){
                    status += "Application successful";
                }
                else{
                    status += "Application failed";
                }
                cout<<status<<endl;
            }
        }
        system("pause");
        system("cls");
    }

    //查看所有预约
    void Student::showallorder(){
        Orderfile of;
        if(of.m_size == 0){
            cout<<"No application"<<endl;
            system("pause");
            system("cls");
            return;
        }

        for(int i = 0;i< of.m_size;i++){
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

    //取消预约
    void Student::cancelorder(){
        Orderfile of;
        if(of.m_size == 0){
            cout<<"No application"<<endl;
            system("pause");
            system("cls");
            return;
        }

        cout<<"Application successful or checking can cancel, input number of application"<<endl;

        vector<int> v;
        int index = 1;
        for(int i = 0;i < of.m_size;i++){
            if(atoi(of.m_orderdata[i]["stuID"].c_str()) == this->m_stuid){
                if(of.m_orderdata[i]["status"] == "1" || of.m_orderdata[i]["status"] == "2"){
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
                    else if(of.m_orderdata[i]["status"] == "2"){
                        status += "Application successful";
                    }
                    cout<<status<<endl;
                    index++;
                }
            }
        }
        cout<<"Input number of application to cancel, 0 represent return"<<endl;
        int select = 0;
        while(true){
            cin>>select;
            if(select >= 0 && select <= v.size()){
                if(select == 0){
                    system("cls");
                    return;
                }
                else{
                    of.m_orderdata[v[select-1]]["status"] = "0";
                    of.updataorder();
                    cout<<"Application cancel"<<endl;
                    break;
                }
            }
            cout<<"Input error, try again"<<endl;
        }
        system("pause");
        system("cls");
    }

    //析构函数
    Student::~Student(){}