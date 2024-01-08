#include <iostream>
#include <math.h>
using namespace std;
//例子
const int N=1e6+10;
int f[N][20];  //20是由log2(n+1)+1算出来的
int n,m;

int query(int l,int r){
//    int x=(int)log(r-l+1)/log(2);
    int x=(int)log2(r-l+1);
    return max(f[l][x],f[r-(1<<x)+1][x]);
}


int main() {
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        int p;
        cin>>p;
        f[i][0]=p;
    }
    //外层循环是遍历列,列不需要遍历到n，而是2的j次方小于等于n
    // 因为f[i][j]代表的是从i开始的2的j次方个元素的最值，因此j最大只能取到log2(n)
    for(int j=1;(1<<j)<=n;++j){
        for(int i=1;i+(1<<j)-1<=n;++i){
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }

    while(m--){
        int x,y;
        cin>>x>>y;
        cout<<query(x,y)<<endl;
    }
    system("pause");
    return 0;
}
