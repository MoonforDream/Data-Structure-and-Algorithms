#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node *next;
};
typedef Node* Stack;

Stack createStack(int data){
    struct Node* p=new struct Node;
    p->data=data;
    p->next=NULL;
    return p;
}

//��ջ
void Push(Stack &head,int data){
    Stack add= createStack(data);
    if(head==NULL){
        head=add;
    }else{
        Node* p=head;
        add->next=p;
        head=add;
    }
}

//��ջ
void Pop(Stack &head){
    if(head==NULL){
        cout<<"ջ��û������"<<endl;
        return;
    }
    Node* p=head;
    head=p->next;
    delete p;
}

//��ȡջ��Ԫ��
int top(Stack head){
    return head->data;
}


//��ӡջ
void printStack(Stack head){
    if(head==NULL){
        cout<<"ջ��û������"<<endl;
        return;
    }
    Node* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//��ȡջ�Ĵ�С
int Size(Stack head){
    Node* p=head;
    int cnt=0;
    if(p->data&&p->next==NULL){
        cnt=1;
    } else{
        while (p!=NULL){
            cnt++;
            p=p->next;
        }
    }
    return cnt;
}

//�ж�ջ�Ƿ�Ϊ��
bool empty(Stack head){
    if (head!=NULL){
        return false;
    }else{
        return true;
    }
}

//���ջ
void destroy(Stack &head){
    if(head==NULL){
        cout<<"ջ��û������"<<endl;
        return;
    }
    Node* tail=head->next;
    while (head!=NULL){
        delete head;
        head=tail;
        if(tail!=NULL)
            tail=tail->next;
        else
            return;
    }
}


class stack{
public:
    //��ջ
    void Push(int data){
        head.push_back(data);
    }

    //��ջ
    void Pop(){
        if(head.empty()){
            cout<<"ջ��û�����ݣ�"<<endl;
            return;
        } else
            head.pop_back();
    }

    //��ȡջ��Ԫ��
    int top(){
        if(head.empty()){
            cout<<"ջ��û�����ݣ�"<<endl;
            return NULL;
        }
        return head.back();
    }

    //��ӡջ
    void printstack(){
        if(head.empty()){
            cout<<"ջ��û������"<<endl;
            return;
        }else{
            for(vector<int>::const_iterator it=head.end()-1;it>=head.begin();it--){
                cout<<*it<<" ";
            }
            cout<<endl;
        }
    }

    //���ջ
    void destroy(){
        head.clear();
    }

    //��ȡջ�Ĵ�С
    int Size(){
        return head.size();
    }

    //�ж�ջ�Ƿ�Ϊ��
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
//    Stack head=NULL;
//    Push(head,10);
//    Push(head,20);
//    Pop(head);
//    printStack(head);
//    destroy(head);
//    if(!empty(head)){
//        int a= Size(head);
//        cout<<a<<endl;
//    }
//    printStack(head);
    stack s;
    s.Push(10);
    s.Push(20);
    s.printstack();
    s.destroy();
    if(s.empty()){
        int a=s.top();
        int b=s.Size();
        cout<<a<<' '<<b<<endl;
    }
    system("pause");
    return 0;
}
