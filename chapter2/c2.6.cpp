#include<iostream>
#include"Sales_data.h"
using namespace std;

int main(){
    Sales_data item1={"111",3,20};
    Sales_data item2={"111",2,25};
    if(item1.bookNo==item2.bookNo)
    cout<<item1.revenue*item1.untis_sold+item2.revenue*item2.untis_sold<<endl;
    return 0;
}