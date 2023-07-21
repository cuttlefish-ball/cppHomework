#include<iostream>
using namespace std;

void f43(){
    int ia[3][2]={{0,1},{2,3},{4,5}};
    for (auto &i:ia){
        for(auto &j:i)
        cout<<j<<endl;
    }

    for (int i=0;i<3;i++){
        for(int j=0;j<2;j++)
        cout<<ia[i][j]<<endl;
    }

    for (int i=0;i<3;i++){
        for(int j=0;j<2;j++)
        cout<<*(*(ia+i)+j)<<endl;
    }
}

int main(){
    f43();
    return 0;
}