#include<iostream>
using namespace std;

void f10(int*x,int*y){
    int temp=*x;
    *x=*y;
    *y=temp;
}

bool f16(const string &s){
    for(auto i:s)
    if(isupper(i))
    return true;
    return false;
}

void f17(string &s){
    for(auto i:s)
    i=tolower(i);
}

int f21(int x,int*y){
    return x>*y? x:*y;
}

void f22(int** x,int**y){
    int *temp=*x;
    *x=*y;
    *y=temp;
}

int f27(initializer_list<int>l){
    int ans=0;
    for(auto i:l){
        ans+=i;
    }
    return ans;
}

int main(){
    int x=1,y=2;
    f10(&x,&y);
    cout<<x<<y<<endl;
    return 0;
}