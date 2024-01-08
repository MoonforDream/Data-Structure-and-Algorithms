# 堆(优先队列)

## 二叉堆

**概念**：

- 优先队列是一个根据优先性而先去执行操作的一种特殊队列，平常队列是先进先出，但是优先队列是根据优先级选择先出的元素。优先队列的主要操作有插入和删除最小值

- **堆(heap)**通常是指**二叉堆**，因为二叉堆的使用次数最频繁，所以我们平常认为的堆就是二叉堆

- **二叉堆**：二叉堆是由**一颗完全二叉树实现**的，完全二叉树是**一颗底层必须从左往右依次插入且底层以上的节点都是填满的树(最后一层也就是叶子节点可以不是填满的，但是已经插入的元素必须是从左到右的中间不空缺元素的)**称为完全二叉树

- 完全二叉树是一个**很有规律的树**，因此**用一个动态数组实现是效率最好的选择**，在动态数组中是按照**从上到下从左到右依次插入数组**中，数组下标为0处不放元素。

  >用数组实现的完全二叉树的性质有：
  >
  >1. 对于**数组中任意一个位置i上的元素**，其**左儿子在数组位置2i上**，**右儿子在**左儿子后的单元也就是**数组下标为(2i+1)的位置**，它的**父亲在i/2的位置上**。
  >2. **数组下标为0的地方是不放我们要存的元素的**



**性质**：

- 堆也就是通常认为的二叉堆(binary heap)，是由一颗完全二叉树实现的
- 堆中的主要操作有插入和删除最小值操作，**堆的删除其实就是删除最小值而不是删除指定值**
- 堆有**堆序性质**，也就是**堆中的任意子树也是一个堆**，因此**任意节点就应该小于它的子节点**，因为堆需要快速查找最小元，因此**我们将最小元放在根节点上**。
- 其**结构体**应该包含**一个数组(动态)**，**堆中存储的有效元素个数**，**数组的容量**以便于扩容



**最大堆/大根堆**：任意节点应该**大于**它的所有后裔

**最小堆/小根堆**：任意节点应该**小于**它的所有后裔



**插入操作(上浮)**：

- 先遵从**堆从上到下，从左到右依次插入**，我们将数据按照这个准则插入到数组。
- 然而，插入后，我们还需要进行**检查这个堆是否有堆序性**，如果没有就需要进行调整
- **插入数据跟根节点进行比较，如果根节点的值比插入数据大，就需要交换，然后一路向上检查比较，直到根节点。**



**删除操作(下沉)**：

- 堆的**删除操作是删除最小值的操作**，而不是删除指定值的操作
- 我们创建堆时，都将**最小值放到根节点**，因此删除我们只需要将根节点删除掉
- 但是删除根节点后，我们的堆序性就无法保证，如何保证堆序性以及堆的性质(也就是完全二叉树的性质)呢
- 我们**需要将根节点的值与叶子层的最右边元素进行交换**，然后**删除交换后处在叶子节点(也就是原来的根节点)的节点**，然后让**现在的根节点跟左右子节点的最小节点比较**，如果**大于就交换，直到检查到叶子节点**，则就调整成功了。





**构建堆**

- 构建堆的操作就**是将一个无序的树，构造成一个堆**
- 一个堆满足完全二叉树的特性以及堆序性，因此我们**需要对这个无序树进行调整**，让其成为一个堆。





实现代码：

```c++
class heap{
public:
    heap(int maxsize){
        key=new int[maxsize+1];
        key[0]=0;
        for(int i=1;i<maxsize+1;i++){
            key[i]=0;
        }
        size=0;
        capacity=maxsize;
    }
    int find(int data){
        for(int i=1;i<size;i++){
            if(key[i]==data){
                return i;
            }
        }
        cout<<"没有找到"<<endl;
        return -1;
    }
    void adjust(int data){
        key[size+1]=data;
        int index=size+1;
        while(index>0){
            int i=index;
            index=index/2;
            if(key[index]>key[i]){
                int temp=key[index];
                key[index]=key[i];
                key[i]=temp;
            }
        }
    }
    void insert(int data){
        if(size==capacity){
            int *an=new int[2*capacity];
            capacity=capacity*2;
            for(int i=0;i<=size;i++){
                an[i]=key[i];
            }
            delete[] key;
            key=an;
        }
        if(key[1]==0){
            key[1]=data;
        }else{
            adjust(data);
        }
        size++;
    }
    void deladjust(int index){
        if(index*2<=size){
            int mn;
            if(key[index*2+1]==NULL){
                mn=index*2;
            }
            else if(key[index*2]>key[index*2+1]){
                mn=index*2+1;
            }else{
                mn=index*2;
            }
            if(key[index]>key[mn]){
                int temp=key[index];
                key[index]=key[mn];
                key[mn]=temp;
            }
            deladjust(mn);
        }
        return;
    }
    void delmin(){
        key[1]=key[size];
        key[size]=0;
        size--;
        deladjust(1);
    }
    void destroy(){
        for(int i=1;i<=size;i++){
            key[i]=0;
        }
        size=0;
        cout<<"成功清除堆中数据"<<endl;
    }
    void print(){
        int cnt=1;
        for(int i=1;i<=size;i++){
            cout<<key[i]<<" ";
            if(i==cnt){
                cout<<endl;
                cnt=pow(2,cnt)+i;
            }
        }
    }
private:
    int *key;    //动态数组，用来存储树节点的元素
    int size;    //堆中存在的有效元素个数
    int capacity;    //数组容量
};
```











