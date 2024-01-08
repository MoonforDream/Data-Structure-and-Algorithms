#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct listnode{
    int data;
    int path;     //存储上一个顶点
    int dist;     //最短距离
    int weight;   //边的权重
    bool flag;   //判断是否有放入队列中
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
            an[i].path=0;
            an[i].weight=0;
            an[i].flag= false;
            an[i].dist=INT_MAX;
        }
    }
    listnode* createNode(int data,int weight){
        auto p=new listnode;
        p->data=data;
        p->next= nullptr;
        p->path=0;
        p->weight=weight;
        p->flag= false;
        return p;
    };
    void insert(int v,int data,int weight){
        auto add= createNode(data,weight);
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
    void Dijkstra(int v){
        an[v].dist=0;
        queue<int>q;
        q.push(v);
        while (!q.empty()){
            int w=q.front();
            q.pop();
            listnode* p=an[w].next;
            while (p!= nullptr){
                if(an[w].dist+p->weight<an[p->data].dist){
                    an[p->data].dist=an[w].dist+p->weight;
                    an[p->data].path=w;
//                    q.push(p->data);
                    if(!an[p->data].flag){
                        q.push(p->data);
                        an[p->data].flag= true;
                    }
                }
                p=p->next;
            }
        }
    }
    void print(int v1,int v2){
        Dijkstra(v1);
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
    g.insert(1,2,2);
    g.insert(1,4,1);
    g.insert(3,1,4);
    g.insert(2,4,3);
    g.insert(5,2,10);
    g.insert(3,6,5);
    g.insert(4,6,8);
    g.insert(4,7,4);
    g.insert(4,3,2);
    g.insert(4,5,2);
    g.insert(5,7,6);
    g.insert(7,6,1);
    g.print(2,5);
    system("pause");
    return 0;
}
