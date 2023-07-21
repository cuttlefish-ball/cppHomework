#include<iostream>
#include<vector>
using namespace std;

int f1(int x,int y){
    return x+y;
}

int f2(int x,int y){
    return x-y;
}

int f3(int x,int y){
    return x*y;
}

int f4(int x,int y){
    return x/y;
}

int main(){

    int(*pf1)(int, int)=f1;
    int(*pf2)(int, int)=f2;
    int(*pf3)(int, int)=f3;
    int(*pf4)(int, int)=f4;

    vector<int(*)(int,int)> a;
    a.push_back(pf1);
    a.push_back(pf2);
    a.push_back(pf3);
    a.push_back(pf4);

    cout<<a[0](2,1)<<a[1](2,1)<<a[2](2,1)<<a[3](2,1)<<endl;
    return 0;
}