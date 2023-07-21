#include<iostream>
using namespace std;

class Screen{
    public:
    typedef string::size_type pos;
    Screen()=default;
    Screen(char c,pos h,pos w):height(h),width(w),contents(h*w,c){}
    Screen(pos h,pos w):height(h),width(w),contents(""){}
    char get() const{return contents[cursor];}
    char get(pos r,pos c) const{return contents[r*width+c];};
    Screen &move(pos r,pos c){
        cursor=r*width+c;
        return *this;
    }
    Screen &set(char c){
        contents[cursor]=c;
        return *this;
    }
    Screen &display(ostream &os){
        os<<contents;
        return *this;
    }


    private:
    pos cursor=0;
    pos height=0,width=0;
    string contents;
};

int main(){
    Screen myScreen('X',5,5);
    myScreen.move(4,0).set('#').display(cout);
    cout<<"\n";
    myScreen.display(cout);
    cout<<"\n";
    return 0;
}