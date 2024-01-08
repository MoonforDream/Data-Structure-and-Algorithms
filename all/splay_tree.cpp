#include <iostream>

using namespace std;

struct splay{
    int data;
    splay* left;
    splay* right;
};

splay* createNode(int data){
    auto p=new splay;
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}

splay* SingleRotatewithLeft(splay* &k1){
    splay* k2;
    k2=k1->left;
    k1->left=k2->right;
    k2->right=k1;
    return k2;
}

splay* SingleRotatewithRight(splay* &k1){
    splay* k2;
    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;
    return k2;
}

splay* DoubleRotatewithLeft(splay* &k1){
    k1->left= SingleRotatewithRight(k1->left);
    return SingleRotatewithLeft(k1);
}

splay* DoubleRotatewithRight(splay* &k1){
    k1->right= SingleRotatewithLeft(k1->right);
    return SingleRotatewithRight(k1);
}

//插入
splay* insert(splay* &root,int data){
    if(NULL==root){
        splay* add= createNode(data);
        root=add;
    }else if(data<root->data){
        root->left= insert(root->left,data);
    }else if(data>root->data){
        root->right= insert(root->right,data);
    }
    return root;
}

//查找
//因为查找data很有可能是相等的，所以要分开这种情况，如果root的下一个是要找的我们就往上返，令节点差为2个保证了判断路径结构的正确性
splay* search(splay* &root,int data){
    if(NULL==root||root->data==data){
        return root;
    }else if(data<root->data){
        root->left= search(root->left,data);
        if(data<root->left->data){
            root= SingleRotatewithLeft(root);
        }else if(data>root->left->data){
            root= DoubleRotatewithLeft(root);
        }
    }else if(data>root->data){
        root->right= search(root->right,data);
        if(data>root->right->data){
            root= SingleRotatewithRight(root);
        }else if(data<root->right->data){
            root= DoubleRotatewithRight(root);
        }
    }
    return root;
}

//查找最小值
int findmin(splay* root){
    if(NULL==root){
        return root->data;
    }
    if (root->left!=NULL){
        return findmin(root->left);
    }else{
        return root->data;
    }
}

//查找最大值
int findmax(splay* root){
    if(NULL==root){
        return root->data;
    }
    if(root->right!=NULL){
        return findmax(root->right);
    }else{
        return root->data;
    }
}

//删除树节点
void del(splay* &root,int data){
    search(root,data);
    if(NULL==root){
        return;
    }else{
        splay* t1=root->left;
        splay* t2=root->right;
        root->left=NULL;
        root->right=NULL;
        delete root;
        int temp= findmax(t1);
        t1= search(t1,temp);
        t1->right=t2;
        root=t1;
    }
}

void inorderprint(splay* root){
    if(NULL==root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<" ";
    inorderprint(root->right);
}

//清空树
void destroy(splay* &root){
    if(NULL==root){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    splay* root=NULL;
    insert(root,10);
    insert(root,3);
    insert(root,5);
    insert(root,6);
    insert(root,2);
    insert(root,8);
    search(root,8);
//    del(root,8);
    inorderprint(root);
    system("pause");
    return 0;
}
