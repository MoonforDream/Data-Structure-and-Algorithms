#include <iostream>
#include <queue>
#include <stack>
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
    }
    void BFS(int s){
        queue<int>q;
        q.push(s);
        an[s].dist=0;
        while (!q.empty()){
            int v=q.front();
            q.pop();
            an[v].flag= true;
            listnode* p=an[v].next;
            while (p!= nullptr){
                if(an[p->data].dist==INT_MAX){
                    an[p->data].dist=an[v].dist+1;
                    an[p->data].path=v;
                    q.push(p->data);
                }
                p=p->next;
            }
        }
    }
    void print(int v1,int v2){
        BFS(v1);
        if(an[v2].dist==INT_MAX){
            cout<<"v"<<v1<<"到达不了"<<"v"<<v2<<endl;
            return;
        }
        stack<int>s;
        cout<<"v"<<v1<<"->v"<<v2<<"最短路径长为:"<<an[v2].dist<<endl;
        cout<<"路径为:"<<endl;
        while (v2!=0){
            s.push(v2);
            v2=an[v2].path;
        }
        while (!s.empty()){
            cout<<s.top()<<" ";
            s.pop();
        }
        cout<<endl;
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
    g.print(1,3);
    system("pause");
    return 0;
}
