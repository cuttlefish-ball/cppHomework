#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
#define NUM 10
SOCKET clientSocket[NUM];
int count=0;

void trans(int id){
    char buff[56];
    char temp[80];
    while(1){
            // cout<<"*"<<endl;
        int r=recv(clientSocket[id],buff,55,0);
        if(r>0){
            buff[r]=0;
            // cout<<buff<<endl;
            memset(temp,0,80);
            sprintf(temp,"�û�%d:%s",id,buff);
            for(int i=0;i<count;i++){
                send(clientSocket[i],temp,strlen(temp),0);
                // cout<<"send to "<<i<<endl;
            }
        }
            // cout<<"temp:"<<temp<<endl;
            // cout<<"#"<<endl;
    }
}

int main()
{
    //1.ȷ������Э��汾
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    
    //2.����socket
    SOCKET serverSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //3.ȷ��������Э���ַ��
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port=htons(9527);

    //4.��
    int r=bind(serverSocket,(sockaddr*)&addr,sizeof(addr));

    //5.����
    r=listen(serverSocket,10);
    cout<<"����������"<<endl;

    //6.����
    for(int i=0;i<NUM;i++){
        clientSocket[i]=accept(serverSocket,NULL,NULL);
        //7.ͨ��
        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)trans,(LPVOID)i,NULL,NULL);
        cout<<"�û�"<<i<<"����"<<endl;
        count++;
    }



    closesocket(serverSocket);
    WSACleanup();

    return 0;
}