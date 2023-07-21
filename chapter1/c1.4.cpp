#include <iostream>
using namespace std;
void f9 (){
    int i=49,ans=0;
    while(++i!=100)
    {
        ans+=i;
    }
    cout<<ans<<endl;
}

void f10(){
    for(int i=10;i>=0;i--)
    cout<<i<<endl;
}

void f11(){
    int l=0,r=0;
    cin>>l>>r;
    if(l>r)
    {
        int i=l;
        l=r;
        r=i;
    }
    while(l<=r)
    cout<<l++<<endl;
}

void f16(){
    int sum=0,a=0;
    while(cin>>a){
        sum+=a;
    }
    cout<<sum<<endl;
}

int main(){
    f9();
    f10();
    f11();
    f16();
    return 0;
}