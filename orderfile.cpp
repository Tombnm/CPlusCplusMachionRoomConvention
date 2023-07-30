#include "orderfile.h"

Orderfile::Orderfile(){
    
    //日期
    string data;
    //时间段
    string time;
    //学生编号
    string stuID;
    //学生姓名
    string stuName;
    //机房编号
    string roomID;
    //预约状态
    string status;

    //预约记录条数
    this->m_size = 0;

    //初始化用于记录的容器
    ifstream ifs("orderfile.txt",ios::in);
    while(ifs>>data && ifs>>time && ifs>>stuID && ifs>>stuName && ifs>>roomID && ifs>>status){
       string key;
       string value;
       map<string,string> m;

       int pos = data.find(":");
       if(pos != -1){
        key = data.substr(0,pos);
        value = data.substr(pos + 1,data.size()-pos);
        m.insert(make_pair(key,value));
       }
       
       pos = time.find(":");
       if(pos != -1){
        key = time.substr(0,pos);
        value = time.substr(pos + 1,time.size()-pos);
        m.insert(make_pair(key,value));
       }

       pos = stuID.find(":");
       if(pos != -1){
        key = stuID.substr(0,pos);
        value = stuID.substr(pos + 1,stuID.size()-pos);
        m.insert(make_pair(key,value));
       }

       pos = stuName.find(":");
       if(pos != -1){
        key = stuName.substr(0,pos);
        value = stuName.substr(pos + 1,stuName.size()-pos);
        m.insert(make_pair(key,value));
       }

       pos = roomID.find(":");
       if(pos != -1){
        key = roomID.substr(0,pos);
        value = roomID.substr(pos + 1,roomID.size()-pos);
        m.insert(make_pair(key,value));
       }

       pos = status.find(":");
       if(pos != -1){
        key = status.substr(0,pos);
        value = status.substr(pos + 1,status.size()-pos);
        m.insert(make_pair(key,value));
       }

        this->m_orderdata.insert(make_pair(this->m_size,m));
        this->m_size++;
    }
}

//更新预约记录
void Orderfile::updataorder(){
    
    if(this->m_size == 0){
        return;
    }

    ofstream ofs("orderfile.txt",ios::out | ios::trunc);
    for(int i = 0;i < this->m_size;i++){
        ofs<<"date:"<<this->m_orderdata[i]["date"]<<" ";
        ofs<<"time:"<<this->m_orderdata[i]["time"]<<" ";
        ofs<<"stuID:"<<this->m_orderdata[i]["stuID"]<<" ";
        ofs<<"stuName:"<<this->m_orderdata[i]["stuName"]<<" ";
        ofs<<"roomID:"<<this->m_orderdata[i]["roomID"]<<" ";
        ofs<<"status:"<<this->m_orderdata[i]["status"]<<" ";
    }
    ofs.close();

    system("pause");
    system("cls");
}

//析构函数
Orderfile::~Orderfile(){}