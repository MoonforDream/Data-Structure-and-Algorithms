#include <iostream>
using namespace std;

struct doublyNode{
    int data;
    struct doublyNode* next;
    struct doublyNode* prev;
};

struct doublyNode *createNode(int data){
    auto* p=(struct doublyNode*)malloc(sizeof(struct doublyNode));
    p->data=data;
    p->prev=NULL;
    p->next=NULL;
    return p;
}

//头插法
struct doublyNode*inserthead(struct doublyNode* head,int data){
    struct doublyNode*add= createNode(data);
    if(head==NULL){
        return add;
    }
    struct doublyNode*p=head;
    head=add;
    head->next=p;
    p->prev=head;
    return head;
}

//尾插法
struct doublyNode * insertlast(struct doublyNode* head,int data){
    struct doublyNode* add= createNode(data);
    if(head==NULL){
        return add;
    }
    struct doublyNode*p=head;
    while (p->next!=NULL){
        p=p->next;
    }
    p->next=add;
    p->prev=p;
    return head;
}

//删除
doublyNode * del(struct doublyNode* head,int data){
    if(head==NULL){
        cout<<"链表没有数据"<<endl;
        return head;
    }
    if(head->data==data){
        struct doublyNode* p=head->next;
        free(head);
        return p;
    }
    struct doublyNode* tail=head;
    struct doublyNode* p=head->next;
    while (p!=NULL){
        if(p->data==data){
            tail->next=p->next;
            free(p);
            return head;
        }
        tail=p;
        p=p->next;
    }
}

void printlist(struct doublyNode* head){
    if(head==NULL){
        cout<<"链表没有数据"<<endl;
    }
    struct doublyNode* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

int main() {
    struct doublyNode* head=NULL;
    head=inserthead(head,10);
    head=inserthead(head,20);
    head=insertlast(head,20);
    head=insertlast(head,10);
    head=del(head,10);
    printlist(head);
    system("pause");
    return 0;
}