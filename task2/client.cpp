#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
SOCKET serverSocket;

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
    // cout<<"*"<<endl;
    int r=recv(serverSocket,temp,59,0);
    // cout<<"r="<<r<<endl;
    if(r>0)
    {
        temp[r]=0;
        cout<<temp<<endl;
    }
    // cout<<"#"<<endl;
    }
}


int main()
{
    //1.ȷ������Э��汾
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //2.����socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //3.ȷ��������Э���ַ��
    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9527);

    //4.���ӷ�����
    int r = connect(serverSocket, (sockaddr*)&addr, sizeof(addr));
    if (r == -1) {
        cout << "���ӷ�����ʧ��" << endl;
        closesocket(serverSocket);
        WSACleanup();
        system("pause");
        return -1;
    }
    cout << "���ӷ������ɹ�" << endl;

    //5.ͨ��
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)mysend,NULL,NULL,NULL);
    myreceive();

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}