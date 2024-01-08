#include <iostream>
using namespace std;

//通过链表的形式，表头就是根节点，通过找到第一个子节点，就能找到其他的子节点。
struct treeNode{
    int data;
    treeNode* firstchild;    //用于指向该节点的第一个子节点
    treeNode* nextsibling;   //用于指向该节点的下一个兄弟节点
};

treeNode* createNode(int data){
    auto p=new treeNode;
    p->data=data;
    p->firstchild=NULL;
    p->nextsibling=NULL;
    return p;
}

//插入节点
void addChild(treeNode* &root,int data){
    treeNode* add=createNode(data);
    if(root==NULL){
        root=add;
    }else{
        if(root->firstchild==NULL){
            root->firstchild=add;
        }else{
            treeNode* p=root->firstchild;
            while(p->nextsibling!=NULL){
                p=p->nextsibling;
            }
            p->nextsibling=add;
        }
    }
}

//先序查找
treeNode* preorderSearch(treeNode* root,int data){
    if(root==NULL){
        return NULL;
    }
    if(root->data==data){
        return root;
    }
    treeNode* res;
    res=preorderSearch(root->firstchild,data);
    if(res!=NULL){
        return res;
    }
    res=preorderSearch(root->nextsibling,data);
    if(res!=NULL){
        return res;
    }
    return NULL;
}

//后序查找
treeNode* postorderSearch(treeNode* root,int data){
    if(root==NULL){
        return NULL;
    }
    treeNode* res;
    res=postorderSearch(root->firstchild,data);
    if(res!=NULL){
        return res;
    }
    res=postorderSearch(root->nextsibling,data);
    if(res!=NULL){
        return res;
    }
    if(root->data==data){
        return root;
    }
    return NULL;
}

//删除节点
void del(treeNode* &root,int data){
    if(root==NULL){
        return;
    }
    treeNode* p=NULL;
    treeNode* tail=root->firstchild;
    while(tail!=NULL){
        if(tail->data==data){
            if(p==NULL){
                root->firstchild=tail->nextsibling;
            }else{
                p->nextsibling=tail->nextsibling;
            }
            delete tail;
            return;
        }
        del(tail,data);
        p=tail;
        tail=tail->nextsibling;
    }
    return;
}

//先序遍历
void preorderprint(treeNode *root){
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    preorderprint(root->firstchild);
    preorderprint(root->nextsibling);
}


//后序遍历
void postorderprint(treeNode* root){
    if(root==NULL){
        return;
    }
    postorderprint(root->firstchild);
    postorderprint(root->nextsibling);
    cout<<root->data<<" ";
}


//清空树
void destroy(treeNode* root){
    if(root==NULL){
        return;
    }
    destroy(root->firstchild);
    destroy(root->nextsibling);
    delete root;
}



int main() {
    treeNode* root=NULL;
    addChild(root,10);
    addChild(root,20);
    addChild(root,30);
    treeNode*p= preorderSearch(root,30);
    addChild(p,100);
    preorderprint(root);
    cout<<endl;
    postorderprint(root);
    del(root,100);
    preorderprint(root);
//    destroy(root);
//    preorderprint(root);
    system("pause");
    return 0;
}
