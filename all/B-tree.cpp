#include <iostream>
#include <vector>
using namespace std;

struct btree{
    int level;  //树的阶数
    vector<int>keys;  //关键字数组
    vector<btree*>child; //子节点数组
    int keynum;   //节点的关键字数目
    btree* parent;    //子节点的父节点
};

btree* createNode(int level){
    auto p=new btree;
    p->level=level;
    p->keynum=0;
    p->parent= nullptr;
    for(int i=0;i<=p->level;i++){
        p->child.push_back(nullptr);
        p->keys.push_back(0);
    }
    return p;
}

pair<btree*,int> find(btree* root,int key){
    int i;
    for(i=root->keynum;i>0;i--){
        if(key<root->keys[i]){
            continue;
        }else if(key>root->keys[i]){
            break;
        }else{
            return make_pair(root,i);
        }
    }
    pair<btree*,int>p=find(root->child[i],key);
    return p;
}


void splitNode(btree* &root,btree* p,int index){
    if(p != nullptr && p->keynum == p->level) {
        //分裂节点
        int mid=p->keynum/2+p->keynum%2;
        btree* newnode= createNode(p->level);
        newnode->parent=p->parent;
        for(int j=root->keynum;j>index-1;j--){
            root->keys[j+1]=root->keys[j];
        }
        root->keys[index]=p->keys[mid];
        root->keynum++;
        for(int j=mid+1;j<=p->keynum;j++){
            newnode->keys[j-mid]=p->keys[j];
            newnode->keynum++;
        }
        p->keynum=p->keynum-newnode->keynum-1;
        int k;
        for(k=root->level-1;k>index-1;k--){
            root->child[k+1]=root->child[k];
        }
        k++;
        root->child[k]=newnode;
    }
    if(root->keynum==root->level) {
        btree *newchild = createNode(root->level);
        int mid = root->keynum / 2 + root->keynum % 2;
        for (int i = mid + 1; i <= root->level; i++) {
            newchild->keys[i - mid] = root->keys[i];
            newchild->keynum++;
        }
        for (int j = newchild->keynum; j <= newchild->level; j++) {
            if(root->child[j])
                root->child[j]->parent=newchild;
            newchild->child[j - newchild->keynum] = root->child[j];
            root->child[j] = nullptr;
        }
        if (root->parent == nullptr) {
            btree *newnode = createNode(root->level);
            newnode->keys[1] = root->keys[mid];
            newnode->keynum++;
            root->keynum = root->level - newchild->keynum - 1;
            newnode->child[0] = root;
            newnode->child[1] = newchild;
            root->parent = newnode;
            newchild->parent = newnode;
            root = newnode;
        } else {
            newchild->parent = root->parent;
            root->keynum = root->level - newchild->keynum - 1;
            int a = root->parent->keynum;
            while (a > 0 && root->keys[mid] < root->parent->keys[a]) {
                root->parent->keys[a + 1] = root->parent->keys[a];
                root->parent->child[a + 1] = root->parent->child[a];
                a--;
            }
            a++;
            root->parent->keys[a] = root->keys[mid];
            root->parent->keynum++;
            root->parent->child[a] = newchild;
        }
    }
}

btree* insert(btree* &root,int key){
    if(0==root->keynum){
        root->keys[1]=key;
        root->keynum++;
        return root;
    }
    int index=root->keynum;
    while (index>0&&key<root->keys[index]){
        root->keys[index+1]=root->keys[index];
        index--;
    }
    index++;
    if(root->child[0]!=nullptr){
        btree* p;
        if(index==root->keynum){
            p=root->child[index+1];
        }else{
            p=root->child[index-1];
        }
        if(root->child[0]->child[0]!=nullptr){
            p= insert(p,key);
        }else if(root->child[0]->child[0]==nullptr){
            int i=p->keynum;
            while (i>0&&key<p->keys[i]){
                p->keys[i+1]=p->keys[i];
                i--;
            }
            i++;
            p->keys[i]=key;
            p->keynum++;
        }
        splitNode(root,p,index);
    }else{
        root->keys[index]=key;
        root->keynum++;
        splitNode(root, nullptr,-1);
    }
    return root;
}

int findmax(btree* root){
    if(nullptr==root){
        return 0;
    }else if(root->child[0]!= nullptr){
        return findmax(root->child[root->keynum]);
    }
    return root->keys[root->keynum];
}


