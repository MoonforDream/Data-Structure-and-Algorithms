#include <iostream>
using namespace std;


//合并操作
void merge(int*an,int *temarr,int lpos,int rpos,int rightend){
    int leftend=rpos-1;
    int nums=(rightend-lpos)+1;
    int tempos=lpos;
    //进行比较lpos和rpos位上的元素
    while (lpos<=leftend&&rpos<=rightend){
        if(an[lpos]<an[rpos]){
            temarr[tempos++]=an[lpos++];
        }else{
            temarr[tempos++]=an[rpos++];
        }
    }
    while (lpos<=leftend){       //处理left数组的剩余元素
        temarr[tempos++]=an[lpos++];
    }
    while (rpos<=rightend){     //处理right数组的剩余元素
        temarr[tempos++]=an[rpos++];
    }
    //使用rightend保证给an数组赋值的正确位置
    for(int i=0;i<nums;i++,rightend--){
        an[rightend]=temarr[rightend];
    }
}


//递归分治调用
void midsort(int* an,int *temarr,int left,int right){
    if(left<right){
        int center=(left+right)/2;
        midsort(an,temarr,left,center);
        midsort(an,temarr,center+1,right);
        merge(an,temarr,left,center+1,right);
    }
}

//归并排序
void mergesort(int *an,int len){
    int *temarr=new int[len];
    midsort(an,temarr,0,len-1);
}

int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
    mergesort(an,len);
    for(int i=0;i<len;i++)
        cout<<an[i]<<" ";
    cout<<endl;
    system("pause");
    return 0;
}