## d-堆

**概念**：

- **d-堆**是二叉堆的简单推广，**它的所有的节点都有d个子节点**，**d-堆的底层也是由一颗完全树构成的**，二叉堆是由完全二叉树构成，3-堆则就是由完全三叉树构成
- 当**堆太大不能完全装入主存的时候**，**d-堆就很有用**，因为**d-堆能够以与B-树大致相同的方式发挥作用**
- d-堆的高度比较浅
- d-堆的性质跟二叉堆相同。因为二叉堆是d-堆的一种特殊情况。











## 左式堆

**概念**：

- 左式堆是**一种能够高效的支持合并操作的堆**，左式堆的**底层也是由二叉树实现**，但是左式堆不是平衡的(**不由完全二叉树实现的**)，**左式堆趋向于不平衡**。
- 左式堆也像二叉堆一样拥有着堆的特性(有序性和结构性)，**左式堆是最小堆**
- 左式堆是一个**拥有堆序性的二叉树(不是二叉堆)加上NPL特性的一棵树**，**任意节点X的NPL(X)(零路径长)为从X到一个没有两个儿子的节点的最短路径的长，因此，具有0个或1个儿子的节点的Npl为0，而Npl(NULL)=-1.**



**性质**：

- **任意一个节点的零路径长比它的子节点的零路径长的最小值+1**
- **对于堆中的每一个节点X，左儿子的零路径长大于等于右儿子的零路径长**
- 在右路径上有r个节点的左式树必然至少有2<sup>r</sup>-1个节点
- 对左式堆的右路径的插入和合并操作可能会破坏左式堆的性质，需要进行调整







**合并操作**

- 插入其实就是合并的一个特殊情况
- 如果两个左式堆合并，有一个堆为空就返回另外一个堆，否则**比较两个堆的根值**
- **递归进去**，我们**将大的根值的堆与小的根值的堆的右子堆合并**
- 然后递归返回后，**将新的堆作为原来小的根值的堆的右孩子(也叫合并)**。
- **如果这样形成的堆的右子堆的零路径长大于左子堆的，就将左子堆跟右子堆交换，并且更新零路径长，就完成了合并的操作。**





实现代码：

```c++
#include <iostream>
using namespace std;

struct heapNode{
    int data;    //数据
    heapNode* left;    //左子节点指针
    heapNode* right;   //右子节点指针
    int Npl;     //零路径长
};

class leftheap{
public:
    leftheap(){
        root=new heapNode;
        root->left= nullptr;
        root->right= nullptr;
        root->data=INT_MAX;
        root->Npl=0;
    }
    heapNode* createNode(int data){
        auto p=new heapNode;
        p->data=data;
        p->left= nullptr;
        p->right= nullptr;
        p->Npl=0;
        return p;
    }
    heapNode* merge(heapNode* h1,heapNode* h2){
        if(h1->left== nullptr){
            h1->left=h2;
        }else{
            h1->right= findmerge_node(h1->right,h2);
            if(h1->left->Npl<h1->right->Npl){
                heapNode* p=h1->left;
                h1->left=h1->right;
                h1->right=p;
            }
            h1->Npl=h1->right->Npl+1;
        }
        return h1;
    }
    heapNode* findmerge_node(heapNode* h1,heapNode* h2){
        if(nullptr==h1){
            return h2;
        }else if(nullptr==h2){
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
        } else
            root=findmerge_node(root,add);
    }
    void delmin(){
        if(root== nullptr){
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
```













## 斜堆

**概念**：

- **斜堆**是**左式堆的自调节形式**，斜堆和左式堆间的关系类似于伸展树和AVL树间的关系
- 斜堆是**具有堆序性的二叉树**，但是**不存在对树的结构限制**
- 不同于左式堆，**关于任意节点的零路径长的任何信息都不保留，因为斜堆的右路径在任何时刻都可以任意长**





**合并操作**

- 斜堆的合并大概都跟左式堆的合并操作一样，但是交换操作不一样，**斜堆的交换是无条件的**
- **就是说当进行将大的根值的堆与小的根值的堆的右子堆合并后，我们就需要进行左子树跟右子树交换的操作，并不是只有到最后小的根值的堆跟新的堆合并后在进行交换**
- 就是**每个合并的步骤就需要交换左右子树**。





实现代码：

```c++
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

```

