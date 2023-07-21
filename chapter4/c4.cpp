#include<iostream>
#include<vector>
using namespace std;
bool f6(int x){
    return x%2==0;
}

void f10(){
    int x;
    while(cin>>x)
    if(x==42)
    break;
}

void f21(vector<int> v){
    for(auto &i:v){
        if(i%2==1)
        i*=2;
    }
}

int main(){
    cout<<f6(3)<<endl;
    vector<int> v={1,2,3,4,5};
    f21(v);
    return 0;
}