void merge(btree* &root,int key,int min,int n){
    int n1 = root->child[n-1]->keynum;
    int n2 = root->child[n]->keynum;
    if (n1 > min) {
        for (int j = n2; j > 0; j--) {
            root->child[n]->keys[j + 1] = root->child[n]->keys[j];
            root->child[n]->child[j + 1] = root->child[n]->child[j];
        }
        root->child[n]->child[1] = root->child[n]->child[0];
        root->child[n]->keys[1] = root->keys[n];
        root->keys[n]=root->child[n-1]->keys[n1];
        root->child[n]->child[0] = root->child[n-1]->child[n1];
        root->child[n-1]->child[n1] = nullptr;
        root->child[n-1]->child[0]->parent = root->child[n-1];
        root->child[n-1]->keynum--;
        root->child[n-1]->keys[n1] = NULL;
        root->child[n]->keynum++;
    } else if (n2 > min) {
        root->child[n-1]->keys[n1+1]=root->keys[n];
        root->keys[n]=root->child[n]->keys[1];
        root->child[n-1]->child[n1 + 1] = root->child[n]->child[0];
        root->child[n-1]->child[n1 + 1]->parent = root->child[n-1];
        root->child[n-1]->keynum++;
        for (int j = 1; j < n2; j++) {
            root->child[n]->keys[j] = root->child[n]->keys[j + 1];
            root->child[n]->child[j - 1] = root->child[n]->child[j];
        }
        root->child[n]->child[n2-1]=root->child[n]->child[n2];
        root->child[n]->keys[n2] = NULL;
        root->child[n]->child[n2] = nullptr;
        root->child[n]->keynum--;
    } else {
        root->child[n-1]->keys[n1+1]=root->keys[n];
        root->child[n-1]->keynum++;
        int n3 = n2 + n1+1;
        for (int j = n1 + 2; j <= n3; j++) {
            root->child[n-1]->keys[j] = root->child[n]->keys[j - n1-1];
            root->child[n-1]->child[j-1]=root->child[n]->child[j];
            root->child[n-1]->keynum++;
        }
        root->child[n]=nullptr;
        int index = root->keynum;
        while (index > n && key < root->keys[index]) {
            root->keys[index-1]=root->keys[index];
            root->child[index-1]=root->child[index];
            index--;
        }
        root->child[root->keynum]= nullptr;
        root->keynum--;
        if(root->parent== nullptr&&root->keynum==0){
            root->child[0]->parent= nullptr;
            root=root->child[0];
        }
    }
}

void del(btree* &root,int key){
    if(nullptr==root){
        return;
    }else{
        int i;
        for(i=root->keynum;i>0;i--){
            if(key<root->keys[i]){
                continue;
            }else if(key>root->keys[i]){
                del(root->child[i],key);
            }else{
                break;
            }
        }
        int min=(root->level/2+root->level%2)-1;
        if(0==i){
            if(root->child[i]&&root->child[i+1]){
                if(root->child[i]->keynum>=min&&root->child[i+1]->keynum>=min){
                    del(root->child[i],key);
                }
            }
            i++;
        }
        if(root->child[0]!= nullptr){
            if(root->keynum>=min){
                if(root->keys[i]==key){
                    int temp= findmax(root->child[i-1]);
                    root->keys[i]=temp;
                    del(root->child[i-1],temp);
                    merge(root,key,min,i);
                }else if(key<root->keys[i]){
                    if(root->child[i-1]->keynum<min){
                        merge(root,key,min,i);
                    }
                }else{
                    if(root->child[i]->keynum<min){
                        merge(root,key,min,i);
                    }
                }
            }else{
                merge(root,key,min,i);
            }
        }else{
            int j;
            for(j=1;j<root->keynum;j++){
                if(root->keys[j]==key){
                    break;
                }
            }
            for(int d=j;d<root->keynum;d++){
                root->keys[d]=root->keys[d+1];
            }
            root->keys[root->keynum]=NULL;
            if(root->keynum>min){
                root->keynum--;
            }else{
                root->keynum--;
                int index=root->parent->keynum;
                for(int k=root->keynum;k>0;k--){
                    root->keys[k+1]=root->keys[k];
                }
                while (index>0&&key<=root->parent->keys[index]){
                    index--;
                }
                if(0==index){
                    root->keys[root->keynum+1]=root->parent->keys[1];
                }else{
                    root->keys[root->keynum+1]=root->parent->keys[index];
                }
            }
        }
    }
}

//中序遍历
void inorderprint(btree* root){
    if(nullptr!=root){
        int i;
        for(i=0;i<root->keynum;i++){
            if(root->child[i]!= nullptr){
                inorderprint(root->child[i]);
            }
            cout<<root->keys[i+1]<<" ";
        }
        if(root->child[i]!= nullptr)
            inorderprint(root->child[i]);
    }
}


int main(){
    btree* root= createNode(4);
    insert(root,1);
    insert(root,2);
    insert(root,3);
    insert(root,4);
    insert(root,10);
    insert(root,15);
    insert(root,23);
    insert(root,28);
    insert(root,30);
    insert(root,31);
    insert(root,32);
    insert(root,33);
    insert(root,34);
    insert(root,35);
    insert(root,36);
    insert(root,37);
    insert(root,38);
    insert(root,39);
    insert(root,40);
    insert(root,41);
    insert(root,42);
    insert(root,43);
    insert(root,44);
    del(root,31);
    inorderprint(root);
    system("pause");
    return 0;
}

