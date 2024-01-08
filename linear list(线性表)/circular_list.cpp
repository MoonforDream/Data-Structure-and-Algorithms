#include <iostream>

using namespace std;

struct CirNode{
    int data;
    struct CirNode* next;
    struct CirNode *prev;
};

struct CirNode* createNode(int data){
//    struct CirNode* p=(struct CirNode*)malloc(sizeof(struct CirNode));
    struct CirNode* p=new struct CirNode;
    p->data=data;
    p->next=NULL;
    p->prev=NULL;
    return p;
}

struct CirNode* inserthead(CirNode* head,int data){
    struct CirNode* add= createNode(data);
    if(head==NULL){
        add->next=add;
        add->prev=add;
        return add;
    }
    struct CirNode* p=head;
    struct CirNode* p1=head->next;
    while (p1!=head){
        p1=p1->next;
    }
    head=add;
    head->next=p;
    p1->next=head;
    head->prev=p1;
    p->prev=head;
    return head;
}

//尾插法
struct CirNode* insertlast(CirNode* head,int data){
    struct CirNode* add= createNode(data);
    if(head==NULL){
        add->prev=add;
        add->next=add;
        return add;
    }
    struct CirNode* p=head;
    while(p->next!=head){
        p=p->next;
    }
    p->next=add;
    add->prev=p;
    add->next=head;
    return head;
}

struct CirNode* del(CirNode* head,int data){
    if(head==NULL){
        cout<<"链表没有数据"<<endl;
        return head;
    }
    if(head->data==data){
        struct CirNode* p=head->next;
        p->prev=head->prev;
//        free(head);
        delete head;
        return p;
    }
    struct CirNode* tail=head;
    struct CirNode* p=head->next;
    while (p!=head){
        if(p->data==data){
            tail->next=p->next;
            p->next->prev=tail;
//            free(p);
            delete p;
            return head;
        }
        tail=p;
        p=p->next;
    }
}

void printlist(CirNode* head){
    if(head==NULL){
        cout<<"链表没有数据"<<endl;
    }
    struct CirNode* p=head;
    do{
        cout<<p->data<<" ";
        p=p->next;
    } while (p!=head);
    cout<<endl;
}

int main() {
    struct CirNode* head=NULL;
    head=inserthead(head,10);
    head=inserthead(head,20);
    head=insertlast(head,20);
    head=insertlast(head,10);
    head= del(head,10);
    printlist(head);
    system("pause");
    return 0;
}
