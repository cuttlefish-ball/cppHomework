#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
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

    //6.接受
    SOCKET clientSocket=accept(serverSocket,NULL,NULL);

    //7.通信
    char buff[56];
    while(1){
        r=recv(clientSocket,buff,55,0);
        if(r>0){
            buff[r]=0;
            cout<<buff<<endl;
        }
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}