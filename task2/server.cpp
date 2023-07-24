#include<winsock2.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
using namespace std;
#define NUM 100
SOCKET clientSocket[NUM],serverSocket,loginSocket,checkSocket[NUM];
int count=0;

void trans(int id){
    char buff[56];
    char temp[80];
    while(1){
        int r=recv(clientSocket[id],buff,55,0);
        if(r>0){
            buff[r]=0;
            memset(temp,0,80);
            sprintf(temp,"用户%d:%s",id,buff);
            for(int i=0;i<count;i++){
                send(clientSocket[i],temp,strlen(temp),0);
            }
        }
        else{
            cout<<"用户"<<id<<"已退出聊天"<<endl;
            break;
        }
    }
}

char checkuser(char* s){
    string str=s;
    if(str=="abc 123")
    return '1';
    else
    return '0';
}

void check(int i){
     while(1){
        char ans[5]={'1'};
        char buff[50];
        int r=recv(checkSocket[i],buff,50,0);
        ans[0]=checkuser(buff);
        if(r>0){
            send(checkSocket[i],ans,5,0);
        }
}
}

void checkThread(){
    for(int i=0;i<NUM;i++)
    {
        checkSocket[i]=accept(loginSocket,NULL,NULL);
        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)check,(LPVOID)i,NULL,NULL);
    }
}

void serveThread(){
    for(int i=0;i<NUM;i++){
        clientSocket[i]=accept(serverSocket,NULL,NULL);
        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)trans,(LPVOID)i,NULL,NULL);
        count++;
    }
}

void createsocket(SOCKET &sock, int port){
    //1.确定网络协议版本
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    
    //2.创建socket
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //3.确定服务器协议地址簇
    SOCKADDR_IN addr={0};
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port=htons(port);

    //4.绑定
    int r=bind(sock,(sockaddr*)&addr,sizeof(addr));

    //5.监听
    r=listen(sock,10);
    cout<<"服务器启动"<<endl;
}

int main()
{
    createsocket(loginSocket,9528);
    createsocket(serverSocket,9527);

    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)checkThread,NULL,NULL,NULL);
    CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)serveThread,NULL,NULL,NULL);

    while(1);

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}