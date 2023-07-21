#include<iostream>
#include<vector>
#include<string>

using namespace std;

void f14(){
    int i;
    vector<int> v;
    while(cin>>i)
    v.push_back(i);
}

void f15(){
    string i;
    vector<string> v;
    while(cin>>i)
    v.push_back(i);
}

void f17(){
    string i;
    vector<string> v;
    while(cin>>i)
    v.push_back(i);
    for(auto &i:v){
{        for(auto &j:i)
            j=toupper(j);
        cout<<i<<endl;}
    }
}

void f20(){
    int i;
    vector<int> v;
    while(cin>>i)
    v.push_back(i);
    for(int j=0;j<v.size()-1;j++)
    cout<<v[j]+v[j+1]<<endl;
    for(int j=0;j<v.size();j++)
    cout<<v[j]+v[v.size()-1-j]<<endl;
}

int main(){
    f14();
    f15();
    f17();
    f20();
    return 0;
}