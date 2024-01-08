# 树

## 普通树(多叉树)

**概念**：

- **树**就是由**根节点(父亲)**分出多个**分支节点(儿子)**，然后分支又分出多个分支，我们将这种结构称为树,树也可以这么定义：一棵树由称作**根的节点r以及0个或多个非空的(子)树T1，T2，T3...Tk组成**，这些子树每一棵的根都被来自**根r的一条有向的边所连接**。
- **从递归定义中我们发现**，一颗树是**N个节点**和**N-1条边**的集合，其中的一个节点叫做**根**。每条边都将某个节点连接到它的父亲，而除去根接待你外每一个节点都有一个父亲。**没有子节点的节点叫做树叶(叶节点)**，**具有相同父节点称为兄弟节点**。**节点深度**就是该节点到根节点的长度是多少，**节点高度**就是该节点到最近叶节点的长度。



![image-20230707221904048](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230707221904048.png)







**代码**:

```c++
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
        return NULL;
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
    return NULL;
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
```







## 树的遍历

树有很多应用。流行的用法之一是包括UNIX、VAX/VMS和DOS在内的许多常用操作中的目录结构。



**核心思想**：

- 树的遍历的核心是**递归**
- 树的遍历的核心思想还有**遍历的方式**(先序遍历，后序遍历....)



**先序遍历**：

- 先从根节点，处理完根节点，再去处理子树
- 先处理子树的根节点，才处理子节点
- **先序遍历总是处理根节点，再处理子节点**



**后序遍历**：

- 先处理子树的子节点，再处理子树的根节点
- 把全部小子树处理完，就处理树的根节点
- **后序遍历总是先处理子节点，再处理根节点**







## 二叉树

**概念**：

- **二叉树(binary tree)**是一颗**每个节点都不能多于两个子节点**的树，左边的子树称为左子树，右边的子树称为右子树



**性质**：

- 二叉树实际上是图，二叉树相对于树更常用。

- 平衡二叉树的深度要比节点数小很多，平均深度为**O(n<sup>1/2</sup>)**
- 对于特殊类型的二叉树，即**二叉查找树(binary search tree)**，平均深度为**O(logN)**，最坏情况的二叉树深度能达到N-1。

![image-20230707230357034](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230707230357034.png)







**先序遍历**：

- **先处理根节点，再处理左子树，最后处理右子树**
- 处理左子树的时候，也是先处理左子树的根节点，再处理剩下的左子节点(或者子树)，最后处理右节点(子树)
- 处理右子树跟处理左子树的操作一样。



**中序遍历**：

- **先处理左子树，再处理根节点，最后处理右子树**
- 处理左子树时，也是先处理左子树的左子节点(子树),再处理左子树的根节点，最后处理左子树的右子节点(子树)
- 处理完左子树，处理根节点
- 处理完根节点，就处理右子树(跟处理左子树的操作一致)



**后序遍历**：

- **先处理左子树，再处理右子树，最后处理根节点**
- 处理左子树的时候，也是先处理左子树的左子节点(子树)，再处理左子树的右子节点(子树)，最后处理左子树的根节点。
- 处理完左子树，再处理右子树(跟处理左子树的操作一致)
- 处理完右子树，最后处理树的根节点





代码：

```c++
//二叉树,用left指向左子树节点，用right指向右子树节点
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

//插入节点
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
            cout<<"该根节点的子节点已满！"<<endl;
        }
    }
}


//先序查找
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

//中序查找
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

//后序查找
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

//清空树
void destroy(binarytree* &root){
    if(NULL==root){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

//删除节点
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

//先序遍历
void preorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    cout<<root->data<<" ";
    preorderprint(root->left);
    preorderprint(root->right);
}

//中序遍历
void inorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    inorderprint(root->left);
    cout<<root->data<<' ';
    inorderprint(root->right);
}

//后序遍历
void postorderprint(binarytree* root){
    if(NULL==root){
        return;
    }
    postorderprint(root->left);
    postorderprint(root->right);
    cout<<root->data<<' ';
}
```











## 二叉查找树(二叉排序树)

**概念**：

