#include<iostream>
#include<string>
using namespace std;
void f2(){
    string s;
    char str[100];
    int i=0;
    while(getline(cin,s));
    cout<<s<<endl;
    while(str[i]=getchar()!=' ')
    i++;
}

void f4(){
    string s1,s2;
    cin>>s1>>s2;
    if(s1==s2)
    cout<<"equal"<<endl;
    else
    {
        cout<<"not equal"<<endl;    
        cout<<(s1>s2? s1:s2)<<endl;
        cout<<(s1.size()>s2.size()? s1:s2)<<endl;
    }
}

void f5(){
    string s1="",s2="",tem="";
    while(cin>>tem){
        s1+=tem;
        s2+=" ";
        s2+=tem;
    }
    cout<<s1<<s2<<endl;
}

void f6(){
    string s="akndsgweg";
    for(char &i : s)
    i='X';
    cout<<s<<endl;
}

void f10(){
    string s;
    cin>>s;
    for(char &i: s){
        if(!ispunct(i))
        cout<<i;
    }
    cout<<endl;
}

int main(){
    f2();
    f4();
    f5();
    f6();
    f10();
}