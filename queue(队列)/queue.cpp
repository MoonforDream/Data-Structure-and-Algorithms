#include <iostream>
#include <vector>
using namespace std;

//����ʵ��
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

//���
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

//����
void pop(Queue* &head){
    if(head==NULL){
        cout<<"������û��Ԫ��"<<endl;
        return;
    }
    Queue* p=head;
    head=p->next;
    delete p;
}

//��ȡ����Ԫ��
int front(Queue* &head){
    if(head==NULL){
        cout<<"������û��Ԫ��"<<endl;
        return NULL;
    }
    return head->data;
}

//��ӡ����
void print(Queue* &head){
    if(head==NULL){
        cout<<"������û��Ԫ��"<<endl;
        return;
    }
    Queue* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//��ն���
void destroy(Queue* &head){
    if(head==NULL){
        cout<<"������û��Ԫ��"<<endl;
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



//����ʵ��
class queue{
public:
    //���(������ĩβ��������)
    void Push(int data){
        head.push_back(data);
    }

    //����(�������һ��Ԫ��ɾ��)
    void Pop(){
        if(head.empty()){
            cout<<"������û�����ݣ�"<<endl;
            return;
        } else{
            auto it=head.begin();
            head.erase(it);
        }
    }

    //��ȡ����Ԫ��
    int front(){
        if(head.empty()){
            cout<<"������û�����ݣ�"<<endl;
            return NULL;
        }
        return head[0];
    }

    //��ӡ����
    void print(){
        if(head.empty()){
            cout<<"������û�����ݣ�"<<endl;
            return;
        }
        for(int i:head){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    //��ն���
    void destroy(){
        head.clear();
    }

    //��ȡ���д�С
    int size(){
        return head.size();
    }

    //�ж϶����Ƿ�Ϊ��
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
