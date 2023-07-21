#include<iostream>
using namespace std;

int fact(int x){
    if(x==0)
    return 1;
    else
    return x*fact(x-1);
}

int f7(){
    static int x=0;
    return x++;
}

int main(){
    int x;
    cin>>x;
    cout<<fact(x)<<endl;
    for(int i=0;i<5;i++)
    cout<<f7()<<endl;
    return 0;
}