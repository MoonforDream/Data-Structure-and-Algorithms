#include <iostream>
using namespace std;

//希尔排序
void shellsort(int *an,int len){
    for(int i=(len-1)/2;i>0;i/=2){
        //插入排序
        for(int j=i;j<len;j++){
            int temp=an[j],k;
            //根据增量i进行分序列排序
            for(k=j;k>=i&&temp<an[k-i];k-=i){
                an[k]=an[k-i];
            }
            an[k]=temp;
        }
    }
}

//将Sedgewick增量序列列出，以便使用
//    const int sedgewick[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161,
//                              3905, 8929, 16001, 36289, 64769, 146305,
//                              260609, 587521, 1045505, 2354689, 4188161,
//                              9427969, 16764929, 37730305, 67084289,
//                              150958081, 268386305, 603906049, 1073643521 };


//使用Sedgewick增量的希尔排序
void shellsort_pro(int* an,int len){
    /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
    int Sedgewick[] = {260609,146305,64769,36289,
                       16001,8929,3905,2161,929, 505,
                       209, 109, 41, 19, 5, 1, 0};
    int k;
    for(k=0;Sedgewick[k]>=len;k++);
    for(int d=Sedgewick[k];d>0;d=Sedgewick[++k]){
        for(int i=d;i<len;i++){
            int temp=an[i];
            int j;
            for(j=i;j>=d&&an[j-d]>temp;j-=d){
                an[j]=an[j-d];
            }
            an[j]=temp;
        }
    }
}

int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
//    shellsort(an,len);
    shellsort_pro(an,len);
    for(int i=0;i<len;i++)
        cout<<an[i]<<" ";
    cout<<endl;
    system("pause");
    return 0;
}
