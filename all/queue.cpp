#include <iostream>
#include <vector>
using namespace std;

//链表实现
struct Queue{
    int data;
    Queue* next;
};

Queue* createNode(int data){
    auto p=new Queue;
    p->data=data;
    p->next=NULL;
    return p;
}

//入队
void push(Queue* &head,int data){
    Queue* add= createNode(data);
    if (head==NULL){
        head=add;
    }else{
        Queue* p=head;
        while (p->next!=NULL){
            p=p->next;
        }
        p->next=add;
    }
}

//出队
void pop(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* p=head;
    head=p->next;
    delete p;
}

//获取队首元素
int front(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return NULL;
    }
    return head->data;
}

//打印队列
void print(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//清空队列
void destroy(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* tail=head->next;
    while (head!=NULL){
        delete head;
        head=tail;
        if(tail!=NULL)
            tail=tail->next;
        else
            return;
    }
}



//数组实现
class queue{
public:
    //入队(向数组末尾插入数据)
    void Push(int data){
        head.push_back(data);
    }

    //出队(将数组第一个元素删除)
    void Pop(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return;
        } else{
            auto it=head.begin();
            head.erase(it);
        }
    }

    //获取队首元素
    int front(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return NULL;
        }
        return head[0];
    }

    //打印队列
    void print(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return;
        }
        for(int i:head){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    //清空队列
    void destroy(){
        head.clear();
    }

    //获取队列大小
    int size(){
        return head.size();
    }

    //判断队列是否为空
    bool empty(){
        if(head.empty()){
            return true;
        } else{
            return false;
        }
    }

private:
    vector<int>head;
};


int main() {
    Queue* head=NULL;
    push(head,20);
    push(head,10);
    push(head,30);
    pop(head);
    int a= front(head);
    cout<<a<<endl;
    print(head);
    destroy(head);
    print(head);
//    queue q;
//    q.Push(20);
//    q.Push(10);
//    q.Push(30);
//    q.Pop();
//    int a=q.front();
//    cout<<a<<endl;
//    q.print();
    system("pause");
    return 0;
}
