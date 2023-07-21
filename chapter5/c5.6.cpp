#include<iostream>

using namespace std;

int main(){
    int x,y;
    cin>>x>>y;
    try
    {
        cout<<(double)x/y<<endl;
    }
    catch(exception e)
    {
        cout<<"除数不能为0"<<endl;
    }
    return 0;
}