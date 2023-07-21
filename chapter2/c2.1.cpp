#include<iostream>
using namespace std;
int gi;
string gs;

void f3(){
    unsigned u=10,u1=42;
    int i=10,i1=42;
    cout<<u-u1<<endl;
    cout<<u1-u<<endl;
    cout<<u-i<<endl;
    cout<<i-u1<<endl;
}

void f8(){
    cout<<"2M\n"<<endl;
    cout<<"2\tM\n"<<endl;
}

int main(){
    f3();
    f8();

    int li=0;
    string ls;
    cout<<gi <<gs <<li <<ls <<endl;
    return 0;
}