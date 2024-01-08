#include <iostream>

using namespace std;

//平衡查找树是其每个节点的左子树和右子树的高度最多差1的二叉查找树
struct AVL{
    int data;
    AVL* left;
    AVL* right;
    int height;  //节点高度
};

AVL* createNode(int data){
    auto p=new AVL;
    p->data=data;
    p->right= nullptr;
    p->left= nullptr;
    p->height=0;
    return p;
}

//防止出现空的高度
int Height(AVL* root){
    if(root== nullptr){
        return -1;
    }else{
        return root->height;
    }
}

//左左情况单旋转函数
AVL* SingleRotatewithLeft(AVL* &k1){
    AVL* k2;
    k2=k1->left;
    k1->left=k2->right;
    k2->right=k1;
    k1->height= max(Height(k1->left), Height(k1->right))+1;
    k2->height= max(Height(k2->left), Height(k2->right))+1;
    return k2;
}

//右右情况单旋转函数
AVL* SingleRotatewithRight(AVL* &k1){
    AVL* k2;
    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;
    k1->height= max(Height(k1->left), Height(k1->right))+1;
    k2->height= max(Height(k2->left), Height(k2->right))+1;
    return k2;
}

//左右情况双旋转
AVL* DoubleRotatewithLeft(AVL* &k1){
    //非递归形式
//    AVL* k2;
//    AVL* k3;
//    k2=k1->left;
//    k3=k1->left->right;
//    k1->left=k3->right;
//    k2->right=k3->left;
//    k3->left=k2;
//    k3->right=k1;
//    k1->height=max(Height(k1->left), Height(k1->right))+1;
//    k2->height=max(Height(k2->left), Height(k2->right))+1;
//    k3->height=max(Height(k3->left), Height(k3->right))+1;
//    return k3;
    //递归形式，建议用递归，好记
    k1->left= SingleRotatewithRight(k1->left);   //k2跟k3单旋转
    return SingleRotatewithLeft(k1);       //k1跟现在的k2(原来的k3)单旋转
}

//右左情况双旋转
AVL* DoubleRotatewithRight(AVL* &k1){
    //非递归形式
//    AVL* k2;
//    AVL* k3;
//    k2=k1->right;
//    k3=k1->right->left;
//    k1->right=k3->left;
//    k2->left=k3->right;
//    k3->left=k1;
//    k3->right=k2;
//    k1->height=max(Height(k1->left), Height(k1->right))+1;
//    k2->height=max(Height(k2->left), Height(k2->right))+1;
//    k3->height=max(Height(k3->left), Height(k3->right))+1;
//    return k3;
    //递归形式
    k1->right= SingleRotatewithLeft(k1->right);       //k2跟k3单旋转
    return SingleRotatewithRight(k1);           //k1跟现在的k2(原来的k3)单旋转
}


//插入
AVL* insert(AVL* &root,int data){
    if(NULL==root){
        AVL* add= createNode(data);
        root=add;
    }else if(data<root->data){
        root->left= insert(root->left,data);
        //判断高度差
        if(2== Height(root->left)- Height(root->right)){
            //左左情况，情形1,单旋转
            if(data<root->left->data){
                root=SingleRotatewithLeft(root);
            }else{   //左右情况，情形2，双旋转
                root=DoubleRotatewithLeft(root);
            }
        }
    }else if(data>root->data){
        root->right= insert(root->right,data);
        if(2== Height(root->right)- Height(root->left)){
            //右右情况，情形4，单旋转
            if(data>root->right->data){
                root=SingleRotatewithRight(root);
            }else{    //右左情况,情形3，双旋转
                root=DoubleRotatewithRight(root);
            }
        }
    }
    //通过递归，从后序开始往上回，这样就能保证树的高度的正确性,这样子到了根节点就拿到了最大的高度
    root->height= max(Height(root->left), Height(root->right))+1;
    return root;
}


//查找
AVL* Search(AVL* root,int data){
    if(NULL==root){
        return NULL;
    }
    if(data<root->data){
        root->left= Search(root->left,data);
    }else if(data>root->data){
        root->right= Search(root->right,data);
    }else
        return root;
}


//查找最小值
int findmin(AVL* root){
    //递归形式
    if(NULL==root){
        return root->data;
    }
    if(root->left!=NULL){
        return findmin(root->left);
    }else{
        return root->data;
    }

    //非递归形式
//    if(NULL!=root){
//        while (root->left!=NULL){
//            root=root->left;
//        }
//        return root->data
//    }
//    return NULL;
}

//查找最大值
int findmax(AVL* root){
    //递归形式
//    if(NULL==root){
//        return NULL;
//    }
//    if(NULL!=root->right){
//        return findmax(root->right);
//    }else{
//        return root->data;
//    }

    //非递归形式
    if(NULL!=root){
        while (root->right!=NULL){
            root=root->right;
        }
    }
    return root->data;
}


//删除节点，删除操作也会导致AVL树平衡破坏，所以删除操作也需要对AVL树做判断
AVL* del(AVL* &root,int data){
    if(NULL==root){
        return NULL;
    }else if(data<root->data){
        root->left= del(root->left,data);
        if(2== Height(root->left)- Height(root->right)){
            if(data<root->left->data){
                root= SingleRotatewithLeft(root);
            }else{
                root= DoubleRotatewithLeft(root);
            }
        }
    }else if(data>root->data){
        root->right=del(root->right,data);
        if(2== Height(root->right)- Height(root->left)){
            if(data>root->right->data){
                root= SingleRotatewithRight(root);
            }else{
                root= DoubleRotatewithRight(root);
            }
        }
    }else if(root->left&&root->right){
        int temp= findmin(root);
        root->data=temp;
        root->right=del(root->right,temp);
    }else{
        AVL* p=root;
        if(NULL==root->left){
            root=root->right;
        }else if(NULL==root->right){
            root=root->left;
        }
        delete p;
    }
    if(root!=NULL)
        root->height=max(Height(root->left), Height(root->right))+1;
    return root;
}


//清空树
void destroy(AVL* &root){
    if(NULL==root){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

//打印，中序遍历
void inorderprint(AVL* root){
    if(NULL==root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<" ";
    inorderprint(root->right);
}

int main() {
    AVL* root=NULL;
    insert(root,4);
    insert(root,3);
    insert(root,7);
    insert(root,8);
    insert(root,6);
    insert(root,5);
//    del(root,5);
//    destroy(root);
    inorderprint(root);
    system("pause");
    return 0;
}
