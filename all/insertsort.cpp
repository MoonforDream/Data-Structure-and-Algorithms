#include <iostream>
using namespace std;

//插入排序
void insertsort(int *an,int len){
    for(int i=1;i<=len-1;i++){
        int temp=an[i];
        int j;
        for(j=i;j>0&&an[j-1]>temp;j--){
            an[j]=an[j-1];
        }
        an[j]=temp;
    }
}

int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
    insertsort(an,len);
    for(int i=0;i<len;i++){
        cout<<an[i]<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
