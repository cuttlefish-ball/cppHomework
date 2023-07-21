#include<iostream>
using namespace std;

class Sales_data{
    friend Sales_data add(const Sales_data&,const Sales_data&);
    friend istream &read(istream&,Sales_data&);
    friend ostream &print(ostream&,Sales_data&);

    private:
    string bookNo;
    double revenue=0.0;
    unsigned untis_sold=0;

    public:
    Sales_data(const string &s,double r,unsigned u):bookNo(s),revenue(r),untis_sold(u){}
    Sales_data(istream &s){read(s,*this);}

    string ISBN() const {return this->bookNo;}

    Sales_data & combine(const Sales_data &r){
        untis_sold+=r.untis_sold;
        revenue+=r.untis_sold;
        return *this;
    }
};

Sales_data add(const Sales_data& a,const Sales_data& b){
    Sales_data sum=a;
    sum.combine(b);
    return sum;
}

istream &read(istream& is,Sales_data& a){
    double price=0.0;
    is>>a.bookNo>>a.untis_sold>>price;
    a.revenue=price*a.untis_sold;
    return is;
}

ostream &print(ostream& os,Sales_data& a){
    os<<a.bookNo<<" "<<a.untis_sold<<" "<<a.revenue<<endl;
    return os;
}

int main(){
    return 0;
}