#include <iostream>
using namespace std;
#include "identity.h"
#include <fstream>
#include <string>
#include "globefile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

//全局函数，进入管理员子菜单界面
void managermenu(Identity * &manager){
    while(true){

        //调用管理员子菜单
        manager->openmenu();

        int select = 0;
        //接收用户选择
        cin>>select;
        
        //将父类指针转为子类指针，调用其它接口
        Manager * idemanager = (Manager*)manager;

        //添加账号
        if(select == 1){
            cout<<"Add account"<<endl;
            idemanager->addaccount();
        }

        //查看账号
        else if(select == 2){
            cout<<"Check account"<<endl;
            idemanager->showaccount();
        }

        //查看机房信息
        else if(select == 3){
            cout<<"Check information of machine room"<<endl;
            idemanager->machineroom();
        }

        //清空预约记录
        else if(select == 4){
            cout<<"Clean order"<<endl;
            idemanager->cleanorder();
        }

        //注销登录
        else if(select == 0){
            //销毁堆区对象
            delete manager;
            cout<<"Log out successful"<<endl;
            system("pause");
            system("cls");
            return;
        }

        else{
            cout<<"Input error, try again"<<endl;
            system("pause");
            system("cls");
        }
    }
}

//全局函数。进入学生子菜单
void studentmenu(Identity * &student){
    while(true){
        //学生菜单
        student->openmenu();

        Student* stu = (Student*) student;
        int select = 0;
        cin>>select;

        //申请预约
        if(select == 1){
            stu->applyorder();
        }
        //查看自身预约
        else if(select == 2){
            stu->showmyorder();
        }
        //查看所有预约
        else if(select == 3){
            stu->showallorder();
        }
        //取消预约
        else if(select == 4){
            stu->cancelorder();
        }
        //退出系统
        else if(select == 0){
            delete student;
            cout<<"Log out successful"<<endl;
            system("pause");
            system("cls");
            return;
        }
        else{
            cout<<"Input error, try again"<<endl;
            system("pause");
            system("cls");
        }
    }
}

//全局函数，进入教师子菜单
void teachermenu(Identity * &teacher){

    while(true){
        //教师菜单
        teacher->openmenu();

        Teacher* tea = (Teacher*) teacher;
        int select = 0;
        cin>>select;
        if(select == 1){
            //查看所有预约
            tea->showallorder();
        }
        else if(select == 2){
            //审核预约
            tea->checkorder();
        }
        else if(select == 0){
            //注销登录
            delete teacher;
            cout<<"Log out"<<endl;
            system("pause");
            system("cls");
            return;
        }
        else{
            cout<<"Input error, try again"<<endl;
            system("pause");
            system("cls");
        }
    } 
}


//使用全局函数实现登录功能，参数1 操作的文件名称，2 操作的身份类型
void login(string filename,int type){
    
    //父类指针，用于指向子类对象
    Identity * person = NULL;

    //读文件
    ifstream ifs;
    ifs.open(filename,ios::in);
    //判断是否打开成功
    if(!ifs.is_open()){
        cout<<"File is not exist"<<endl;
        ifs.close();
        return;
    }

    //准备接收用户信息
    int id = 0 ;
    string name;
    string pwd;

    //判断身份
    //学生身份
    if(type == 1){
        cout<<"Input id of student"<<endl;
        cin>>id;
    }
    //老师身份
    else if(type == 2){
        cout<<"Input id of teacher"<<endl;
        cin>>id;
    }
    
    cout<<"Input your name"<<endl;
    cin>>name;
    cout<<"Input your password"<<endl;
    cin>>pwd;

    //学生身份验证
    if(type == 1){
        int fid;
        string fname;
        string fpwd;
        //逐行读入内容，每行内容读到空格会结束
        while(ifs>>fid && ifs>>fname && ifs>>fpwd){
            if(id == fid && name == fname && pwd == fpwd){
                cout<<"Student login successful"<<endl;
                system("pause");
                system("cls");
                //创建一个学生子类对象
                person = new Student(id,name,pwd);

                //学生模块子菜单
                studentmenu(person);
                return;

                return;
            }
        }
    }
    //教师身份验证
    else if(type == 2){
        int fid;
        string fname;
        string fpwd;
        while(ifs>>fid && ifs>>fname && ifs>>fpwd){
            if(id == fid && name == fname && pwd == fpwd){
                cout<<"Teacher login successful"<<endl;
                system("pause");
                system("cls");
                //创建一个教师子类对象
                person = new Teacher(id,name,pwd);

                //教师子菜单模块
                teachermenu(person);
                return;
            }
        }
    }
    //管理员身份验证
    else if(type == 3){
        string fname;
        string fpwd;
        while(ifs>>fname && ifs>>fpwd){
            if(name == fname && pwd == fpwd){
                cout<<"Admin login successful"<<endl;
                system("pause");
                system("cls");
                //创建一个管理员子类对象
                person = new Manager(name,pwd);

                //管理员模块子菜单
                managermenu(person);
                return;
            }
        }
    }

    cout<<"Login failed"<<endl;
    system("pause");
    system("cls");
}




int main(){

    //用于接受用户的选择
    int select = 0;
    while(true){
        
        cout<<"====Welcome to machine room reservation system===="<<endl;
        cout<<endl;
        cout<<"Input your ID"<<endl;
        cout<<"\t\t--------------------------------\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         1. Stusent           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         2. Teacher           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         3. Manager           |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t|         0. Quit              |\n";
        cout<<"\t\t|                              |\n";
        cout<<"\t\t--------------------------------\n";
        cout<<endl;
        cout<<"Input your choice"<<endl;

        cin>>select;

        switch(select){

            //学生身份
            case 1:
            login("stufile.txt",1);
            break;

            //老师身份
            case 2:
            login("teafile.txt",2);
            break;

            //管理员身份
            case 3:
            login("adminfile.txt",3);
            break;

            //退出系统
            case 0:
            cout<<"Welcome to use next"<<endl;
            system("pause");
            return 0;
            break;

            default:
            cout<<"Input error, try again"<<endl;
            system("pause");
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}