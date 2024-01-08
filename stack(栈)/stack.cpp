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

//进栈
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

//出栈
void Pop(Stack &head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
        return;
    }
    Node* p=head;
    head=p->next;
    delete p;
}

//获取栈顶元素
int top(Stack head){
    return head->data;
}


//打印栈
void printStack(Stack head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
        return;
    }
    Node* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//获取栈的大小
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

//判断栈是否为空
bool empty(Stack head){
    if (head!=NULL){
        return false;
    }else{
        return true;
    }
}

//清空栈
void destroy(Stack &head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
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
    //入栈
    void Push(int data){
        head.push_back(data);
    }

    //出栈
    void Pop(){
        if(head.empty()){
            cout<<"栈中没有数据！"<<endl;
            return;
        } else
            head.pop_back();
    }

    //获取栈顶元素
    int top(){
        if(head.empty()){
            cout<<"栈中没有数据！"<<endl;
            return NULL;
        }
        return head.back();
    }

    //打印栈
    void printstack(){
        if(head.empty()){
            cout<<"栈中没有数据"<<endl;
            return;
        }else{
            for(vector<int>::const_iterator it=head.end()-1;it>=head.begin();it--){
                cout<<*it<<" ";
            }
            cout<<endl;
        }
    }

    //清空栈
    void destroy(){
        head.clear();
    }

    //获取栈的大小
    int Size(){
        return head.size();
    }

    //判断栈是否为空
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
