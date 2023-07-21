#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
#define NUM 10
SOCKET clientSocket[NUM];

void trans(int id){
    char buff[56];
    while(1){
        int r=recv(clientSocket[id],buff,55,0);
        if(r>0){
            buff[r]=0;
            cout<<buff<<endl;
        }
    }
}

int main()
{
    //1.确定网络协议版本
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    
    //2.创建socket
    SOCKET serverSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //3.确定服务器协议地址簇
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port=htons(9527);

    //4.绑定
    int r=bind(serverSocket,(sockaddr*)&addr,sizeof(addr));

    //5.监听
    r=listen(serverSocket,10);

    cout<<"服务器启动"<<endl;

    //6.接受
    for(int i=0;i<NUM;i++){
        clientSocket[i]=accept(serverSocket,NULL,NULL);
        //7.通信
        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)trans,(LPVOID)i,NULL,NULL);
    }



    closesocket(serverSocket);
    WSACleanup();

    return 0;
}