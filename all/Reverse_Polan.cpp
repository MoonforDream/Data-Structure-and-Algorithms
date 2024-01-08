#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

bool flag(char a,char b){
    int a1,b1;
    if(a=='+'||a=='-'){
        a1=1;
    }else if(a=='*'||a=='/'){
        a1=2;
    }else if(a=='('||a==')'){
        a1=3;
    }
    if(b=='+'||b=='-'){
        b1=1;
    }else if(b=='*'||b=='/'){
        b1=2;
    }else if(b=='('||b==')'){
        b1=3;
    }
    return a1>=b1;
}

vector<char> reversePolan(char *an,int len){
    stack<char>s;
    vector<char>v;
    int cnt=0;
    for(int i=0;i<len;i++){
        if(an[i]!='+'&&an[i]!='-'&&an[i]!='*'&&an[i]!='/'&&an[i]!='('&&an[i]!=')'){
            v.push_back(an[i]);
        }else if(an[i]=='+'||an[i]=='-'||an[i]=='*'||an[i]=='/'||an[i]=='('||an[i]==')'){
            if(s.empty()){
                s.push(an[i]);
            }else if(an[i]=='('){
                s.push(an[i]);
                cnt=1;
            }else if(an[i]==')'&&cnt==1){
                while (s.top()!='('){
                    v.push_back(s.top());
                    s.pop();
                }
                s.pop();
                cnt=0;
            } else if(flag(s.top(),an[i])){
                while (!s.empty()){
                    if(s.top()=='('){
                        break;
                    }
                    v.push_back(s.top());
                    s.pop();
                }
                s.push(an[i]);
            }else{
                s.push(an[i]);
            }
        }
    }
    if(!s.empty()){
        while (!s.empty()){
            v.push_back(s.top());
            s.pop();
        }
    }
    return v;
}


int main() {
    char an[]={'a','+','b','*','c','+','(','d','*','e','+','f',')','*','g'};
    int len= sizeof(an)/ sizeof(an[0]);
    auto a= reversePolan(an,len);
    for(char i:a){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
