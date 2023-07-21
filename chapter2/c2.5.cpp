#include<iostream>
using namespace std;

void f35(){
    const int i=1;
    auto j=i;
    const auto &k=i;
    auto *p=&i;
    cout<<typeid(i).name()<<endl;
    cout<<typeid(j).name()<<endl;
    cout<<typeid(k).name()<<endl;
    cout<<typeid(p).name()<<endl;
}

int main(){
    f35();
    return 0;
}