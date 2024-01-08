#include <iostream>
#include <string>
using namespace std;

void getnext(int *next,const string& s,int size){
    //初始化
    int j=0;
    next[0]=0;
    for(int i=1;i<size;i++){
        //前后缀不相等情况
        while (j>0&&s[i]!=s[j]){
            j=next[j-1];    //回溯找到相等位置或者回到0
        }
        //前后缀相同情况
        if(s[i]==s[j]) j++;
        next[i]=j;
    }
}


int KMP(const string &text,const string &mode){
    int len=text.size();
    if(len==0) return 0;
    int size=mode.size();
    int j=0,next[size];
    getnext(next,mode,size);
    for(int i=0;i<len;i++){
        while (j>0&&text[i]!=mode[j]){
            j=next[j-1];
        }
        if(text[i]==mode[j]) j++;
        if(j==size) return (i-j+1);
    }
    return -1;
}


int main() {
    string text="mississippi";   //文本串
    string mode="issip";     //模式串
    cout<<KMP(text,mode);
     system("pause");
    return 0;
}