- 二叉树的一个重要应用是它们在查找中的使用---二叉查找树
- 二叉查找树**每个节点的值都不同**，以后再处理值相同的情况
- **对于二叉查找树的每个节点，它的左子树中所有关键字值小于该节点的关键字值，而它的右子树中所有的关键字值大于该节点的关键字值**
- 该数的所有元素可以用某种统一的方式排序----**二叉查找树有序**
- 二叉查找树的平均深度为*O(logN)*
- 二叉查找树应该用**中序遍历**方式遍历







代码:

```c++
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
```



















## 平衡查找树(AVL树)

**概念**：

- 为了防止因为插入删除而导致的**树结构不平衡**(通常我们删除节点总是对右子树的最小值节点替代操作，而不是交替的利用左子树的最大值节点替代，这就将导致左子树的平均深度大于右子树平均深度，直接导致整颗树平均深度的增加，导致对树节点的操作时间增长)，导致对树的操作所用时间成倍数增长的问题，我们采用**平衡二叉树---左右子树的平均深度差不多**，达到一种平衡的操作，平衡二叉树希望对树的任意节点的操作时间为*O(logN)*
- AVL(Adelson-Velskii和Landis)树是**带有平衡条件的二叉查找树**。这个平衡条件需要容易保持，而且需保证树的深度是O(logN)。
- 一颗AVL树是**其每个节点的左子树和右子树的高度最多差1的二叉查找树**，空树的高度定义为-1
- 在高度为h的AVL树中，最少节点数S(h)由S(h)=S(h-1)+S(h-2)+1算出。该h为该数最大高度。







**旋转**：

- 功能：对被破坏平衡的AVL树进行修正，**使得重新平衡**

- 对于我们**对树的插入操作**，**破坏AVL树的平衡**，我们则需要对树进行简单的修正来保持平衡，这个操作我们称其为**旋转**

- 我们把必须重新平衡的节点(**就是造成AVL树不平衡的插入点跟因此被打破平衡的另外一个节点(也就是插入点跟树中的一个节点高度差大于1)的共同根节点**)叫做α，由于任意节点最多有两个儿子，因此高度不平衡时，α点的两颗子树的高度差2，这种不平衡的情形有四种：

  > 1.对α的左儿子的左子树进行一次插入
  >
  > 2.对α的左儿子的右子树进行一次插入
  >
  > 3.对α的右儿子的左子树进行一次插入
  >
  > 4.对α的右儿子的右子树进行一次插入

- 对于1和4的情形称为**插入发生在"外边"的情况**(即**左-左**的情况或**右-右**的情况)，该情况需要通过对**树的一次单旋转**而完成调整

- 对于2和3的情形称为**插入发生在"内部"的情况**(即**左-右**的情况或**右-左**的情况)，这个情况需要通过对**树的双旋转**来处理







### **单旋转**

- 对于情形1(如图4-31)，我们需要将造成不平衡的插入点上移一层，另外那个跟它高度差为2的节点下移一层(**就是将α点跟其左节点进行单旋转**(*单旋转就是类似将左节点拎起来，其他的节点根据重量下坠，然后再根据二叉查找树的特性排序形成新的平衡二叉树*))，并形成一个新的平衡二叉查找树，具体操作就如图4-32，插入6会破坏AVL树的特性，因为6是插入点，而8没有子节点(这个空的子节点其实就是被破坏平衡的高度差为2的节点)，它们的共同根节点就为8，所以8为α点，我们需要将α点的左节点也就是7跟α点也就是8进行单旋转，然后形成新的平衡查找树

  具体操作为：

  > 1. 向α点的左儿子的左子树插入节点造成不平衡
  > 2. 将α点跟α点的左儿子做单旋转
  > 3. 原先α点的左儿子的左子树根节点成为现在α点(之前的α点的左儿子)的左儿子，原先的α点作为现在α点的右儿子，原先α点的左儿子的右子树根节点成为现在α点的右儿子的左子树根节点
  > 4. 重新形成一个新的AVL树

  ![image-20230712224654575](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230712224654575.png)

  ![image-20230712224427132](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230712224427132.png)

