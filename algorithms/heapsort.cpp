#include <iostream>
using namespace std;
#define leftchild(i) (2*(i)+1)    //定义宏函数，找到根节点的左孩子

//构建堆
void buildheap(int* an,int len,int index){
    int temp,child;
    for(temp=an[index];leftchild(index)<len;index=child){
        child=leftchild(index);
        if(child!=len-1&&an[child+1]>an[child]){
            child++;
        }
        if(an[child]>temp){
            an[index]=an[child];
        }else{
            break;
        }
    }
    an[index]=temp;
}

//堆排序
void heapsort(int* an,int len){
    for(int i=(len-1)/2;i>=0;i--){
        buildheap(an,len,i);
    }
    for(int i=len-1;i>0;i--){
        int temp=an[0];
        an[0]=an[i];
        an[i]=temp;
        buildheap(an,i,0);
    }
}

int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
    heapsort(an,len);
    for(int i=0;i<len;i++)
        cout<<an[i]<<" ";
    cout<<endl;
    system("pause");
    return 0;
}
