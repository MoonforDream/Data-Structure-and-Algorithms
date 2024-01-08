#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;   // ����һ����ʾ������ֵ

struct listnode{
    int data;
    int path;     //�洢��һ������
    int dist;     //��̾���
    int weight;   //�ߵ�Ȩ��
    bool flag;    //�ж��Ƿ���ʹ�
    listnode* next;
};


struct edge{
    int u,v,w;  //u��vΪ����ģ�wΪȨ��,uΪ��ʼ�㣬vΪ�յ�
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
            an[i].dist=INF;
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
        auto add1= createNode(v,weight);
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
    static bool cmp(const edge &a,const edge &b){
        return a.w<b.w;
    }
    int findroot(int v,int parent[]){
        int t=v;
        while (parent[t]>-1){    //���Ҹü��ϵĸ��ڵ�(����)��
            t=parent[t];
        }
        return t;
    }
    void Kruskal(int v){
        vector<edge>q;
        //�洢ÿ����ͨ�����ĸ��׽ڵ������
        int parent[vnum+1];
        int w=0;     //��¼��С����������Ȩ
        memset(parent,-1, sizeof(int)*(vnum+1));
        //���ɱ߼����顣
        for(int i=1;i<=vnum;i++) {
            listnode *p = an[i].next;
            while (p != nullptr) {
                if(i<p->data)
                    q.push_back({i, p->data, p->weight});
                p = p->next;
            }
        }
        //����������СȨ�߷����һλ��
        sort(q.begin(),q.end(), cmp);
        for(int i=0,num=0;num<vnum-1;i++){
            int v1=findroot(q[i].u,parent);
            int v2= findroot(q[i].v,parent);
            //�ж����Ƚڵ��Ƿ����--�ж��Ƿ���һ������.
            if(v1!=v2){
                cout<<"("<<q[i].u<<","<<q[i].v<<")"<<" Ȩ:"<<q[i].w<<endl;
                w+=q[i].w;
                parent[v2]=v1;    //�ϲ����ϡ�
                num++;
            }
        }
        cout<<"��Ȩ:"<<w;
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
    g.insert(1,3,4);
    g.insert(2,4,3);
    g.insert(5,2,10);
    g.insert(3,6,5);
    g.insert(4,6,8);
    g.insert(4,7,4);
    g.insert(4,3,2);
    g.insert(4,5,7);
    g.insert(5,7,6);
    g.insert(7,6,1);
    g.Kruskal(1);
    system("pause");
    return 0;
}