- 对于情形4(如图4-33)，其实情形4跟情形差不多的做法就是方向改变了，我们需要将造成不平衡的插入点上移一层，另外那个跟它高度差为2的节点下移一层(**就是将α点跟其右节点进行单旋转**(*单旋转就是类似将右节点拎起来，其他的节点根据重量下坠，然后再根据二叉查找树的特性排序形成新的平衡二叉树*))，并形成新的平衡二叉查找树

  具体操作为：

  >1. 向α点的右儿子的右子树插入节点造成不平衡
  >2. 对α点跟α点的右儿子进行单旋转
  >3. 原先的α点成为现在的α点(之前的α点的右儿子)的左儿子，原先的α点的右儿子的右子树根节点成为现在的α点的右儿子，原先α点的右儿子的左子树根节点成为了现在α点的左儿子的右子树根节点
  >4. 重新形成一颗新的AVL树

  ![image-20230712224758752](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230712224758752.png)












### 双旋转

- 对于情形2和3，单旋转无法修正被破坏的AVL树，对于图4-34子树Y太深，单旋转无法减低它的深度

  ![image-20230713164436865](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230713164436865.png)

- 对于情形2，例如图4-35(k1<k2<k3)，我们需要用到**双旋转**(*让α的左儿子的右子树根节点跟α的左儿子做一次单旋转，旋转完后，α的左儿子的右子树就是α的左儿子，原来α的左儿子变成了α的左儿子的右子树根节点，然后现在的α的左儿子(也就是原来的α的左儿子的右子树根节点)跟α点做一次单旋转*)，具体步骤就是

  > 1. 向α的左儿子的右子树插入节点
  > 2. 就双旋转后，让α的左儿子的右子树根节点(这里成为k2)旋转到α点(这里称为k3)的位置，α的左儿子(称为k1)成为k2的左儿子，k3成为k2的右儿子
  > 3. 如果插入的是左节点，就让它成为k1的右儿子，如果插入的是右节点就让它成为k3的左儿子。
  > 4. 然后就形成了新的AVL树

  ![image-20230713174303812](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230713174303812.png)

- 对于情形三(图4-36，k1<k2<k3)，跟情形二做法差不多只是方向改变了，我们需要用到**双旋转**(*让α的右儿子的左子树根节点跟α的右儿子做一次单旋转，旋转完后，α的右儿子的左子树就是α的右儿子，原来α的右儿子变成了α的右儿子的左子树根节点，然后现在的α的右儿子(也就是原来的α的右儿子的左子树根节点)跟α点做一次单旋转*)，具体步骤就是

  >1. 向α的右儿子的左子树插入节点
  >2. 就双旋转后，让α的右儿子的左子树根节点(这里成为k2)旋转到α点(这里称为k1)的位置，α的右儿子(称为k3)成为k2的右儿子，k1成为k2的左儿子
  >3. 如果插入的是左节点，就让它成为k1的右儿子，如果插入的是右节点就让它成为k3的左儿子。
  >4. 然后就形成了新的AVL树

  ![image-20230713175843996](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230713175843996.png)







**代码**:

```c++
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
    p->right=NULL;
    p->left=NULL;
    p->height=0;
    return p;
}

//防止出现空的高度
int Height(AVL* root){
    if(root==NULL){
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
```



















## 伸展树

**概念**：

- **伸展树**是一颗对**任意一个节点被访问**后，就经过**一系列的AVL树的旋转操作**将该**节点放到根上**的特殊**二叉查找树**。
- 伸展树能**保证对树操作M次的时间复杂度为O(MlogN)**，而当一个查找树的一个节点刚好处于查找树最坏的情形，我们每次访问都需要按照最坏情形的时间计算，这将耗费**O(M*N)**的时间，伸展树就是要**将访问的节点进行移动**，使它不一直存在一个地方，避免了多次操作最坏情形的出现，而伸展树访问的节点比较深，经过移动，对该节点的原先子树节点访问也会避免往更深处进行操作
- 伸展树不要求保留高度或平衡信息，因此能够节省空间以及简化代码





**查找操作**：

- 关于访问节点，然后对其进行一系列旋转操作，将该节点放到**根**上，我们需要对访问该节点的路径上(**从下到上**)**每一个节点都需要和它们的父节点**实施**单旋转**，直到将该节点推到根

- 但是如果只进行单旋转情况，并直接从下到上的话，则会浪费大部分时间

- 因此我们需要使用**展开**操作，而展开操作其实就是根据路径树的结构分情况进行操作

