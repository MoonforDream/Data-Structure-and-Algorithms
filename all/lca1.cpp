#include <bits/stdc++.h>
using namespace std;

const int N=5e5+20;
int n,m,s,a,b;  //n为节点数，m为查询次数，s为根节点编号,a和b用于临时存储节点的临时变量
int dep[N],p[N];
vector<int>g[N]; //存储边集

void dfs(int u,int d){
    dep[u]=d;
    int size=g[u].size();
    for(int i=0;i<size;++i){
        int v=g[u][i];
        if(v==p[u]) continue;
        p[v]=u;
        dfs(v,d+1);
    }
}

int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]) x=p[x];
    while(x!=y){
        x=p[x];
        y=p[y];
    }
    return x;
}


int main() {
    cin>>n>>m>>s;
    for(int i=1;i<n;++i){
        cin>>a>>b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(s,0);
    while(m--){
        cin>>a>>b;
        cout<<lca(a,b)<<endl;
    }
    system("pause");
    return 0;
}
