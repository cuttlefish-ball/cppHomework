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
    cout<<"�������û�����"<<endl;
    cin>>username;
    cout<<"���������룺"<<endl;
    cin>>password;
    string temp=(username+' '+password);
    send(loginSocket,temp.c_str(),strlen(temp.c_str()),0);
    char ans[5];
    int r=recv(loginSocket,ans,5,0);
    if(r>0)
    {        
        if(ans[0]=='1')
        {
            cout<<"��¼�ɹ�"<<endl;
            return true;
        }
        else
        {
            cout<<"��¼ʧ��"<<endl;
            return false;
        }
        }
    return false;
}

void createsocket(SOCKET &sock,int port){
    //1.ȷ������Э��汾
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //2.����socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //3.ȷ��������Э���ַ��
    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    //4.���ӷ�����
    int r = connect(sock, (sockaddr*)&addr, sizeof(addr));
    if (r == -1) {
        cout << "���ӷ�����ʧ��" << endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
    }
}

int main()
{
    createsocket(loginSocket,9528);
    cout << "���ӷ������ɹ�" << endl;
    while(!login());
    closesocket(loginSocket);
    //5.ͨ��
    createsocket(serverSocket,9527);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)mysend,NULL,NULL,NULL);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)myreceive,NULL,NULL,NULL);
    while(1){}

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}