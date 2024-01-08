#include <iostream>

using namespace std;

struct binarysearch{
    int data;
    binarysearch* left;
    binarysearch* right;
};

binarysearch* createNode(int data){
    auto p=new binarysearch;
    p->data=data;
    p->right=NULL;
    p->left=NULL;
    return p;
}


//插入节点
binarysearch* insert(binarysearch* &root,int data){
    if (NULL==root){
        binarysearch* add= createNode(data);
        root=add;
    }else if(data<root->data){
        root->left= insert(root->left,data);
    }else if(data>root->data){
        root->right= insert(root->right,data);
    }
    return root;
}


//查找,直接判断大小然后递归分树查找(小就左子树，大就右子树，不然就是中间的树根节点)
binarysearch* Search(binarysearch* root,int data){
    if(NULL==root){
        return NULL;
    }
    if(data<root->data){
        return Search(root->left,data);
    } else if(data>root->data){
        return Search(root->right,data);
    }else{
        return root;
    }
}


//查找树的最小值,二叉查找树只需顺着左子树一路到最左就是最小
int findmin(binarysearch* root){
//    递归形式
    if(NULL==root){
        return root->data;
    }
    if(root->left==NULL){
        return root->data;
    }else{
        return findmin(root->left);
    }

    //非递归形式
//    if(NULL!=root){
//        while (root->left!=NULL){
//            root=root->left;
//        }
//    }else{
//        return NULL;
//    }
//    return root->data;
}

//查找树的最大值，二叉查找树只需顺着右子树一路到最右就是最大
int findmax(binarysearch* root){
    //递归形式
//    if(NULL==root){
//        return NULL;
//    }
//    if(root->right==NULL){
//        return root->data;
//    }else{
//        return findmax(root->right);
//    }

    //非递归形式
    if(NULL!=root){
        while (root->right!=NULL){
            root=root->right;
        }
    }else{
        cout<<"树没有数据"<<endl;
    }
    return root->data;
}


//遍历(使用中序遍历)
void inorderprint(binarysearch* root){
    if(NULL == root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<" ";
    inorderprint(root->right);
}

//删除节点，如果只有一个节点就分析是左子树还是右子树，然后将子树代替该根节点
//如果既有左节点(子树)和右节点(子树)，就找到右子树的最小值节点代替该根节点！
binarysearch* del(binarysearch* &root,int data){
    if(NULL==root){
        return NULL;
    }else if(data<root->data){
        root->left= del(root->left,data);
    }else if(data>root->data){
        root->right=del(root->right,data);
    }else if(root->left&&root->right){     //找寻右子树的最小值节点，删除最小值节点只有两种情况就是只有右子树(节点)或者没有节点。
        int temp= findmin(root->right);
        root->data=temp;
        root->right=del(root->right,temp);
    }else{   //只有一个子节点或者没有子节点的情况
        binarysearch* p=root;
        if(NULL==root->left){
            root=root->right;
        }else if(NULL==root->right){
            root=root->left;
        }
        delete p;
    }
    return root;
}


//清空树
binarysearch* destroy(binarysearch* &root){
    if(NULL!=root){
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
    return NULL;
}

int main() {
    binarysearch* root=NULL;
    insert(root,7);
    insert(root,4);
    insert(root,8);
    insert(root,5);
    insert(root,2);
    insert(root,3);
    insert(root,1);
    inorderprint(root);
//    destroy(root);
//    inorderprint(root);
    system("pause");
    return 0;
}
