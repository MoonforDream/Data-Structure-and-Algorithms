#include <iostream>
using namespace std;

//冒泡排序
//冒泡排序时间复杂度O(n²)
void bubbleSort(int an[],int len){
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len-1-i;j++){
            if(an[j]>an[j+1]){
                int temp=an[j+1];
                an[j+1]=an[j];
                an[j]=temp;
            }
        }
    }
}


int main() {
    int an[]={3,7,10,-1,20,10,55,70,80,90};
    int len=sizeof(an)/sizeof(an[0]);  //求数组元素个数
    bubbleSort(an,len);
    for(int i=0;i<len;i++){
        cout<<an[i]<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
