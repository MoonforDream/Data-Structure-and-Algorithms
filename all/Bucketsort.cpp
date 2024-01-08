#include <iostream>
#include <cstring>
using namespace std;

//��������
void CountSort(int *an,int len) {
    int max=an[0];
    for(int i=0;i<len;i++){
        if(an[i]>max){
            max=an[i];
        }
    }
    int arr[max+1];
    memset(arr,0,sizeof(int)*(max+1));
    for(int i=0;i<len;i++){
        arr[an[i]]++;
    }
    int j=0;
    for(int i=0;i<max+1;i++){
        while (arr[i]>0){
            an[j]=i;
            arr[i]--;
            j++;
        }
    }
}


//��������
void countsort(int *an,int len,int exp){
    int count[10]={0};  //��������
    int ret[len];  //�������
    for(int i=0;i<len;i++){
        count[(an[i]/exp)%10]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    //����ط���Ҫ��β������ͷ����Ϊ�����ͷ������βʱ�����Ǿ��޷�ȷ��ǰ����ֵ�������ȷλ�ã�����
    for(int i=len-1;i>=0;i--){
        ret[count[(an[i]/exp)%10]-1]=an[i];
        count[(an[i]/exp)%10]--;
    }
    for(int i=0;i<len;i++){
        an[i]=ret[i];
    }
}

void RadixSort(int *an,int len){
    int max=an[0];
    int min=an[0];
    for(int i=1;i<len;i++){
        if(an[i]>max){
            max=an[i];
        }
        if(an[i]<min){
            min=an[i];
        }
    }
    for(int i=0;i<len;i++){
        an[i]+=abs(min);
    }
    //����λ�����з���Ͱʽ����
    for(int k=1;max/k>0;k*=10){
        countsort(an,len,k);
    }
    for(int i=0;i<len;i++){
        an[i]-=abs(min);
    }
}


int main() {
    int an[]={7,8,9,10,1,-2,53,26,77,23,1034,-6};
    int len=sizeof(an)/sizeof(an[0]);
//    CountSort(an,len);
    RadixSort(an,len);
    for(int i=0;i<len;i++){
        cout<<an[i]<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
