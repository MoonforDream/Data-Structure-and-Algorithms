#include <iostream>
using namespace std;

void insertsort(int* an,int low,int high){
    for(int i=low+1;i<=high;i++){
        int temp=an[i];
        int j;
        for(j=i;j>0&&an[j-1]>temp;j--){
            an[j]=an[j-1];
        }
        an[j]=temp;
    }
}

//三数中值分割法选取枢纽元
int midian3(int *an,int left,int right){
    int center=(left+right)/2;
    if(an[left]>an[center]){
        swap(an[left],an[center]);
    }
    if(an[left]>an[right]){
        swap(an[left],an[right]);
    }
    if(an[center]>an[right]){
        swap(an[center],an[right]);
    }
    //因为上述操作已经满足an[left]<an[center]<an[right]，an[right]大于枢纽元，我不需要进行交换让其在比较一位
    //因此让枢纽元跟right-1位置交换，这样在排序时减轻了右边数组的压力
    swap(an[center],an[right-1]);
    return an[right-1];   //返回枢纽元
}

void Qsort(int* an,int left,int right){
    if(left+10<=right){
        int pivot=midian3(an,left,right);
        int i=left,j=right-1;
        for(;;){
            while (an[++i]<pivot){}
            while (an[--j]>pivot){}
            if(i<j){
                swap(an[i],an[j]);
            }else{
                break;
            }
        }
        swap(an[i],an[right-1]);
        Qsort(an,left,i-1);
        Qsort(an,i+1,right);
    }
    else{
        insertsort(an,left,right);
    }
}

//快速排序
void quicksort(int *an,int len){
    Qsort(an,0,len-1);
}


void quicksort1(int *an,int low,int high){
    int left=low,right=high;
    if(left>= right) return;
    int temp=an[left];
    while (left!=right){
        while (an[right]>=temp&&left<right){
            right--;
        }
        while (an[left]<=temp&&left<right){
            left++;
        }
        if(left<right){
            swap(an[left],an[right]);
        }
    }
    swap(an[low],an[left]);
    quicksort1(an,low,left-1);
    quicksort1(an,left+1,high);
}

int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
    quicksort(an,len);
//    quicksort1(an,0,len-1);
    for(int i=0;i<len;i++)
        cout<<an[i]<<" ";
    cout<<endl;
    system("pause");
    return 0;
}
