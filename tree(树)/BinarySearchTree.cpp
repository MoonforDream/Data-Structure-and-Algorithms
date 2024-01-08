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


//����ڵ�
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


//����,ֱ���жϴ�СȻ��ݹ��������(С�����������������������Ȼ�����м�������ڵ�)
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


//����������Сֵ,���������ֻ��˳��������һ·�����������С
int findmin(binarysearch* root){
//    �ݹ���ʽ
    if(NULL==root){
        return root->data;
    }
    if(root->left==NULL){
        return root->data;
    }else{
        return findmin(root->left);
    }

    //�ǵݹ���ʽ
//    if(NULL!=root){
//        while (root->left!=NULL){
//            root=root->left;
//        }
//    }else{
//        return NULL;
//    }
//    return root->data;
}

//�����������ֵ�����������ֻ��˳��������һ·�����Ҿ������
int findmax(binarysearch* root){
    //�ݹ���ʽ
//    if(NULL==root){
//        return NULL;
//    }
//    if(root->right==NULL){
//        return root->data;
//    }else{
//        return findmax(root->right);
//    }

    //�ǵݹ���ʽ
    if(NULL!=root){
        while (root->right!=NULL){
            root=root->right;
        }
    }else{
        cout<<"��û������"<<endl;
    }
    return root->data;
}


//����(ʹ���������)
void inorderprint(binarysearch* root){
    if(NULL == root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<" ";
    inorderprint(root->right);
}

//ɾ���ڵ㣬���ֻ��һ���ڵ�ͷ�����������������������Ȼ����������ø��ڵ�
//���������ڵ�(����)���ҽڵ�(����)�����ҵ�����������Сֵ�ڵ����ø��ڵ㣡
binarysearch* del(binarysearch* &root,int data){
    if(NULL==root){
        return NULL;
    }else if(data<root->data){
        root->left= del(root->left,data);
    }else if(data>root->data){
        root->right=del(root->right,data);
    }else if(root->left&&root->right){     //��Ѱ����������Сֵ�ڵ㣬ɾ����Сֵ�ڵ�ֻ�������������ֻ��������(�ڵ�)����û�нڵ㡣
        int temp= findmin(root->right);
        root->data=temp;
        root->right=del(root->right,temp);
    }else{   //ֻ��һ���ӽڵ����û���ӽڵ�����
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


//�����
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
