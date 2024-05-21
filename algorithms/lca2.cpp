#include <bits/stdc++.h>
using namespace std;

const int N=5e5+20;
int n,m,s,a,b;  //n为节点数，m为查询次数，s为根节点编号,a和b用于临时存储节点的临时变量
int dep[N],f[N][22]; //log2(N)算出来19，可以创建大于19的数组
vector<int>g[N]; //存储边集

void dfs(int u,int p,int d){
    dep[u]=d;
    f[u][0]=p;
    for(int i=1;i<=log2(dep[u]);++i){
        f[u][i]=f[f[u][i-1]][i-1];
    }
    int size=g[u].size();
    for(int i=0;i<size;++i){
        int v=g[u][i];
        if(v==p) continue;
        dfs(v,u,d+1);
    }
}



int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=log2(dep[x]-dep[y]);i>=0;--i){
        if((1<<i)<=dep[x]-dep[y]) x=f[x][i];
    }
    if(x==y) return x;
    for(int i=log2(dep[x]);i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}


int main() {
    cin>>n>>m>>s;
    for(int i=1;i<n;++i){
        cin>>a>>b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(s,s,0);
    while(m--){
        cin>>a>>b;
        cout<<lca(a,b)<<endl;
    }
    system("pause");
    return 0;
}
