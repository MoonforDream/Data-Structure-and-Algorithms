#include <iostream>
#include <queue>
#include <math.h>
#include <limits.h>
using namespace std;

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
    //case4:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的两个儿子都是红色，这样双旋转和单旋转都可以，这里优先选择ps单选转
    //case2:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的右儿子为红色情况，需要ps单旋转调整
    if(s->right->color==red){
        val=s->right->data;
    }
    //case1:要删除节点cur跟其兄弟节点s原本颜色为黑色，父亲节点p为红色，s的左儿子为红色的情况,需要ps.l双旋转调整
    else if(s->left->color==red){
        val=s->left->data;
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
        if(ans==h+1) break;
        RBNode* cur=q.front();
        q.pop();
        if(cur== nullptr){
            cout<<"null"<<" ";
            continue;
        }
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

int main() {
    RBtree rBtree;
    rBtree.insert(30);
    rBtree.insert(15);
    rBtree.insert(65);
    rBtree.insert(10);
    rBtree.insert(20);
    rBtree.insert(5);
    rBtree.insert(60);
    rBtree.insert(70);
    rBtree.insert(50);
    rBtree.insert(64);
    rBtree.insert(66);
    rBtree.insert(85);
    rBtree.insert(40);
    rBtree.insert(55);
    rBtree.insert(63);
    rBtree.insert(80);
    rBtree.insert(90);
    rBtree.insert(45);
    rBtree.del(65);
    rBtree.del(50);
    rBtree.del(30);
    rBtree.print();
    return 0;
}