- **具体步骤**：

  > 1. 判断路径的结构，分为“**之字形**”和“**一字形**”
  > 2. 如果是“**之字形**”，就需要对要访问的节点进行**双旋转**操作，*如果访问的节点不是根的孙节点*，则进行双旋转操作后，**会将路径结构转换为“一字形”**，然后再进行“一字形”操作，将其放在根上
  > 3. 如果是“**一字形**”，就需要路径**从下到上逐一进行单旋转操作**，直至要访问的节点成为根才结束

  ![image-20230714224309258](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230714224309258.png)







**删除操作**：

- 我们可以**通过访问要被删除的节点然后访问后进行删除**，这样的话，被删除节点就会被推到根上，**将该节点删除，树就会分为两颗子树T<sub>L</sub>和T<sub>R</sub>(左子树和右子树)**
- 要想将T<sub>L</sub>和T<sub>R</sub>重新合成为一个树，就**需要找到T<sub>L</sub>的最大值**，并进行**旋转操作**，**将其作为T<sub>L</sub>的根节点**，而此时T**<sub>L</sub>将是一个没有右儿子的树**，然后将**T<sub>R</sub>的根节点作为现在T<sub>L</sub>根节点的右儿子**









代码：

```c++
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
```















## **B-树(B-tree)**

**概念**：

- B-树是一个**非二叉树**的**多路平衡查找树(数据有序)**，是**一颗所有数据都存储在树叶节点上**的树，不一定存储具体的数据，也可以是指向包含数据的记录的指针或地址

- 对于**阶为M(子节点数量在2和M之间)**的B-树具有一下结构特性：

  > 1. 树的根节点或者叶子节点，或者子节点数的范围为[2,M]
  > 2. B树每个结点关键字数量为[ceil(2/M)-1,M-1]
  > 3. 除根外，所有非树叶节点的子节点数在[ceil(2/M),M]之间，ceil为向上取整函数
  > 4. **所有的树叶都在相同的深度上**

- 非叶子节点也有存储关键词的地方，这个地方是来表示范围的(*如果要查找的数据小于该关键字就找关键字左边的子节点数据，大于就右边的子节点数据*)，**如果叶子节点数据按照升序排列，则非叶子节点的关键词有m-1个(m为该非叶子节点的子节点个数)，如果按照降序排列，则非叶子节点的关键字有m个**，例如图4-58为升序排列的B树

  ![](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230716162205621.png)







**插入操作**

- 插入在叶子节点进行

- 向B树中插入数据，**根据非叶子节点的关键字找到正确的存储数据的叶子节点**。

- 如果节点内的数据小于M-1(M为阶数)，就根据排列规则插入；如果节点能够存储的数据已经满了，就进行**分裂节点(叶子节点)**

  > 分裂节点操作步骤：
  >
  > 1. 先看看**该叶子节点的关键字数量**是否小于M-1(M为阶数)
  > 2. 按顺序插入进去，节点的关键字数量如果**大于M-1**，就**将该叶子节点分裂成两个叶子节点**，两个叶子节点的**数据各占原叶子节点的一半**，**中间的关键字(数据)作为根节点的关键字**，**剩下分成两部分的节点作为其(中间关键字形成的根节点)左右节点**。当根节点大于M-1的时候，就分裂根节点！
  > 3. 如果小于则根据插入的关键字大小按顺序插入。





**删除操作**

1. 通过递归找到指定删除的节点

2. 删除的关键字在非叶子节点上，就将其左边的指向叶子节点中的最大值跟要删除的关键字互换，就递归进去删除最大值。

3. 删除的关键字在叶子节点上

   >1. 叶子节点的关键字个数大于ceil(M/2-1),直接删除
   >2. 叶子节点的关键字个数等于ceil(M/2-1),向父节点借关键字

4. 递归返回上一层后检查该节点的关键字数，如果小于ceil(M/2-1)，就向父节点借关键字，合并该关键字的左右节点，然后不断返回上一层，不断地检查，向父节点借关键字，合并子节点直到返回到根节点。







代码：

