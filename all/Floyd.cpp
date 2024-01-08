#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


void Floyd(int n, vector<vector<int>>& edges){
    const int INF=0x3f3f3f3f;
    int dist[n][n];
    memset(dist,INF, sizeof(dist));
    for(int i=0;i<n;++i){
        dist[i][i]=0;
    }
    for(auto edge:edges){
        dist[edge[0]][edge[1]]=edge[2];
        dist[edge[1]][edge[0]]=edge[2];
    }

    //Floyd算法计算全源最短路代码
    for(int k=0;k<n;++k){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
    for(int i=0;i<n;++i){
        cout<<"第"<<i<<"城市到其他城市最短路径：";
        for(int j=0;j<n;++j)
            cout<<"("<<i<<","<<j<<","<<dist[i][j]<<")"<<" ";
        cout<<endl;
    }
}


int main() {
    vector<vector<int>>edges{{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}};
    Floyd(5,edges);
    system("pause");
    return 0;
}
