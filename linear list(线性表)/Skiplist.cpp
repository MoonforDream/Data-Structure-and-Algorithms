#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct Node{
    int val;     //存储元素值
    vector<Node*>next;   //存储各层数指针的数组
    int level;  //阶数
};


class skiplist{
public:
    skiplist(int level):Maxlevel(level){
        head= createNode(NULL,Maxlevel);
    }
    ~skiplist() {
        Node* tail=head;
        Node* p;
        while (tail!= nullptr){
            p=tail;
            tail=tail->next[0];
            delete p;
        }
        head= nullptr;
    };

    Node* find(int data);
    void insert(int data);
    void del(int data);
    void print();

private:
    Node* head;
    int Maxlevel;

    Node* createNode(int data,int level){
        auto p = new Node;
        p->val=data;
        p->level=level;
        p->next.resize(level,NULL);
        return p;
    }

    int rand_level(){
        int level=1;
        while(rand()%2&&level<=Maxlevel){
            level++;
        }
        return level;
    }


};

Node *skiplist::find(int data) {
    Node* p=head;
    for(int i=Maxlevel-1;i>=0;i--){
        while (p->next[i]!= nullptr&&p->next[i]->val<data){
            p=p->next[i];
        }
    }
    if(p->next[0]!= nullptr&&p->next[0]->val==data){
        return p->next[0];
    }
    return nullptr;
}

void skiplist::insert(int data) {
    int level=rand_level();
    Node* add= createNode(data,level);
    if(head->next[0]== nullptr){
        head->next[0]=add;
        return;
    }
    Node* p=head;
    Node* prev[level];
    for(int i=level-1;i>=0;i--){
        while (p->next[i]!= nullptr&&p->next[i]->val<data){
            p=p->next[i];
        }
        prev[i]=p;
    }
    for(int i=0;i<level;i++){
        add->next[i]=prev[i]->next[i];
        prev[i]->next[i]=add;
    }
}

void skiplist::del(int data) {
    Node* p=head;
    Node* prev[Maxlevel];
    for(int i=Maxlevel-1;i>=0;i--){
        while (nullptr!=p->next[i]&&p->next[i]->val<data){
            p=p->next[i];
        }
        prev[i]=p;
    }
    if(p->next[0]!= nullptr&&p->next[0]->val==data){
        Node* tail=p->next[0];
        for(int i=Maxlevel-1;i>=0;i--){
            if(prev[i]->next[i]!= nullptr&&prev[i]->next[i]->val==data)
                prev[i]->next[i]=prev[i]->next[i]->next[i];
        }
        delete tail;
    }
}

void skiplist::print() {
    Node* p=head->next[0];
    while (p!= nullptr){
        cout<<p->val<<" ";
        p=p->next[0];
    }
    cout<<endl;
}


int main() {
    skiplist sl(8);
    sl.insert(1);
    sl.insert(2);
    sl.insert(10);
    sl.insert(31);
    sl.insert(21);
//    sl.del(21);
    Node* p=sl.find(10);
    cout<<p->val;
    sl.print();
    system("pause");
    return 0;
}
