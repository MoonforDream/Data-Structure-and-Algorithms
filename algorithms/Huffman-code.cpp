#include <iostream>
#include <queue>
using namespace std;

struct tree{
    char data;
    tree* left;
    tree* right;
    int weight;
};

struct cmp{
    bool operator()(tree *a, const tree* b){
        return a->weight<b->weight;
    }
};

priority_queue<tree*,vector<tree*>,cmp>pq;


tree* createNode(char data,int weight){
    tree* p=new tree;
    p->data=data;
    p->left= nullptr;
    p->right= nullptr;
    p->weight=weight;
    return p;
}

tree* merge(tree* &t1,tree* &t2){
    int n=t1->weight+t2->weight;
    tree* p= createNode(0,n);
    p->left=t1;
    p->right=t2;
    return p;
}

tree* Huffman(){
    tree* p;
    while (!pq.empty()){
        tree* t1=pq.top();
        pq.pop();
        tree* t2=pq.top();
        pq.pop();
        p=merge(t1,t2);
        pq.push(p);
    }
    return p;
}

int main() {
    for(int i=0;i<10;i++){
        char data=char('a'+i);
        tree* p= createNode(data,i+5);
        pq.push(p);
    }
    tree* p=Huffman();
    system("pause");
    return 0;
}
