#include <iostream>
using namespace std;

struct heapNode{
    int data;    //数据
    heapNode* left;    //左子节点指针
    heapNode* right;   //右子节点指针
    int Npl;     //零路径长
};

class leftheap{
public:
    leftheap(){
        root=new heapNode;
        root->left= nullptr;
        root->right= nullptr;
        root->data=INT_MAX;
        root->Npl=0;
    }
    heapNode* createNode(int data){
        auto p=new heapNode;
        p->data=data;
        p->left= nullptr;
        p->right= nullptr;
        p->Npl=0;
        return p;
    }
    heapNode* merge(heapNode* h1,heapNode* h2){
        if(h1->left== nullptr){
            h1->left=h2;
        }else{
            h1->right= findmerge_node(h1->right,h2);
            if(h1->left->Npl<h1->right->Npl){
                heapNode* p=h1->left;
                h1->left=h1->right;
                h1->right=p;
            }
            h1->Npl=h1->right->Npl+1;
        }
        return h1;
    }
    heapNode* findmerge_node(heapNode* h1,heapNode* h2){
        if(nullptr==h1){
            return h2;
        }else if(nullptr==h2){
            return h1;
        }
        if(h1->data<h2->data){
            return merge(h1,h2);
        }else{
            return merge(h2,h1);
        }
    }
    void insert(int data){
        heapNode* add= createNode(data);
        if(root->data==INT_MAX){
            root=add;
        } else
            root=findmerge_node(root,add);
    }
    void delmin(){
        if(root== nullptr){
            return;
        }
        heapNode* h1=root->left;
        heapNode* h2=root->right;
        delete root;
        root= findmerge_node(h1,h2);
    }
    int getmin(){
        return root->data;
    }
    heapNode* print(heapNode* p){
        if(p!= nullptr){
            cout<<p->data<<" ";
            print(p->left);
            print(p->right);
        }
        return p;
    }
    void print(){
        if(root== nullptr){
            return;
        }
        print(root);
    }
private:
    heapNode* root;
};

int main() {
    leftheap h;
    h.insert(3);
    h.insert(10);
    h.insert(8);
    h.insert(17);
    h.insert(21);
    h.insert(14);
    h.insert(23);
    h.insert(26);
    h.delmin();
    cout<<h.getmin()<<endl;
    h.print();
    system("pause");
    return 0;
}
