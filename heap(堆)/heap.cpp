#include <iostream>
#include <math.h>
using namespace std;

class heap{
public:
    heap(int maxsize){
        key=new int[maxsize+1];
        key[0]=0;
        for(int i=1;i<maxsize+1;i++){
            key[i]=0;
        }
        size=0;
        capacity=maxsize;
    }
    int find(int data){
        for(int i=1;i<size;i++){
            if(key[i]==data){
                return i;
            }
        }
        cout<<"没有找到"<<endl;
        return -1;
    }
    void adjust(int data){
        key[size+1]=data;
        int index=size+1;
        while(index>0) {
            int i = index;
            index = index / 2;
            if (key[index] > key[i]) {
                int temp = key[index];
                key[index] = key[i];
                key[i] = temp;
            }
        }
    }
    void insert(int data){
        if(size==capacity){
            int *an=new int[2*capacity];
            capacity=capacity*2;
            for(int i=0;i<=size;i++){
                an[i]=key[i];
            }
            delete[] key;
            key=an;
        }
        if(key[1]==0){
            key[1]=data;
        }else{
            adjust(data);
        }
        size++;
    }
    void deladjust(int index){
        if(index*2<=size){
            int mn;
            if(key[index*2+1]==0){
                mn=index*2;
            }
            else if(key[index*2]>key[index*2+1]){
                mn=index*2+1;
            }else{
                mn=index*2;
            }
            if(key[index]>key[mn]){
                int temp=key[index];
                key[index]=key[mn];
                key[mn]=temp;
            }
            deladjust(mn);
        }
        return;
    }
    void delmin(){
        key[1]=key[size];
        key[size]=0;
        size--;
        deladjust(1);
    }
    void destroy(){
        for(int i=1;i<=size;i++){
            key[i]=0;
        }
        size=0;
        cout<<"成功清除堆中数据"<<endl;
    }
    void print(){
        int cnt=1;
        for(int i=1;i<=size;i++){
            cout<<key[i]<<" ";
            if(i==cnt){
                cout<<endl;
                cnt=pow(2,cnt)+i;
            }
        }
    }
private:
    int *key;    //动态数组，用来存储树节点的元素
    int size;    //堆中存在的有效元素个数
    int capacity;    //数组容量
};

int main() {
    heap h(15);
    h.insert(13);
    h.insert(21);
    h.insert(16);
    h.insert(24);
    h.insert(31);
    h.insert(19);
    h.insert(68);
    h.insert(65);
    h.insert(26);
    h.insert(32);
    h.insert(20);
    h.insert(15);
    h.insert(18);
    h.insert(33);
    h.insert(34);
    h.insert(35);
//    h.delmin();
//    h.delmin();
    h.print();
    int i= h.find(20);
    cout<<i<<endl;
    system("pause");
    return 0;
}
