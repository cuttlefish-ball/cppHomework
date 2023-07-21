#include<iostream>
#include<vector>
#include<string>
using namespace std;

void f23(){
    vector<int> v={1,2,3,4,5,6,7,8,9,10};
    for(auto i=v.begin();i<v.end();i++)
        {
            *i*=2;
            cout<<*i<<endl;
        }
}

void f24(){
    int i;
    vector<int> v;
    while(cin>>i)
    v.push_back(i);
    for(auto j=v.begin();j<v.end()-1;j++)
    cout<<*j+*(j+1)<<endl;
    for(auto j=v.begin(), k=v.end();j<v.end();j++,k--)
    cout<<*j+*(k-1)<<endl;
}

void f25(){
    vector<unsigned> scores(11,0);
    unsigned grade;
    auto i=scores.begin();
    while(cin>>grade){
        if(grade<=100)
        *(i+grade/10)+=1;
    }
    // for(auto i:scores)
    // cout<<i<<endl;
}

int main(){
    f23();
    f24();
    f25();
    return 0;
}