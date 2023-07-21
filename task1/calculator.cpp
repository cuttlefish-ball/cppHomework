#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

double op(double x,double y, string z){
   
    if(z=="+")
    return x+y;
    if(z=="-")
    return x-y;
    if(z=="*")
    return x*y;
    if(z=="/")
    return x/y;
    return 0;
}

int prior(char c){
	if(c == '+' || c == '-'){
		return 1;
	}else if(c == '*' || c == '/'){
		return 2;
	}else{
		return 0;
	}
	
} 

vector<string> to_postfix(string s){
    vector<string> vs;
    stack<char> st;
    for(int i=0;i<s.length();i++){
        string tmp;
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
            if(st.empty()||st.top()=='(')
            st.push(s[i]);
            else{
                while(!st.empty() && prior(st.top()) >= prior(s[i])){
                    tmp += st.top();
					vs.push_back(tmp);
					st.pop();
					tmp = "";
                }
                st.push(s[i]);
            }
        }
        if(s[i]=='('){
            st.push(s[i]);
        }
        if(s[i]==')'){
            while(st.top() != '('){
					tmp += st.top();
					vs.push_back(tmp);
					st.pop();
					tmp = "";
				}
				st.pop();
        }
        if((s[i]>='0' && s[i]<='9')){
            	tmp += s[i];
            	while(i+1<s.size() && s[i+1]>='0' && s[i+1]<='9'||s[i+1] == '.')
            	{
                	tmp += s[i+1];
                	++i;
   				}
            	vs.push_back(tmp);
  			}
    }
    while(!st.empty()){
		string tmp = "";
		tmp += st.top();
		vs.push_back(tmp);
		st.pop();
	}
    return vs;
}

double calculate(vector<string> s){
    double num,x,y;
    stack<double> st;
    for(auto i:s){
        if(i=="+"||i=="-"||i=="*"||i=="/"){
            y=st.top();
            st.pop();
            x=st.top();
            st.pop();
            st.push(op(x,y,i));
        }
        else{
            num=atof(i.c_str());
            st.push(num);
        }
    }
    return st.top();
} 

int main(){
    string s;
    double ans;
    while(cin>>s){
        ans=calculate(to_postfix(s));
        cout<<ans<<endl;
    }
    return 0;
}