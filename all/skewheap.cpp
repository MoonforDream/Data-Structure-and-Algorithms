#include <iostream>
using namespace std;

struct heapNode{
    int data;
    heapNode* left;
    heapNode* right;
};

class skewheap{
public:
    skewheap(){
        root=new heapNode;
        root->data=INT_MAX;
        root->left= nullptr;
        root->right= nullptr;
    }
    heapNode* createNode(int data){
        auto p=new heapNode;
        p->data= data;
        p->left= nullptr;
        p->right= nullptr;
        return p;
    }
    heapNode* merge(heapNode* h1,heapNode* h2){
        if(h1->left== nullptr){
            h1->left=h2;
        }else{
            h1->right= findmerge_node(h1->right,h2);
            heapNode* p=h1->left;
            h1->left=h1->right;
            h1->right=p;
        }
        return h1;
    }
    heapNode* findmerge_node(heapNode* h1,heapNode* h2){
        if(nullptr==h1){
            return h2;
        }
        if(nullptr==h2){
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
        }else
            root=findmerge_node(root,add);
    }
    void delmin(){
        if(nullptr==root){
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
    skewheap h;
    h.insert(3);
    h.insert(10);
    h.insert(8);
    h.insert(17);
    h.insert(21);
    h.insert(14);
    h.insert(23);
    h.insert(26);
    h.delmin();
    h.print();
    system("pause");
    return 0;
}
