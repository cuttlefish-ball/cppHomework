#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
int main()
{
    //1.ȷ������Э��汾
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //2.����socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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
    char buff[56];
    while (1) {
        cin >> buff;
        send(serverSocket, buff, strlen(buff), 0);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}