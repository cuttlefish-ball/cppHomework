#include<vector>
#include<iostream>
#include<string>
using namespace std;

bool comp(vector<int>a1,vector<int>a2){
    for(int i=0;i<a2.size();i++)
    if(a1[i]!=a2[i])
    return false;
    return true;
}

bool f17(vector<int>a1,vector<int>a2){
    if(a1.size()>=a2.size())
    return comp(a1,a2);
    else
    return comp(a2,a1);
}

int main(){
    vector<int> a1={0,1,2,2};
    vector<int> a2={0,1};
    cout<<f17(a1,a2)<<endl;
    return 0;
}