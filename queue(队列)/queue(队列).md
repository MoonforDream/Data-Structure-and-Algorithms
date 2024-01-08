# 队列(queue)

**概念**：

- **队列**也是一种线性表，使用队列时插入在一端进行而删除则在另一端进行，队列的基本操作是**入队**，它是在**表的末端**(也叫做**队尾**)插入一个元素，**出队**，它是删除在**表的开头(****队头**)的元素。



![image-20230706231238605](https://github.com/MoonforDream/Data-Structure-and-Algorithms/tree/main/images/image-20230706231238605.png)











**数组实现**：

```c++
//数组实现
class queue{
public:
    //入队(向数组末尾插入数据)
    void Push(int data){
        head.push_back(data);
    }

    //出队(将数组第一个元素删除)
    void Pop(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return;
        } else{
            auto it=head.begin();
            head.erase(it);
        }
    }

    //获取队首元素
    int front(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return NULL;
        }
        return head[0];
    }

    //打印队列
    void print(){
        if(head.empty()){
            cout<<"队列中没有数据！"<<endl;
            return;
        }
        for(int i:head){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    //清空队列
    void destroy(){
        head.clear();
    }

    //获取队列大小
    int size(){
        return head.size();
    }

    //判断队列是否为空
    bool empty(){
        if(head.empty()){
            return true;
        } else{
            return false;
        }
    }

private:
    vector<int>head;
};
```







**链表实现：**

```c++
//链表实现
struct Queue{
    int data;
    Queue* next;
};

Queue* createNode(int data){
    auto p=new Queue;
    p->data=data;
    p->next=NULL;
    return p;
}

//入队
void push(Queue* &head,int data){
    Queue* add= createNode(data);
    if (head==NULL){
        head=add;
    }else{
        Queue* p=head;
        while (p->next!=NULL){
            p=p->next;
        }
        p->next=add;
    }
}

//出队
void pop(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* p=head;
    head=p->next;
    delete p;
}

//获取队首元素
int front(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return NULL;
    }
    return head->data;
}

//打印队列
void print(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//清空队列
void destroy(Queue* &head){
    if(head==NULL){
        cout<<"队列中没有元素"<<endl;
        return;
    }
    Queue* tail=head->next;
    while (head!=NULL){
        delete head;
        head=tail;
        if(tail!=NULL)
            tail=tail->next;
        else
            return;
    }
}
```