```c++
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

//创造节点
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

//查找指定值，返回一个包含节点指针，和指定值的位置的对组
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

//分裂节点
void splitNode(btree* &root,btree* p,int index){
    if(p!=nullptr){
        if(p->keynum==p->level){
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

//插入节点
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

//查找最大值
int findmax(btree* root){
    if(nullptr==root){
        return 0;
    }else if(root->child[0]!= nullptr){
        return findmax(root->child[root->keynum]);
    }
    return root->keys[root->keynum];
}

//合并节点
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

//删除节点
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
            if(root->child[i]->keynum>=min&&root->child[i+1]->keynum>=min){
                del(root->child[i],key);
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
```















## 红黑树(RB-tree)

**概念**：

- **红黑树**是AVL树的变种，它**是每一个节点或者着成红色，或者着成黑色的一棵二叉查找树。**
- 对红黑树的操作**在最坏情形下花费O(logN)时间**，它的插入操作使用的是非递归形式实现
- 红黑树的**高度最多是2log(N+1)**





**特性**：

- 红黑树是具有**着色性质**的**二叉查找树**，也就意味着树的节点值是**有序的**，且每个节点**只可能是红色或者黑色**
- 红黑树的**根是黑色的**
- 如果**一个节点是红色的**，那么它的**子节点必须是黑色的**
- 从**一个节点到一个空指针**的**每一条路径必须包含相同数目的黑色节点**











**自顶向下插入操作**：

1. 如果使用自底向上插入的话还需要进行逐步递归是他们保证满足红黑树特性，效率就降低了。

2. 令*X为新插入节点(在下面的第三操作中为当前节点)，P为X的父节点，G为P的父节点(也就是X的祖父节点)，GP为G的父节点(也就是P的祖父节点，X的曾祖父节点)*

3. 因为红黑树是一颗二叉查找树，因此在**插入时需要查找要插入的值的正确位置**，在这个**查找路径中**，如果**遇到节点(X)为黑色而子节点全部为红色**，我们就进行`翻转操作`，也就是**将该节点(X)着成红色，子节点全部着成黑色**。**翻转后**:

   >如果翻转后发现**P和X节点都是红色**就需要根据树的结构进行`旋转操作`
   >
   >1. 如果**X，P，G形成"一字形"**，则**对P的父节点G**(也就是X的祖父节点)**与P进行**`单旋转`，并**将新根也就是P着成黑色，新根的子节点都着成红色**。
   >2. 如果**X，P，G形成"之字形"**，则对**G与X节点**进行`双旋转`，并**将新根着成黑色(也就是X节点)**，然后**将新根的子节点着成红色**

4. 如果**该节点(X)是黑色则继续将X下降**，直到**找到红色节点继续翻转**，**或者找到指定插入位置**，找到指定位置也就是当前节点位置X就进行插入，**新节点也是红色，需要重新判断其父节点是否为红色，为红色又需要进行翻转操作来调整**。













**自顶向下删除操作**

1. 自顶向下删除也需要保证红黑树的性质，插入是插入一片红色的叶子节点，那么反过来**我们删除一个红色叶子节点就不会破坏红黑树性质**，**自顶向下插入的翻转操作是将红色节点减少，并将红色节点上浮**，因为**删除是插入的逆过程，因此删除的翻转操作就是要将树中的红色节点增多，并将红色节点下沉，这样我们删除红色叶子节点的概率更大，并且不会破坏红黑树性质**

2. 删除操作一共有六种情况需要解决

   >1. 要**删除节点cur跟其兄弟节点s原本颜色为黑色**，**父亲节点p为红色**
   >
   >  - **s的两个儿子都是红色**，这样双旋转和单旋转都可以，这里优先选择`ps单选择`调整，*情况1*
   >  - **s的左儿子为红色**，需要`ps.l双旋转`调整(s.l为s的左儿子)，*情况2*
   >  - **s的右儿子为红色**，需要`ps单旋转`调整，*情况3*
   >  - **s有两个黑色儿子**，直接`cur,p,s颜色翻转操作`调整，*情况4*
   >
   >2. **p和cur为黑色**，**s为红色**，需要`交换sp节点的颜色`，并且sp`单旋转`调整，*情况5*
   >3. **cur为红色**，可以继续`将cur下降`，也就是当前cur指向原本cur的子节点，如果为红色继续下降，如果为黑色就判断是否需要操作，*情况6*

