#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
SOCKET serverSocket,loginSocket;

void mysend(){
    char buff[56];
    while (1) {
        cin.getline(buff,55);
        send(serverSocket, buff, strlen(buff), 0);
    }
}

void myreceive(){
    char temp[60];
    while(1){
    int r=recv(serverSocket,temp,59,0);
    if(r>0)
    {
        temp[r]=0;
        cout<<temp<<endl;
    }
    }
}

bool login(){
    string username,password;
    cout<<"请输入用户名："<<endl;
    cin>>username;
    cout<<"请输入密码："<<endl;
    cin>>password;
    string temp=(username+' '+password);
    send(loginSocket,temp.c_str(),strlen(temp.c_str()),0);
    char ans[5];
    int r=recv(loginSocket,ans,5,0);
    if(r>0)
    {        
        if(ans[0]=='1')
        {
            cout<<"登录成功"<<endl;
            return true;
        }
        else
        {
            cout<<"登录失败"<<endl;
            return false;
        }
        }
    return false;
}

void createsocket(SOCKET &sock,int port){
    //1.确定网络协议版本
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //2.创建socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //3.确定服务器协议地址簇
    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    //4.连接服务器
    int r = connect(sock, (sockaddr*)&addr, sizeof(addr));
    if (r == -1) {
        cout << "连接服务器失败" << endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
    }
}

int main()
{
    createsocket(loginSocket,9528);
    cout << "连接服务器成功" << endl;
    while(!login());
    closesocket(loginSocket);
    //5.通信
    createsocket(serverSocket,9527);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)mysend,NULL,NULL,NULL);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)myreceive,NULL,NULL,NULL);
    while(1){}

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}