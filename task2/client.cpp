#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
int main()
{
    //1.确定网络协议版本
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //2.创建socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //3.确定服务器协议地址簇
    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9527);

    //4.连接服务器
    int r = connect(serverSocket, (sockaddr*)&addr, sizeof(addr));
    if (r == -1) {
        cout << "连接服务器失败" << endl;
        closesocket(serverSocket);
        WSACleanup();
        system("pause");
        return -1;
    }
    cout << "连接服务器成功" << endl;

    //5.通信
    char buff[56];
    while (1) {
        cin >> buff;
        send(serverSocket, buff, strlen(buff), 0);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}