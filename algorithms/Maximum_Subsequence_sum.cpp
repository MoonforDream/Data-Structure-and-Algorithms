#include <iostream>

using namespace std;

//算法1，暴力求解,时间复杂度为O(N?)
int Maxsum(const int an[],int size){
    int maxsum=0;
    for(int i=0;i<size;i++){
        for(int j=i;j<size;j++){
            int thissum=0;
            for(int k=i;k<=j;k++){
                thissum+=an[k];
                if(thissum>maxsum){
                    maxsum=thissum;
                }
            }
        }
    }
    return maxsum;
}

//算法2，微优化，边算边比较，时间复杂度为O(N?)
int Maxsum1(const int an[],int size){
    int maxsum=0;
    for(int i=0;i<size;i++){
        int thissum=0;
        for(int j=i;j<size;j++){
            thissum+=an[j];
            if(thissum>maxsum){
                maxsum=thissum;
            }
        }
    }
    return maxsum;
}


//算法3，分治法求解，时间复杂度为O(nlogn)
int max3(int maxleft,int maxright,int maxcenter){
    int maxsum;
    maxsum=maxleft>maxright?maxleft:maxright;
    maxsum=maxsum>maxcenter?maxsum:maxcenter;
    return maxsum;
}

int maxsubsum(const int an[],int left,int right){
    int maxleftsum,maxrightsum;
    if(left==right){
        if(an[left]>0){
            return an[left];
        }else{
            return 0;
        }
    }
    int center=(left+right)/2;
    maxleftsum= maxsubsum(an,left,center);
    maxrightsum= maxsubsum(an,center+1,right);
    int leftsum=0,maxleft=0;
    for(int i=center;i>=left;i--){
        leftsum+=an[i];
        if(leftsum>maxleft){
            maxleft=leftsum;
        }
    }
    int rightsum=0,maxright=0;
    for(int i=center+1;i<=right;i++){
        rightsum+=an[i];
        if(rightsum>maxright){
            maxright=rightsum;
        }
    }
    return max3(maxleftsum,maxrightsum,maxleft+maxright);
}

int Maxsum2(const int an[],int size){
    return maxsubsum(an,0,size-1);
}


//最简单最快算法，时间复杂度为O(N)
int Maxsum3(const int an[],int size){
    int maxsum=INT_MIN,thissum=0;
    for(int i=0;i<size;i++){
        thissum+=an[i];
        if(thissum>maxsum){
            maxsum=thissum;
        }
        if(thissum<0){
            thissum=0;
        }
    }
    return maxsum;
}

int main() {
    int an[8]={-4,-3,-5,-2,-1,-2,-6,-2};
    int size=sizeof(an)/ sizeof(an[0]);
    int maxsum=Maxsum(an,size);
    int maxsum1= Maxsum1(an,size);
    int maxsum2= Maxsum2(an,size);
    int maxsum3= Maxsum3(an,size);
    cout<<maxsum<<endl;
    cout<<maxsum1<<endl;
    cout<<maxsum2<<endl;
    cout<<maxsum3<<endl;
    system("pause");
    return 0;
}
