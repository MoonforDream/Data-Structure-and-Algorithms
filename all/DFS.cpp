#include <iostream>
using namespace std;

struct listnode{
    int data;
    bool flag;    //判断是否访问过
    int path;     //存储上一个顶点
    int dist;     //距离
    listnode* next;
};

class graph{
public:
    graph(int n){
        vnum=n;
        an=new listnode[n+1];
        for(int i=0;i<n+1;i++){
            an[i].data=0;
            an[i].next= nullptr;
            an[i].flag=0;
            an[i].path=0;
            an[i].dist=INT_MAX;
        }
    }
    listnode* createNode(int data){
        auto p=new listnode;
        p->data=data;
        p->next= nullptr;
        p->flag=0;
        p->path=0;
        return p;
    };
    void insert(int v,int data){
        auto add= createNode(data);
        if(an[v].next== nullptr){
            an[v].next=add;
        } else{
            listnode* p=an[v].next;
            while (p->next!= nullptr){
                p=p->next;
            }
            p->next=add;
        }
        auto add1= createNode(v);
        if(an[data].next== nullptr){
            an[data].next=add1;
        } else{
            listnode* p=an[data].next;
            while (p->next!= nullptr){
                p=p->next;
            }
            p->next=add1;
        }
    }
    void DFS(int v){
        cout<<v;
        an[v].flag= true;
        listnode* p=an[v].next;
        while (p!= nullptr){
            if(!an[p->data].flag){
                DFS(p->data);
            }
            p=p->next;
        }
    }
private:
    listnode *an;
    int vnum;
};

int main() {
    graph g(7);
    g.insert(1,2);
    g.insert(1,4);
    g.insert(1,3);
    g.insert(2,4);
    g.insert(2,5);
    g.insert(3,6);
    g.insert(4,6);
    g.insert(4,7);
    g.insert(4,3);
    g.insert(5,4);
    g.insert(5,7);
    g.insert(7,6);
    g.DFS(2);
    system("pause");
    return 0;
}