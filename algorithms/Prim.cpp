#include <iostream>
#include <queue>
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
    void Prim(int v){
        an[v].dist=0;
        //ʹ�����ȶ���
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
        //pair<int,int>����ĵ�һ��ΪȨ���ڶ���Ϊ���㡣
        q.push(make_pair(0,v));
        while (!q.empty()){
            int w=q.top().second;
            q.pop();
            listnode* p=an[w].next;
            if(an[w].flag) continue;
            while (p!= nullptr){
                //ѡȡ��СȨ�ı߶����Ƕ��㵽�������̾���
                if(p->weight<an[p->data].dist&&!an[p->data].flag){
                    an[p->data].dist=p->weight;
                    an[p->data].path=w;
                    q.push(make_pair(p->weight,p->data));
                }
                p=p->next;
            }
            an[w].flag= true;
        }
        int w=0;     //��¼��С����������Ȩ
        for(int i=1;i<=vnum;i++){
            if(an[i].path!=0){
                if(i>an[i].path)
                    cout<<"("<<an[i].path<<","<<i<<")"<<" Ȩ:"<<an[i].dist<<endl;
                else
                    cout<<"("<<i<<","<<an[i].path<<")"<<" Ȩ:"<<an[i].dist<<endl;
                w+=an[i].dist;
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
    g.Prim(1);
    system("pause");
    return 0;
}
