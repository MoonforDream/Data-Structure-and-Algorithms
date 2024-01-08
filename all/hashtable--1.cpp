#include <iostream>
#include <vector>
using namespace std;

//分离链接法
//定义链表
template<class T>
struct listnode{
    T data;
    listnode* next;
    int cnt;
};


template<class T>
class hashtable{
public:
    int isPrime(int num) {
        if(num <= 1) {
            return 0;
        }
        int i;
        for(i = 2; i*i <= num; i++) {
            if(num % i == 0) {
                return 0;
            }
        }
        return 1;
    }
    //找出大于tablesize最近的素数
    int prime(int size){
        while (!isPrime(size)) {
            size++;
        }
        return size;
    }
    float loadfactor(){
        return (float)count/(float)tablesize;
    }
    listnode<T>* createNode(T data){
        listnode<T>* list=(listnode<T>*)malloc(sizeof(listnode<T>));
        list->data=data;
        list->next= nullptr;
        list->cnt=1;
        return list;
    }
    hashtable(int size){
        this->count=0;
        this->tablesize=prime(size);
        for(int i=0;i< this->tablesize;i++){
            listnode<T>*list=(listnode<T>*)malloc(sizeof(listnode<T>));
            list->next=NULL;
            list->cnt=0;
            v.push_back(list);
        }
    }
    //散列函数(哈希函数)，用于将关键字处理得到映射的数组下标，这里用了简单的哈希函数，在不同场景有不同的函数设计
    int hash(T data){
        return data%this->tablesize;
    }

    listnode<T>* findnode(listnode<T>* head,T data){
        if(head!= nullptr){
            listnode<T>* p=head;
            while (p!= nullptr){
                if(p->data==data){
                    return p;
                }
                p=p->next;
            }
        }
        return NULL;
    }

    void insert(T data){
        if(loadfactor()>1||loadfactor()==1){
            int size= this->tablesize;
            this->tablesize=prime(count*2);
            for(int i=size;i< this->tablesize;i++){
                listnode<T>*list=(listnode<T>*)malloc(sizeof(listnode<T>));
                list->next=NULL;
                list->cnt=0;
                v.push_back(list);
            }
        }
        int index= hash(data);
        if(nullptr==v[index]->next){
            listnode<T>* list= createNode(data);
            v[index]->next=list;
        } else{
            listnode<T>* tail=findnode(v[index]->next,data);
            if(tail==NULL){
                listnode<T>* list= createNode(data);
                listnode<T>* p=v[index]->next;
                v[index]->next=list;
                v[index]->next->next=p;
            }else{
                tail->cnt++;
            }
        }
        this->count++;
    }
    listnode<T>* find(T data){
        int index= hash(data);
        listnode<T>* p=findnode(v[index]->next,data);
        return p;
    }
    void print(){
        for(int i=0;i< this->tablesize;i++){
            listnode<T>* p=v[i]->next;
            cout<<"索引为"<<i<<":"<<" ";
            if(p== nullptr){
                cout<<endl;
                continue;
            }
            while (p!= nullptr){
                for(int j=0;j<p->cnt;j++)
                    cout<<p->data<<" ";
                p=p->next;
            }
            cout<<endl;
        }
    }
    void del(T data){
        int index= hash(data);
        listnode<T>* tail=v[index]->next;
        listnode<T>* p=v[index];
        while (tail->next!= nullptr){
            if(tail->data==data){
                break;
            }
            p=tail;
            tail=tail->next;
        }
        if(tail->data==data){
            if(tail->cnt>1){
                tail->cnt--;
                count--;
                return;
            }
            p->next=tail->next;
            delete tail;
            count--;
        }
        return;
    }
private:
    int count;
    vector<listnode<T>*>v;
    int tablesize;
};

int main() {
    hashtable<int>ht(10);
    ht.insert(10);
    ht.insert(13);
    ht.insert(30);
    ht.insert(43);
    ht.insert(81);
    ht.insert(81);
    ht.insert(45);
    ht.insert(33);
    ht.insert(34);
    ht.insert(44);
    ht.insert(12);
    ht.insert(13);
    ht.print();
//    listnode<int>*p=ht.find(81);
//    cout<<p->data<<endl;
//    ht.del(13);
//    ht.print();
    system("pause");
    return 0;
}