3. **tomove指向要删除节点也就是目标节点，而p指向真正要删除的叶子节点**，cur则while循环完后则是指向nil节点，因为将tomove标记完，就进行cur和p就查找tomove右子树的最小值节点进行删除，而while循环终止条件为cur==nil情况，因此p指向真正要删除的节点

4. **找到tomove和p后，将tomove的data等于p的data，将p删除**，因为p为叶子节点，将p的父节点指向nil。



![image-20230831235326572](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230831235326572.png)																				*情况2*





![image-20230831235206080](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230831235206080.png)																			*情况3*



![image-20230831235036611](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230831235036611.png)																			*情况4*



![image-20230831235617247](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230831235617247.png)																		*情况5*







**计算红黑树层数**：

- 需要**对log2(树中总共节点数+1)向上取整**

代码：

```c++
int Height(const int count){
    return std::ceil(std::log2(count+1));
}
```









**代码实现**：

```c++
typedef enum {red,black} colortype;

struct RBNode{
    int data;
    RBNode *left,*right,*parent;
    colortype color;   //颜色
    RBNode(const int val,RBNode* l,RBNode* r,RBNode* p,colortype c=red):data(val),
    left(l),right(r),parent(p),color(c){};
};

class RBtree{
public:
    RBtree(){
        nil=new RBNode(INT_MAX, nullptr, nullptr, nullptr,black);
        root= nullptr;
        t=new RBNode(INT_MIN,nil,nil,nil,black);
        size=0;
    }

    ~RBtree(){
        clear();
        delete t;
        delete nil;
    };
    void insert(const int val);      //插入操作
    void del(const int val);       //删除操作
    RBNode* find(const int val);   //查找操作
    void print();     //打印操作,层序遍历
    //清空操作
    void clear(){
        clear(root);
        root= nullptr;
        t->right=nil;
        size=0;
    }

protected:
    void overturnred(const int val,RBNode* &cur);    //翻转操作,将当前节点变成红色，子节点变成黑色
    void overturnblack(int val,RBNode* &cur);   //翻转操作，将当前节点变成黑色，子节点变成红色
    RBNode* SingleRotatewithleft(RBNode* &k1);
    RBNode* SingleRotatewithright(RBNode* &k1);
    RBNode* Rotate(const int val,RBNode* &k1){
        if(val<k1->data){
            return k1->left=val<k1->left->data? SingleRotatewithleft(k1->left): SingleRotatewithright(k1->left);
        }else{
            return k1->right=val<k1->right->data? SingleRotatewithleft(k1->right): SingleRotatewithright(k1->right);
        }
    }
    void clear(RBNode* &rt);
    // 计算红黑树层数
    int Height(int nodeCount) {
        // 红黑树的层数为 log2(nodeCount+1)
        return (int)std::ceil(std::log2(nodeCount+1));
    }
private:
    RBNode* root;
    RBNode* nil;   //空节点，color为黑色
    RBNode* t;  //根标记，用于删除操作的便捷
    int size;
};

RBNode* RBtree::SingleRotatewithleft(RBNode *&k1) {
    RBNode* k2;
    k2=k1->left;
    k1->left=k2->right;
    k2->right=k1;
    return k2;
}

RBNode* RBtree::SingleRotatewithright(RBNode *&k1) {
    RBNode* k2;
    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;
    return k2;
}

//翻转操作
void RBtree::overturnred(const int val,RBNode* &cur) {
    cur->color=red;
    cur->left->color=cur->right->color=black;
    RBNode* p=cur->parent;
    if(p->color==red){
        RBNode* g=p->parent;
        g->color=red;
        if((val<g->data)!=(val<p->data)){     //双旋转
            p= Rotate(val,g);
        }
        cur= Rotate(val,g->parent);
        cur->color=black;
    }
    root->color=black;
}


//插入操作
void RBtree::insert(const int val) {
    if(root== nullptr){
        root=new RBNode(val,nil,nil, t,black);
        t->right=root;
        size++;
        return;
    }
    RBNode *cur,*p;
    cur=p=root;
    while (cur!=nil){
        p=cur;
        if(cur->left->color==red&&cur->right->color==red){
            overturnred(val,cur);
        }
        cur=val<p->data?p->left:p->right;
    }
    if(cur!=nil){
        return;
    }
    cur=new RBNode(val, nil, nil, p);
    if(val<p->data){
        p->left=cur;
    }else{
        p->right=cur;
    }
    overturnred(val,cur);
    size++;
}

void RBtree::overturnblack(int val, RBNode *&cur) {
    cur->color=red;
    RBNode* p=cur->parent;
    RBNode* s=val<p->data?p->left:p->right;
    //case4:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的两个儿子都是红色，这样双旋转和单旋转都可以，这里优先选择ps单选择
    //case1:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的左儿子为红色的情况,需要ps.l双旋转调整
    if(s->left->color==red){
        val=s->left->data;
    }
    //case2:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的右儿子为红色情况，需要ps单旋转调整
    else if(s->right->color==red){
        val=s->right->data;
    }
    //case3:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s有两个黑儿子(nil节点也是黑色),直接将颜色翻转即可
    else{
        //翻转操作
        if(s!=nil){
            s->color=red;
        }
        p->color=black;
        return;
    }
    if((val<s->data)!=(val<p->data)){
        Rotate(val,p);
    }
    RBNode* g=p->parent;
    Rotate(val,g);
    //将调整完的cur的新祖父也就是s或者s的左儿子变成红色，也就是删除完cur后将颜色调整到之前cur在翻转前的情况
    g->color=red;
    g->left->color=g->right->color=black;
}


void RBtree::del(const int val) {
    RBNode* tomove=nil;  //找到删除节点
    RBNode *g,*p,*s,*cur;
    g=p=t,s=t->left,cur=root;
    while (cur!=nil){
        //翻转颜色
        if(cur->left->color==black&&cur->right->color==black){
            overturnblack(val,cur);
        }else{
            g=p;p=cur;
            if(val<p->data){
                cur=p->left,s=p->right;
            }else{
                tomove=cur,cur=p->right,s=p->left;
            }
            //case5:此时肯定p和cur都为黑色，因为如果p为红色早就翻转了，s肯定是红色，将s变成黑色，p变为红色，sp单旋转调整
            if(cur->color==black){
                s->color=black;
                p->color=red;
                //单旋转完，cur新祖父变为s,将s重新更改
                g= Rotate(val,g);
                s=val<p->data?p->left:p->right;
                //调整完该情况就重新检查上述操作
                continue;
            }
            //else，cur一定为红色，则可以直接继续将cur继续下降
        }
        g=p;p=cur;
        if(val<p->data){
            cur=p->left,s=p->right;
        }else{
            tomove=cur,cur=p->right,s=p->left;
        }
    }
    root->color=black;   //保证红黑树性质2不被破坏，也就是根一定为黑色

    //判断是否找到真正要删除的节点，如果找不到就退出
    if(tomove==nil&&tomove->data!=val){
        cout<<"未找到要删除对应值的节点";
        return;
    }

    //tomove是要删除的节点，而p指向的是真正要删除的节点
    tomove->data=p->data;
    if(g->left==p) g->left=nil;
    else g->right=nil;
    delete p;
    size--;
}

RBNode* RBtree::find(const int val) {
    if(root!= nullptr){
        RBNode* cur=root;
        while (cur!=nil){
            if(cur->data==val) return cur;
            cur=val<cur->data?cur->left:cur->right;
        }
        if(cur==nil){
            cout<<"树中没有指定值节点"<<endl;
        }
    }
    return root;
}

void RBtree::print() {
    if(root== nullptr){
        cout<<"树为空"<<endl;
        return;
    }
    queue<RBNode*>q;
    q.push(root);
    int cnt=1;
    int ans=0;
    int h= Height(size);
    while (!q.empty()){
        if(ans==h) break;
        RBNode* cur=q.front();
        q.pop();
        q.push(cur->left);
        q.push(cur->right);
        if(cur->color==red){
            cout<<"\033[31m"<<cur->data<<"\033[0m"<<" ";
        }else if(cur==nil) cout<<"nil"<<" ";
        else cout<<cur->data<<" ";
        if(cnt==pow(2,ans)){
            cout<<endl;
            cnt=0,ans++;
        }
        cnt++;
    }
    return;
}


void RBtree::clear(RBNode* &rt) {
    if(rt!=nil){
        clear(rt->left);
        clear(rt->right);
        delete rt;
        rt=nil;
    }
    return;
}
```

