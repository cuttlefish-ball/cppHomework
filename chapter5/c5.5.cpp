#include<iostream>
#include<string.h>
using namespace std;

int main(){
    char s1[20],s2[20];
    scanf("%s",&s1);
    while(1){
        scanf("%s",&s2);
        if(strcmp(s1,s2)==0)
        break;
        strcpy(s1,s2);
    }
    return 0;
}