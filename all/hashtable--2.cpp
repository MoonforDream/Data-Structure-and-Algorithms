#include <iostream>
#include <vector>
using namespace std;

//开放定址法
class hashtable{
public:
    bool isprime(int n){
        if(n<=1)
            return false;
        for(int i=2;i*i<n;i++){
            if(n%i==0){
                return false;
            }
        }
        return true;
    }

    int prime(int size){
        while (!isprime(size)){
            size++;
        }
        return size;
    }
    hashtable(int size){
        this->tablesize= prime(size);
        for(int i=0;i<tablesize;i++){
            v.push_back(NULL);
        }
    }
    //线性探测法
    int hash1(int key){
        int index=key%tablesize;
        int cnt=0;
        while (v[index]!=NULL){
            if(cnt>1){
                cout<<"没有空余的位置插入"<<endl;
                return -1;
            }
            if(index==tablesize-1){
                cnt++;
                index=0;
                continue;
            }
            index++;
        }
        return index;
    }

    //平方探测法
    int hash2(int key){
        int index=key%tablesize;
        int cnt=0,n=0,i=0;
        while (v[index]!=NULL){
            if(i>1){
                cout<<"没有空余的位置插入"<<endl;
                return -1;
            }
            cnt++;
            cnt*=cnt;
            index=index+cnt-n;
            n=cnt;
            if(index>tablesize-1){
                i++;
                index=index-tablesize;
            }
        }
        return index;
    }
    float localfactor(){
        return (float)count/(float)tablesize;
    }
    void insert(int key){
        if(localfactor()>0.5||localfactor()==0.5){
            int size=tablesize*2;
            for(int i=tablesize;i<size;i++){
                v.push_back(NULL);
            }
            tablesize=size;
        }
        int index=hash2(key);
        if(index!=-1){
            v[index]=key;
            count++;
        }
    }
    int find(int key){
        int index=key%tablesize;
        int size=tablesize;
        for(int i=index;i<=size+index;i++){
            if(v[i]==key){
                return i;
            }
            if(i==tablesize-1){
                size=0;
                i=0;
            }
        }
        cout<<"为找到"<<endl;
        return -1;
    }
    void del(int key){
        int index=find(key);
        if(index!=-1){
            count--;
            v[index]=NULL;
        }
        return;
    }
    void print(){
        for(int i=0;i<tablesize;i++){
            cout<<"索引为"<<i<<": "<<v[i]<<endl;
        }
    }

private:
    int count;
    vector<int>v;
    int tablesize;
};


int main() {
    hashtable ht(10);
//    ht.insert(11);
//    ht.insert(13);
//    ht.insert(11);
    ht.insert(43);
    ht.insert(81);
    ht.insert(81);
    ht.insert(81);
    ht.insert(45);
    ht.insert(80);
    ht.del(80);
    ht.print();
    system("pause");
    return 0;
}
