#include<vector>
#include<iostream>
#include<string>
using namespace std;
char f5(unsigned grade){
    char letterScore;
    vector<char>score={'F','E','D','C','B','A'};
    if(grade<60)
    letterScore=score[0];
    else if(grade<70)
    letterScore=score[1];
    else if(grade<80)
    letterScore=score[2];
    else if(grade<90)
    letterScore=score[3];
    else if(grade<=100)
    letterScore=score[4];
    return letterScore;
}

int f9(){
    string s;
    int ans=0;
    cin>>s;
    for(auto i:s)
    if(i=='a'||i=='e'||i=='i'||i=='o'||i=='u')
    ans++;
    return ans;
}

int f12(){
    string s;
    int ans=0;
    cin>>s;
    for(auto i=s.begin();i<s.end()-1;i++)
    if(*i=='f'&&(*(i+1)=='f'||*(i+1)=='i'||*(i+1)=='l'))
    ans++;
    return ans;
}

int main(){
    cout<<f5(87)<<endl;
    cout<<f12()<<endl;
    return 0;
}