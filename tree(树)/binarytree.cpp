#include <iostream>

using namespace std;

//������,��leftָ���������ڵ㣬��rightָ���������ڵ�
struct binarytree{
    int data;
    binarytree* left;
    binarytree* right;
};

binarytree* createNode(int data){
    auto p=new binarytree;
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}

//����ڵ�
void addchild(binarytree* &root,int data){
    binarytree* add= createNode(data);
    if(NULL == root) {
        root = add;
    }else{
        if(NULL == root->left){
            root->left=add;
        }else if(NULL==root->right){
            root->right=add;
        }else{
            cout<<"�ø��ڵ���ӽڵ�������"<<endl;
        }
    }
}


//�������
binarytree* preorderSearch(binarytree* root,int data){
    if(NULL == root){
        return NULL;
    }
    if(root->data==data){
        return root;
    }
    binarytree* res;
    res=preorderSearch(root->left,data);
    if(NULL!=res){
        return res;
    }
    res=preorderSearch(root->right,data);
    if(NULL!=res){
        return res;
    }
    return NULL;
}

//�������
binarytree* inorderSearch(binarytree* root,int data){
    if(NULL == root){
        return NULL;
    }
    binarytree* res;
    res=inorderSearch(root->left,data);
    if(NULL!=res){
        return res;
    }
    if(root->data==data){
        return root;
    }
    res=inorderSearch(root->right,data);
    if(NULL!=res){
        return res;
    }
    return NULL;
}

//�������
binarytree* postorderSearch(binarytree* root,int data){
    if(NULL==root){
        return NULL;
    }
    binarytree* res;
    res= postorderSearch(root->left,data);
    if(NULL!=res){
        return res;
    }
    res= postorderSearch(root->right,data);
    if (NULL!=res){
        return res;
    }
    if(root->data==data){
        return root;
    }
    return NULL;
}

//�����
void destroy(binarytree* &root){
    if(NULL==root){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

//ɾ���ڵ�
void del(binarytree* &root,int data){
    if(NULL == root){
        return;
    }
    binarytree* p=root;
    binarytree* tail=root->left;
    while (tail!=NULL){
        if(tail->data==data){
            if(NULL!=p->right){
                p->left=p->right;
                p->right=NULL;
                delete tail;
                return;
            }else{
                delete tail;
                p->left=NULL;
                return;
            }
        }
        del(tail,data);
        binarytree* temp=p;
        p=tail;
        tail=temp->right;
    }
    return;
}

//�������
void preorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    cout<<root->data<<" ";
    preorderprint(root->left);
    preorderprint(root->right);
}

//�������
void inorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<' ';
    inorderprint(root->right);
}

//�������
void postorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    postorderprint(root->left);
    postorderprint(root->right);
    cout<<root->data<<' ';
}

int main() {
    binarytree* root=NULL;
    addchild(root,10);
    addchild(root,20);
    addchild(root,30);
    addchild(root,10);
    binarytree* p=postorderSearch(root,30);
    addchild(p,100);
    del(root,20);
    preorderprint(root);
    system("pause");
    return 0;
}
