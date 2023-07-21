#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

void f31(){
    int a[10];
    for(int i=0;i<10;i++)
    a[i]=i;
}

void f32(){
    int a[10];
    for(int i=0;i<10;i++)
    a[i]=i;
    int b[10];
    for(int i=0;i<10;i++)
    b[i]=a[i];
}

void f34(){
    int a[10];
    int *b=begin(a);
    int *e=begin(a);
    b+=e-b;
    cout<<b<<endl;
}

bool f36(int*a,int*b,int size){
    for(int i=0;i<size;i++)
    if(*(a+i)!=*(b+i))
    return false;
    return true;
}

void f35(int*a,int size){
    for(int i=0;i<size;i++)
    *(a+i)=0;
}

void f40(){
    char a[5]="abcd";
    char b[5]="efgh";
    char c[10];
    strcat(a,b);
    strcpy(c,b);
}

void f41(){
    int a[3]={0,1,2};
    vector<int> b(begin(a),end(a));
}


int main(){
    int a[3]={0,1,3};
    int b[3]={0,1,3};
    f31();
    f32();
    f34();
    f35(a,3);
    bool ans=f36(a,b,3);
    cout<<ans<<endl;
    f40();
    return 0;
}