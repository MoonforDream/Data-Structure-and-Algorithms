#include <iostream>
#include <queue>
using namespace std;

struct listnode{
    int data;
    listnode* next;
};

class graph{
public:
    graph(int n){
        vnum=n;
        an=new listnode[n+1];
        indegree=(int*) malloc(sizeof(int)*(n+1));
        for(int i=0;i<n+1;i++){
            an[i].data=0;
            an[i].next= nullptr;
            indegree[i]=0;
        }
    }
    listnode* createNode(int data){
        auto p=new listnode;
        p->data=data;
        p->next= nullptr;
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
        indegree[data]++;
    }
    int findedgenull(){
        for(int i=1;i<=vnum;i++){
            if(indegree[i]==0){
                return i;
            }
        }
        return 0;
    }
    //拓扑排序
    void topsort(){
        queue<int>q;
        int v=findedgenull();
        if(v==0){
            cout<<"该图含有圈"<<endl;
            return;
        }else{
            q.push(v);
            if(q.empty()){
                cout<<"该图含有圈"<<endl;
                return;
            }
            while (!q.empty()){
                int w=q.front();
                cout<<w<<" ";
                q.pop();
                listnode* p=an[w].next;
                while (p!= nullptr){
                    if(--indegree[p->data]==0){
                        q.push(p->data);
                    }
                    p=p->next;
                }
            }
            cout<<endl;
        }
    }
private:
    listnode *an;
    int vnum;
    int *indegree;
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
    g.topsort();
//    g.print();
    system("pause");
    return 0;
}
