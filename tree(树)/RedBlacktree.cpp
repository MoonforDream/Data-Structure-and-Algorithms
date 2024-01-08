#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

typedef enum {red,black} colortype;

struct RBNode{
    int data;
    RBNode *left,*right,*parent;
    colortype color;   //��ɫ
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
    void insert(const int val);      //�������
    void del(const int val);       //ɾ������
    RBNode* find(const int val);   //���Ҳ���
    void print();     //��ӡ����,�������
    //��ղ���
    void clear(){
        clear(root);
        root= nullptr;
        t->right=nil;
        size=0;
    }

protected:
    void overturnred(const int val,RBNode* &cur);    //��ת����,����ǰ�ڵ��ɺ�ɫ���ӽڵ��ɺ�ɫ
    void overturnblack(int val,RBNode* &cur);   //��ת����������ǰ�ڵ��ɺ�ɫ���ӽڵ��ɺ�ɫ
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
    // ������������
    int Height(int nodeCount) {
        // ������Ĳ���Ϊ log2(nodeCount+1)
        return (int)std::ceil(std::log2(nodeCount+1));
    }
private:
    RBNode* root;
    RBNode* nil;   //�սڵ㣬colorΪ��ɫ
    RBNode* t;  //����ǣ�����ɾ�������ı��
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

//��ת����
void RBtree::overturnred(const int val,RBNode* &cur) {
    cur->color=red;
    cur->left->color=cur->right->color=black;
    RBNode* p=cur->parent;
    if(p->color==red){
        RBNode* g=p->parent;
        g->color=red;
        if((val<g->data)!=(val<p->data)){     //˫��ת
            p= Rotate(val,g);
        }
        cur= Rotate(val,g->parent);
        cur->color=black;
    }
    root->color=black;
}


//�������
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
    //case4:Ҫɾ���ڵ�cur�����ֵܽڵ�sԭ����ɫΪ��ɫ�����׽ڵ�pΪ��ɫ��s���������Ӷ��Ǻ�ɫ������˫��ת�͵���ת�����ԣ���������ѡ��ps��ѡ��
    //case1:Ҫɾ���ڵ�cur�����ֵܽڵ�sԭ����ɫΪ��ɫ�����׽ڵ�pΪ��ɫ��s�������Ϊ��ɫ�����,��Ҫps.l˫��ת����
    if(s->left->color==red){
        val=s->left->data;
    }
    //case2:Ҫɾ���ڵ�cur�����ֵܽڵ�sԭ����ɫΪ��ɫ�����׽ڵ�pΪ��ɫ��s���Ҷ���Ϊ��ɫ�������Ҫps����ת����
    else if(s->right->color==red){
        val=s->right->data;
    }
    //case3:Ҫɾ���ڵ�cur�����ֵܽڵ�sԭ����ɫΪ��ɫ�����׽ڵ�pΪ��ɫ��s�������ڶ���(nil�ڵ�Ҳ�Ǻ�ɫ),ֱ�ӽ���ɫ��ת����
    else{
        //��ת����
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
    //���������cur�����游Ҳ����s����s������ӱ�ɺ�ɫ��Ҳ����ɾ����cur����ɫ������֮ǰcur�ڷ�תǰ�����
    g->color=red;
    g->left->color=g->right->color=black;
}


void RBtree::del(const int val) {
    RBNode* tomove=nil;  //�ҵ�ɾ���ڵ�
    RBNode *g,*p,*s,*cur;
    g=p=t,s=t->left,cur=root;
    while (cur!=nil){
        //��ת��ɫ
        if(cur->left->color==black&&cur->right->color==black){
            overturnblack(val,cur);
        }else{
            g=p;p=cur;
            if(val<p->data){
                cur=p->left,s=p->right;
            }else{
                tomove=cur,cur=p->right,s=p->left;
            }
            //case5:��ʱ�϶�p��cur��Ϊ��ɫ����Ϊ���pΪ��ɫ��ͷ�ת�ˣ�s�϶��Ǻ�ɫ����s��ɺ�ɫ��p��Ϊ��ɫ��sp����ת����
            if(cur->color==black){
                s->color=black;
                p->color=red;
                //����ת�꣬cur���游��Ϊs,��s���¸���
                g= Rotate(val,g);
                s=val<p->data?p->left:p->right;
                //���������������¼����������
                continue;
            }
            //else��curһ��Ϊ��ɫ�������ֱ�Ӽ�����cur�����½�
        }
        g=p;p=cur;
        if(val<p->data){
            cur=p->left,s=p->right;
        }else{
            tomove=cur,cur=p->right,s=p->left;
        }
    }
    root->color=black;   //��֤���������2�����ƻ���Ҳ���Ǹ�һ��Ϊ��ɫ

    //�ж��Ƿ��ҵ�����Ҫɾ���Ľڵ㣬����Ҳ������˳�
    if(tomove==nil&&tomove->data!=val){
        cout<<"δ�ҵ�Ҫɾ����Ӧֵ�Ľڵ�";
        return;
    }

    //tomove��Ҫɾ���Ľڵ㣬��pָ���������Ҫɾ���Ľڵ�
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
            cout<<"����û��ָ��ֵ�ڵ�"<<endl;
        }
    }
    return root;
}

void RBtree::print() {
    if(root== nullptr){
        cout<<"��Ϊ��"<<endl;
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
//    rBtree.del(65);
//    rBtree.del(50);
//    rBtree.del(30);
    rBtree.print();
    system("pause");
    return 0;
}
