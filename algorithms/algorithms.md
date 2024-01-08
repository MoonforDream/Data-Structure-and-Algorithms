# 算法



## 最大子序列和求解问题

### 暴力求解

- 直接利用嵌套循环将每次序列和求出来，并跟当前最大序列和比较，得出最大序列和，时间复杂度为*O(n³)*

代码：

```c++
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
```



### 微优化解法

- 将比较部分的循环优化成一个边加边比较的算法，比暴力解法减少一层循环，时间复杂度为*O(n²)*

代码：

```c++
//算法2，微优化，边算边比较，时间复杂度为O(N²)
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
```





### 分治法求解

**分治法概念**：

- 就是将复杂的问题分成小问题，然后解决小问题在通过处理将小问题的解法合并在一起成为大问题的解法。

**最大子序列和的解法**

- 最大子序列和可能出现在三处，分别是**左半部**、**右半部**或者**跨越输入数据的中部**，前两种情况可以递归求解，第三种情况的最大和可以通过求出前半部分的最大和(包含前半部分的最后一个元素)以及后半部分的最大和(包含后半部分的第一个元素)相加得到，前半部分和后半部分的最大和也可以通过进行分成相对应的前后半部分然后求解。该算法的时间复杂度将会降低到*O(nlogn)*

代码：

```c++
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
        return an[left];
    }
    int center=(left+right)>>1;
    maxleftsum= maxsubsum(an,left,center);
    maxrightsum= maxsubsum(an,center+1,right);
    int leftsum=0,maxleft=INT_MIN;
    for(int i=center;i>=left;i--){
        leftsum+=an[i];
        if(leftsum>maxleft){
            maxleft=leftsum;
        }
    }
    int rightsum=0,maxright=INT_MIN;
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
```







### 贪心解法(最快最简单解法)

- 该解法也是一种边加边比较，但是它只有一层循环，它的本质就是通过每次相加然后在比较的同时，当他的当前sum不大于最大sum时，并且该sum<0则我们将它归0，这样进行求解序列和时，就能保证它能主动找到正数和，正数和是最有可能成为最大序列和的，该算法的时间复杂度为*O(n)*

代码：

```c++
//最简单最快算法，时间复杂度为O(N)
int Maxsum3(int an[],int size){
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

//这个代码虽多，但比上面的节约了一些时间。
int Maxsum3(int nums[],int size){
    int maxsum=0,thissum=0,cnt=0,msum=0;
    for(int i=0;i<size;i++){
        if(nums[i]<0){
            if(cnt==0){
                mnum=nums[i];
            }else if(nums[i]>msum){
                msum=nums[i];
            }
            cnt++;
        }
    }
    for(int i=0;i<size;i++){
        thissum+=nums[i];
        if(thissum>maxsum){
            maxsum=thissum;
        }else if(thissum<0){
            thissum=0;
        }
    }
    if(cnt==size&&maxsum==0){
        maxsum=msum;
    }
    return maxsum;
}
```









## 二分查找

**概念**：

- **针对于已经预先排序好的数据**，每次将数据进行对半查找，然后看它中间的数据是否是要找的，如果是就返回中间位置，不是就判断该数据是在前半部分还是后半部，然后在进而取其中部，看其是否找到，然后如果还没找到就一直重复操作，直到找到为止，该算法时间复杂度为*O(logn)*



代码：

```c++
int BinarySearch(const ElementType A[],ElementType X,int N){
    int Low=0,Mid,High=N-1;
    while(Low<=High){
        Mid=(Low+High)/2;
        if(A[Mid]<X){
            Low=Mid+1;
        }else if(A[Mid]>X){
            High=Mid-1;
        }else{
            return Mid;
        }
    }
    return -1;//未找到指定数据
}
```







## 欧几里德算法

**概念**：

- 用于求两个数的**最大公约数**(两个数都可以共同整除的最大数)，利用不断相互取余，直到其中一个余数为0，则最大公约数为不为0的余数，该算法的时间复杂度为*O(logn)*



代码：

```c++
unsigned int gcd(unsigned int M,unsigned int N){
    unsigned int Rem;
    while(N>0){
        Rem=M%N;
        M=N;
        N=Rem;
    }
    return M;
}

//递归版(简洁)
int gcd(int a,int b){
    return !b ? a:gcd(b,a%b);
}
```







## 快速幂算法

**概念**：

- 计算X<sup>N</sup>的最常见的算法是使用N-1次乘法自乘，但是可以使用一种将**利用分治思想跟递归结合的算法**更好，效率更高。判断N是偶数还是奇数，如果是偶数的话，我们有X<sup>N</sup>=X<sup>N/2</sup>\*X<sup>N/2</sup>，如果为奇数，我们有X<sup>N</sup>=X<sup>(N-1)/2</sup>\*X<sup>(N-1)/2</sup>\*X，然后在不断的递归并将N等于0和N等于1为递归的基准情形，当N等于1返回X，该算法的时间复杂度为*O(logn)*



代码：

- **递归**：

```c++
long int Pow(long int X,long int N){
    if(N==0)
        return 1;
    if(N==1)
        return X;
    if(X%2==0){
        return Pow(X*X,N/2);
    }else{
        return Pow(X*X,N/2)*X;
    }
}
```

- **非递归**：

```c++
//有些题目数字过大防止溢出会对结果取模
long long quickpow(long long a,long long b,int mod){
    long long res=1;
    if(b==0) return 1;
    while(b){
        //b为奇数
        if(b%2==1){
            res=res*a%mod;
        }
        b/=2;
        a=a*a%mod;
    }
    return res;
}
```

- **位运算加速**：假设我们要求a的11次方那么他会分解成8+2+1，那如何将其分解成8+2+1的情况，我们**可以将其转换成二进制**，11的二进制为1011，11=1*2<sup>3</sup>+0\*2<sup>2</sup>+1\*<sup>1</sup>+1\*2<sup>0</sup>，这样**我们每次取11的二进制的最后一位这样就能分解成8+2+1了**。

  ```c++
  long long quickpow(long long a,long long b,int mod){
      long long res=1;
      if(b==0) return 1;
      while(b){
          //b&1就可以等价于b%2==1，如果b为偶数b&1==0，为奇数b&1==1
          if(b&1){
              res=res*a%mod;
          }
          b>>=1;  //等价于b/=2
          a=a*a%mod;
      }
      return res;
  }
  ```

  





## 排序算法

**概念**：

- 我们在的排序工作能**在主存中**完成的，我们就叫这种算法叫做**内部排序**
- 不能在主存中完成而必须**在磁盘或磁带上完成**的排序算法叫做**外部排序**









### 冒泡排序

**概念**：

- **冒泡排序**是一个很简单的排序算法，冒泡排序是**比较相邻的元素**，如果第一个比第二个大，就交换他们两个，对每一对相邻元素做同样的工作，执行完毕后，找到第一个最大值，重复以上步骤，**每次比较次数-1**，直到不需要比较为止。
- *冒泡排序是一种每一轮排序遍历时，抛出当前遍历时的最大值来进行一个到最后升序的排序方法*
- 冒泡排序的时间复杂度为*O(n²)*



**注意事项**：

- 冒泡排序的时间复杂度不是很好，有时候数据量大就应该考虑其他线性时间复杂度的排序算法





**实现代码：**

```c++
//比较相邻的元素，如果第一个比第二个大，就交换他们两个
//对每一对相邻元素做同样的工作，执行完毕后，找到第一个最大值
//重复以上步骤，每次比较次数-1，直到不需要比较


//冒泡排序,升序排序
void bubbleSort(int an[],int len){
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len-1-i;j++){
            if(an[j]>an[j+1]){
                int temp=an[j+1];
                an[j+1]=an[j];
                an[j]=temp;
            }
        }
    }
}
```









### 插入排序

**概念**：

- **插入排序(insertsort)**：插入排序是一个**基于比较移动数据**来实现有序化的算法，*时间复杂度为O(N²)*
- 插入排序**根据元素的个数N进行N-1趟排序**，从**第一趟开始**，在**第P趟**，我们将**数组索引第P位的元素或者元素位于第P+1位置上的元素与该元素前面的所有元素进行比较**，比较后**找到**该元素存在的**对应位置进行移动或者叫做插入(不是交换)**
- 第P趟结束，无序的数组或者数据则变成有序化了。





代码：

```c++
//插入排序
void insertsort(int *an,int len){
    for(int i=1;i<len;i++){
        int temp=an[i];
        int j;
        for(j=i;j>0&&an[j-1]>temp;j--){
            an[j]=an[j-1];
        }
        an[j]=temp;
    }
}
```















### 希尔排序

**概念**：

- **希尔排序(shellsort)**是**基于插入排序所优化的算法**，该算法**依靠增量序列来使到减少相邻元素交换排序的机会以及减少排序执行的趟次**，这将比插入排序所花费的**时间减少**，即使希尔排序的*时间复杂度也为O(N²)*
- 关于**增量序列h**，我们将数组的所有元素，**按照索引号i,i+h,i+2h....(在数组索引范围0-N-1之内)作为一个序列进行排序**，而这个**排序是按照序列内的索引号排序**因此不会影响到其他索引号的排序，而形成**增量序列的h的选取可以自定义**，但是**希尔建议使用h1=(N-1)/2,h2=h1/2直到hk=1的方式进行形成增量序列(但不是很好)。**
- 例如：一个无序数组的元素有12个，则排序该数组需要三趟，h(根据数组最大索引号也就是11除以2取得h1)分别为5，2，1，因此在以5为增量的趟次中，0，5，10为一个序列并将对应号上的元素进行插入排序，1，6，11又为1个序列进行排序。

![image-20230727192100476](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230727192100476.png)





代码：

- **使用Sedgewick增量作为希尔排序序列的时间复杂度为O(N<sup>7/6</sup>)**

```c++
//希尔排序
void shellsort(int *an,int len){
    for(int i=(len-1)/2;i>0;i/=2){
        //插入排序
        for(int j=i;j<len;j++){
            int temp=an[j],k;
            //根据增量i进行分序列排序
            for(k=j;k>=i&&temp<an[k-i];k-=i){
                an[k]=an[k-i];
            }
            an[k]=temp;
        }
    }
}

//使用Sedgewick增量的希尔排序
void shellsort_pro(int* an,int len){
    /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
    int Sedgewick[] = {260609,146305,64769,36289,
                       16001,8929,3905,2161,929, 505,
                       209, 109, 41, 19, 5, 1, 0};
    int k;
    for(k=0;Sedgewick[k]>=len;k++);
    for(int d=Sedgewick[k];d>0;d=Sedgewick[++k]){
        for(int i=d;i<len;i++){
            int temp=an[i];
            int j;
            for(j=i;j>=d&&an[j-d]>temp;j-=d){
                an[j]=an[j-d];
            }
            an[j]=temp;
        }
    }
}
```















### 堆排序

**概念**：

- 堆排序(heapsort)：是一个**基于二叉堆的排序算法**,但是他又跟二叉堆的不一样，二叉堆的数组索引为0的是个哑节点，但是**堆排序是得从0开始的**
- 堆排序的实现需要根据要实现顺序的方式，**将无序的数组在原数组下重新构建成大根堆/小根堆数组**，如果要实现**升序**，就需要**构建成大根堆**，实现**降序**，就需要**构建成小根堆数组**。**构建完**堆数组，然后**以类似堆中操作删除最大元/最小元的方式，将数组实现有序**。
- **构建堆(以升序为例)**：我们需要**拿取数组元素个数N**，**从(N-1)/2到0遍历(拿取堆中的根节点)**，**遍历时拿取该根节点的子节点中的最大值**，如果**最大值大于根节点，就进行根节点与该最大值交换**，**遍历完毕后就形成了大根堆**
- **删除最大/最小元(以升序为例)**：要实现升序，则需要拿取数组元素个数N并**执行从N-1到1次的删除最大元操作**，而最大元就是大根堆数组中的第一位元素，在遍历到索引号为i时，我们需要**将最大元与数组索引号为N-i-1的元素进行交换**，然后**重新构建最大堆保证堆数组的第一位元素就是最大元**，跟**遍历完毕就得到升序的数组**，反之就得到降序的数组。





代码：

```c++
#define leftchild(i) (2*(i)+1)    //定义宏函数，找到根节点的左孩子

//构建堆
void buildheap(int* an,int len,int index){
    int temp,child;
    for(temp=an[index];leftchild(index)<len;index=child){
        child=leftchild(index);
        if(child!=len-1&&an[child+1]>an[child]){
            child++;
        }
        if(an[child]>temp){
            an[index]=an[child];
        }else{
            break;
        }
    }
    an[index]=temp;
}

//堆排序
void heapsort(int* an,int len){
    for(int i=(len-1)/2;i>=0;i--){
        buildheap(an,len,i);
    }
    for(int i=len-1;i>0;i--){
        int temp=an[0];
        an[0]=an[i];
        an[i]=temp;
        buildheap(an,i,0);
    }
}
```

















### 归并排序

**概念**：

- **归并排序(mergesort)**：是基于**递归和分治策略**的排序算法，*其时间复杂度为O(nlogn)*，但是归并排序不利于主存内排序，因为合并数组需要线性附加内存，如果N很大，则需要的表很大。
- 归并算法是将一个无序要排序的数组，将其分半，然后**用递归，将数组一次次分半**，然后利用**递归到**最后一层也就是**数组无法再分了**，**递归返回时，开辟一个新数组，就用合并的操作将其有序的放入新数组**，最后递归完毕就会得到一个有序的数组了。



**合并操作**：

- 对于某一个**合并操作**来讲(以合成升序数组为例，**两个数组前提是要有序的**)，我们将数组分成了A，B两个数组(**其实并没有分成两个，只是用lpos，rpos记录这两个数组在原来数组的起始位置**)，用**leftend，rightend记录两个数组结尾的数组索引**，然后我们**开辟一个能存下A和B数组两个数组元素的数组**
- 然后，我们**将lpos位置的元素跟rpos位置的元素比较**，**哪个小就放进tempos位置上的新数组temarr中**，如果**lpos位置小**，则将**lpos位置元素赋值到temarr中的tempos位置上，tempos和lpos++，然后lpos++完的位置上的元素再跟rpos比较，重复之前操作**。
- **直到一个数组元素全部赋值完后，如果另一个数组还有剩下元素，则将剩下的数组赋值到temarr中，则合并操作就结束了。**



代码：

```c++
//合并操作
void merge(int*an,int *temarr,int lpos,int rpos,int rightend){
    int leftend=rpos-1;
    int nums=(rightend-lpos)+1;
    int tempos=lpos;
    //进行比较lpos和rpos位上的元素
    while (lpos<=leftend&&rpos<=rightend){
        if(an[lpos]<an[rpos]){
            temarr[tempos++]=an[lpos++];
        }else{
            temarr[tempos++]=an[rpos++];
        }
    }
    while (lpos<=leftend){       //处理left数组的剩余元素
        temarr[tempos++]=an[lpos++];
    }
    while (rpos<=rightend){     //处理right数组的剩余元素
        temarr[tempos++]=an[rpos++];
    }
    //使用rightend保证给an数组赋值的正确位置
    for(int i=0;i<nums;i++,rightend--){
        an[rightend]=temarr[rightend];
    }
}


//递归分治调用
void midsort(int* an,int *temarr,int left,int right){
    if(left<right){
        int center=(left+right)/2;
        midsort(an,temarr,left,center);
        midsort(an,temarr,center+1,right);
        merge(an,temarr,left,center+1,right);
    }
}

//归并排序
void mergesort(int *an,int len){
    int *temarr=new int[len];
    midsort(an,temarr,0,len-1);
}
```















### 快速排序

**概念**：

- **快速排序(quicksort)**：也是一种分治的递归算法，时间复杂度为*O(nlogn)*，是实践中最快的已知排序算法

- 对数组S的快速排序的具体操作是：

  > 1. 如果S中元素个数为0或1，则直接返回该数组
  > 2. 取S中任一元素v，称之为**枢纽元(pivot)**
  > 3. 将S-{v}(S中除去v的其余元素)分成两个不想交的集合：S<sub>1</sub>={x∈S-{v}|x<=v}和S<sub>2</sub>={x∈S-{v}|x>=v}.(这个操作就是分治操作，不断地递归取枢纽元将其分割为一个个小集合进行排序)
  > 4. 返回{quicksort(S<sub>1</sub>)后，继随v，继而quicksort(S<sub>2</sub>)}

- 对于元素**小于等于20的数组**我们成为小数组，当数组为小数组时，**快速排序不如插入排序好**，这种情况下**使用插入排序而不是使用递归的快速排序，将会节省大约15%的运行时间(相对于自始至终使用快速排序)**





**选取枢纽元**：

1. **随机选取法**：一个**比较安全**的选取方法，**通过使用随机数生成器进行随机产生枢纽元v**，因为随机的枢纽元不可能总在接连不断地产生劣质的分割。但是随机数的生成时间比较长，**无法降低算法的平均运行时间**
2. **三数中值分割法**：一个**比较好**的选取方法，我们**使用数组的左端、右端和中心位置上的三个元素的中间值(就是排序后第二大的元素)作为枢纽元v**。使用该选取方法**消除了预排序输入的坏情形**，并且**减少了快速排序大约5%的运行时间**



**分割策略**：

- 当数组中的**元素互异**时，在分割阶段，我们**将枢纽元跟数组最右端的元素进行交换**，让枢纽元离开分区域内。我们需要**将小于枢纽元和大于枢纽元的元素分布在区域的左右边。**
- 利用**i指向最左边的元素**，**j指向倒数第二个位置(也就是交换后枢纽元的左边位置)**，如果**i指向的元素小于枢纽元，i就向右移动**，如果**j指向的元素大于枢纽元，j就向左边移动**，直到**当i指向的位置不小于枢纽元，j指向的位置不大于枢纽元，就将i，j位置上的元素交换，但不交换i，j，交换完各自向右向左移动一位**。
- 重复上述的操作，**直到i和j交错**，也就是当i在j的右边一位，j在i的左边一位的时候，**不进行移动与交换**，然后**将枢纽元指向的元素和i所指的元素进行交换**
- 对于**i或者j指向元素跟枢纽元相等**时，**i和j停止移动进行交换位置上的元素，然后各自向右向左移动一位。**









代码：

- **在实际操作中**，我们在选取枢纽元的操作中，已经将**left，center，right位置上的元素排好序**了，而**right位置上的元素本身就比枢纽元大**，我们**不直接交换center和right位置上的元素，而是交换center跟right-1上的元素，这样将会为后面根据枢纽元分割区域中少比较一位。**优化了算法的性能

```c++
void insertsort(int* an,int low,int high){
    for(int i=low+1;i<=high;i++){
        int temp=an[i];
        int j;
        for(j=i;j>0&&an[j-1]>temp;j--){
            an[j]=an[j-1];
        }
        an[j]=temp;
    }
}

//三数中值分割法选取枢纽元
int midian3(int *an,int left,int right){
    int center=(left+right)/2;
    if(an[left]>an[center]){
        swap(an[left],an[center]);
    }
    if(an[left]>an[right]){
        swap(an[left],an[right]);
    }
    if(an[center]>an[right]){
        swap(an[center],an[right]);
    }
    //因为上述操作已经满足an[left]<an[center]<an[right]，an[right]大于枢纽元，我不需要进行交换让其在比较一位
    //因此让枢纽元跟right-1位置交换，这样在排序时减轻了右边数组的压力
    swap(an[center],an[right-1]);
    return an[right-1];   //返回枢纽元
}

void Qsort(int* an,int left,int right){
    if(left+10<=right){
        int pivot=midian3(an,left,right);
        int i=left,j=right-1;
        for(;;){
            while (an[++i]<pivot){}
            while (an[--j]>pivot){}
            if(i<j){
                swap(an[i],an[j]);
            }else{
                break;
            }
        }
        swap(an[i],an[right-1]);
        Qsort(an,left,i-1);
        Qsort(an,i+1,right);
    }
    else{
        insertsort(an,left,right);
    }
}

//快速排序
void quicksort(int *an,int len){
    Qsort(an,0,len-1);
}
```







- 另一种快速排序，**每一次递归，我们将数组最左端就当作枢纽元**，还是**左端left开始跟right指向的元素跟枢纽元的值比较**，an[left]<枢纽元left++，an[right]>枢纽元right--，**直到找到an[left]>枢纽元，an[right]<枢纽元的时候进行交换an[left]和an[right]**，**直到left==right，就将枢纽元(也就是最左端的元素)与left当前所在位置进行交换**，使得枢纽元放在正确的位置，然后在**以left为界限分治。**

  ```c++
  void quicksort(int *an,int low,int high){
      int left=low,right=high;
      if(left<high) return;
      int temp=an[left];   //枢纽元
      while(left!=right){
          //找寻右边区域小于枢纽元的元素位置
          while(an[right]>=temp&&left<right){
              right--;
          }
          //找寻左边区域大于枢纽元的元素位置
          while(an[left]<=temp&&left<right){
              left++;
          }
          //将找到的进行交换使得左边区域小于枢纽元，右边区域大于枢纽元
          if(left<right){
              swap(an[left],an[right]);
          }
      }
      //将枢纽元换到正确的中间区域
      swap(an[low],an[left]);
      //以left也就是当前枢纽元所在位置为界限进行分治
      quicksort(an,low,left-1);
      quicksort(an,left+1,high);
  }
  ```

  













### 桶式排序

**概念**:

- **桶排序(Bucket sort)**：桶排序是一个**非比较排序方法**，它的排序是**典型的用空间换时间的方法**，它的时间复杂度甚至可能是线性复杂度(*O(n)*)。如果我们有N个**整数**，数的大小范围为1~M(或者0~M-1),就可以根据数据大小范围创建一个空桶(可以看作数组)或者多个空桶，然后将数据分桶后，就可以将这些数据从头到尾输出，输出完就会发现数据已经排好序了！时间复杂度为*O(M+N)*



**注意事项**：

- 该类算法是典型的空间换时间，要注意空间的开销
- 该类算法排序的对象必须是整数，如果是浮点数和自定义类数据比较，就无法使用该类排序方法。
- 分完桶之后，排序的算法自行选择
- 分桶规则，根据数据自定义映射规则。





#### 计数排序

**概念**：

- 假设要排序的数据为N个整数，数的大小范围为0~M-1,我们就创建一个空桶(数组)，数组的长度为该数据的最大值(**将每一个元素看作是数组的下标,例如元素1就放在数组a[1]中**)，数组的值全部初始化为0，然后利用循环如果出现一个元素，就将其对应数组的下标中的数据+1(例如有数据中1出现了两次，则a[1]==2)，然后再将根据排序方式将数组元素顺序/逆序打印，对应数组下标的值为多少就打印几次。该排序方法时间复杂度为*O(n)*。



**注意事项**：

- 元素一定要为整数且为正数！



代码：

```c++
//计数排序
void CountSort(int *an,int len) {
    int max=an[0];
    for(int i=0;i<len;i++){
        if(an[i]>max){
            max=an[i];
        }
    }
    int arr[max+1];
    memset(arr,0,sizeof(int)*(max+1));
    for(int i=0;i<len;i++){
        arr[an[i]]++;
    }
    int j=0;
    for(int i=0;i<max+1;i++){
        while (arr[i]>0){
            an[j]=i;
            arr[i]--;
            j++;
        }
    }
}

```









#### 基数排序

**概念**：

- 当数据范围过大的时候，如果使用桶排序则需要创建的空桶太多了，因此我们使用**多趟桶式排序**---我们将会用**最低(有效)位**优先的方式进行桶式排序。
- 首先我们得先**创建一个0-9的桶(线性表)**，我们将会将数据分趟次(根据数据最大数的位次)排序，第一次就以**每个数据的最低位排序**依次放到其最低位对应的桶中，例如：数据231就放在数组a[2]中，然后再根据**次低位**进行第二趟排序，如果只有一位数的数据就根据第一趟排序的顺序依次放在第0位的桶中，然后如果还有百位的数据则就继续第三趟排序。
- 时间复杂度为*O(n)*



**注意事项**：

- 数据一定得是整数。
- **如果数据出现负数，则需要数组每个元素先加上最小值的绝对值，然后排序完后再减去最小值的绝对值就能实现负数也能排序。**
- 该算法是基于计数排序的，所以会使用到计数排序的排序方法



![image-20230704203814374](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230704203814374.png)





代码：

```c++
void countsort(int *an,int len,int exp){
    int count[10]={0};  //计数数组
    int ret[len];  //结果数组
    for(int i=0;i<len;i++){
        count[(an[i]/exp)%10]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    //这个地方需要从尾遍历到头，因为如果从头遍历到尾时，我们就无法确定前面出现的数的正确位置！！！
    for(int i=len-1;i>=0;i--){
        ret[count[(an[i]/exp)%10]-1]=an[i];
        count[(an[i]/exp)%10]--;
    }
    for(int i=0;i<len;i++){
        an[i]=ret[i];
    }
}

void RadixSort(int *an,int len){
    int max=an[0];
    for(int i=1;i<len;i++){
        if(an[i]>max){
            max=an[i];
        }
    }
    //通过最大数的位数对数据分趟桶式排序
    for(int k=1;max/k>0;k*=10){
        countsort(an,len,k);
    }
}
```





**能够对负数排序的改进基数排序代码：**

```c++
//基数排序
void countsort(int *an,int len,int exp){
    int count[10]={0};  //计数数组
    int ret[len];  //结果数组
    for(int i=0;i<len;i++){
        count[(an[i]/exp)%10]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    //这个地方需要从尾遍历到头，因为如果从头遍历到尾时，我们就无法确定前面出现的数的正确位置！！！
    for(int i=len-1;i>=0;i--){
        ret[count[(an[i]/exp)%10]-1]=an[i];
        count[(an[i]/exp)%10]--;
    }
    for(int i=0;i<len;i++){
        an[i]=ret[i];
    }
}

void RadixSort(int *an,int len){
    int max=an[0];
    int min=an[0];
    for(int i=1;i<len;i++){
        if(an[i]>max){
            max=an[i];
        }
        if(an[i]<min){
            min=an[i];
        }
    }
    for(int i=0;i<len;i++){
        an[i]+=abs(min);
    }
    //根据位数进行分趟桶式排序
    for(int k=1;max/k>0;k*=10){
        countsort(an,len,k);
    }
    for(int i=0;i<len;i++){
        an[i]-=abs(min);
    }
}
```

















## 图论算法



### 拓扑排序

**概念**：

- 拓扑排序是对有向无圈图的顶点的一种排序。排序不必是唯一的，任何合理的排序都是可以的。
- 具体做法是：先**找出任意一个没有入边的顶点v**(就是没有其他顶点指向的顶点)，**将顶点v放入队列**，然后**将顶点v和它邻接的边从图中删除**(其实就是将顶点v指向的顶点的入边数都-1，这样就可以代表删除边了)，然后**用数组topnum来记录该顶点的排序位置**。然后**重复上述操作**。顶点v的**入度(indegree)为边(u,v)的条数**。并**用indegree数组来存储每个顶点的入度值**。如果**不存在入度为0的顶点，则该图是个有圈图。**





代码：

```c++
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
```















### 最短路径算法

**概念**：

- 考查最短路径问题，可能会输入一个**赋权图(也就是边带有权的图)**，则一条路径的**v1v2..vN的值就是对路径的边的权求和**，这叫做**赋权路径长**，如果是**无权路径长就是单纯的路径上的边数**。

- 在赋权图，可能会出现负值边的情况，这样当我们去找最短路径时，可能会产生负值圈，毕竟一直走负值边可以将数值变得更短。

  





**单源最短路径问题**：

- 给定一个赋权图G=(V,E)和一个特定顶点s作为输入，找出从s到G中每一个其他顶点的最短赋权路径。





**无权最短路径**：

- 给定一个无权图G=(V,E)和一个起始顶点s作为输入，找出从s到G中每一个其他顶点的最短路径。

#### 广度优先搜索算法(BFS)

**概念**：

- **广度优先搜索算法(BFS)**用于在**无权图或者边权相同的图中寻找最短路径。**
- 该方法**按层处理顶点**，首先**从起始点出发**，进行**发散找到与起始点邻接的顶点a,...**，并**将s到这些顶点的路径距离更新**，然后**将该点标记成已经访问的顶点并将该点的前一个顶点记录下来(被标记的顶点我们后面遇到就认为该点已经不需要再进行处理了)**，然后**再从顶点a,...发散**，找**到该顶点的邻接顶点，然后重复操作**，**直到所有顶点都被标记完**，就完成了搜索。
- **具体代码实现**，是**用一个队列**，在**迭代开始**时，**队列中只含有距离为迭代距离currdist的那些顶点**，然后**执行操作时，将距离currdist+1的顶点的那些顶点添加到队列中**，只要当前距离为currdist顶点处理完，就会处理距离为currdist+1(也就是当前顶点发散的顶点)的顶点添加到队列中。
- 在队列中其实**可以将know域也就是标记去掉**，因为队列的形式已经说明执行过了，就不会在执行，因此相当于标记了。





代码：

```c++
//图的邻接表的结点信息
struct listnode{
    int data;
    bool flag;    //判断是否访问过
    int path;     //存储上一个顶点
    int dist;     //距离
    listnode* next;
};

//图的信息
class graph{
private:
    listnode *an;   //邻接表形式存储图
    int vnum;     //图中结点数
};

//s为起点，an数组的邻接表表示图
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
```









#### Dijkstra算法

**概念**：

- 用于**求解赋权图的最短路径(无负值边)**，Dijkstra算法是**解决单源最短路径问题的一般方法，**并且该**解法是贪心算法**。Dijkstra只是BFS的升级版使他能够求赋权图的最短路径，如果求无权图Dijkstra跟BFS的做法一样！
- Dijkstra算法是**分阶段**的，该算法认为**每一个阶段，都将该阶段当作最好的情况处理**，类似于BFS算法，但是还是有不同的地方，比起BFS多出了需要进行每个阶段出现最好情况就进行更新路径。
- 具体做法是，从图中**选取起始点v**，然后**找出邻接点**，并**将当前起始点到邻接点v3,v4...的距离更新**，如果是**赋权图就是dv+C<sub>v,v3</sub>(就是顶点v到v3的权)**，如果是**无权就是dv+1**，并**将v标记为已知**。然后**选取邻接点集中的一点再做为起始点**，然后**重复操作**，将当前顶点的前一个顶点记录。当**v到某个顶点的距离在当前阶段是最小的(最好情况)**，那么**就进行更新**，如果**不是就无需更新**。
- 具体来说，当我们扩展一个新结点时，我们会考虑它的所有未访问过的邻接结点，并计算从起始结点经过当前结点到达邻接结点的路径长度。如果这个长度小于已知的最短路径长度（或者邻接结点的路径长度尚未初始化），我们就更新邻接结点的路径长度。这样做的目的是通过不断更新路径长度来找到起始结点到所有其他结点的最短路径。
- 实现的时候可以使用优先队列来进行优化算法，只将顶点和其最短路径值进入队列中当队列非空，执行以下操作：**u等于队顶的节点**，**w等于队顶节点的最短路径值**；**遍历u的所有边，如果能找到节点v最短路径值小于v的当前值，更新v，将v压入队列**。结束
- **没有用优先队列**优化的Dijkstra算法的**时间复杂度为O(N²)**，如果**使用优先队列**，则**时间复杂度为O(nlogn)**，可以不用考虑已知域;



**Dijkstra跟BFS区别：**

1. **处理顶点**：
   - 在**BFS算法**中，当一个**顶点被扩展**时，它的**所有未访问过的邻居顶点都被添加到队列中**，这样它们将按照遍历的顺序逐个被访问。
   - 在**Dijkstra算法**中，当一个**顶点被扩展**时，它的**邻居顶点也被考虑**，但是Dijkstra算法会计算扩展的顶点与其邻居之间的边的权重，并根据这个权重来更新到达邻居顶点的最短路径长度。这个更新过程使得Dijkstra算法能够处理带有非负权重的图。
2. **选择下一个顶点**：
   - 在**BFS算法**中，**下一个要被扩展的顶点是队列中的下一个顶点**，也就是按照队列的先进先出（FIFO）原则选择。
   - 在**Dijkstra算法**中，**下一个要被扩展的顶点是距离起始点路径长度最小的顶点**，也就是根据已知的最短路径长度来选择。这需要使用优先队列或者最小堆来高效地选择路径长度最小的顶点。





代码：

```c++
//图的邻接表的结点信息
struct listnode{
    int data;
    int path;     //存储上一个顶点
    int dist;     //最短距离
    int weight;   //数组索引顶点跟该顶点的边的权重
    listnode* next;
};

//图的信息
class graph{
private:
    listnode *an;   //邻接表形式存储图
    int vnum;     //图中结点数
};

//v是起始点
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
                    q.push(p->data);
                }
                p=p->next;
            }
        }
    }
```















#### Floyd算法



**概念**：

- Floyd(弗洛伊德)算法是**基于动态规划思想**的算法，也称**插点法**，是**全源最短路算法**(全源就代表经过一次Floyd算法，每个点到各个点的最短路径都能算出来)
- 用于求任意一对顶点间的最短路径，此时图中的**边的权值可以出现负数，但不能出现负环**
- 时间复杂度为`O(n³)`，n为点个数









**基本思想**：

1. 对于从i到j的弧，进行n次试探
2. 首先考虑i，0，j是否存在，如果存在，则比较i，j和i，0，j的路径长度，去最短者进行更新i，j的最短路径
3. 然后再添加顶点1，依次类推。





**具体过程**：

1. 当一个图里有**n个城市**，求全源最短路径问题
2. 定义**城市k为从当前图拿出来，并重新插入图中的城市**，`城市i`，`城市j`分别为当前`源城市`和`目的城市`。`dist[i\][j]表示城市i到城市j的最短路径`
3. 假设当前图中没有城市k，我们**将城市k重新插入到图中**
4. 我们需要判断城市i到城市j的最短路径是否要更新，则**比较路径经过城市k和原来的路径长度进行比较**，如果**经过城市k的路径长度更短，则更新dist[i\][j]**，因此就为`dist[i][j]=min(dist[i][k]+dist[k][j],dist[i][j])`
5. 因此对这个图**执行n次上述操作(也就是插点法)**，得出的dist二维数组就为全源的最短路径。





**代码模板**：

```c++
//dist[n][n]用来记录图中各点到各点的最短路径
void Floyd(int **dist){
    for(int k=0;k<n;++k){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
}
```







**例题部分代码**：

具体可看力扣[1334. 阈值距离内邻居最少的城市](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)，只包含求解全源最短路径代码

```c++
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
```





























### 最小生成树

**概念**：

- **最小生成树**是一颗**连接图G所有顶点的边构成的一颗权最小的树**，**最小生成树一般是在无向图中寻找。**
- 最小生成树**共有N-1条边(N为顶点数)**。





**算法**：

#### Prim算法

**概念**：

- Prim(普里姆)算法是生成最小生成树的一种算法，该算法基本上和求最短路径的Dijkstra算法一样
- 具体操作：**选取一个顶点作为树的根节点v1**，然后**从这个顶点发散**，找到其**邻接顶点(加入队列中)**，然后**选取根节点到邻接顶点中权最小的路径**(也就是连接该路径的另一个顶点)进行**添加到树中(也将连接的顶点除去v1的顶点的邻接顶点加入队列中)**，然后初步**形成一个图为u**，然后再**按顺序的查找图u与队列中的顶点的最小路径并加入树中**，重复操作。
- 最小生成树信息打印，**打印树中边的顶点对组**。



实现代码：

`使用优先队列`

```c++
void Prim(int v){
        an[v].dist=0;
        //使用优先队列,定义参数<数据类型，容器类型，比较方法>
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
        //pair<int,int>对组的第一个为权，第二个为顶点。
        q.push(make_pair(0,v));
        while (!q.empty()){
            int w=q.top().second;
            q.pop();
            listnode* p=an[w].next;
            if(an[w].flag) continue;
            while (p!= nullptr){
                //选取最小权的边而不是顶点到顶点的最短距离
                if(p->weight<an[p->data].dist&&!an[p->data].flag){
                    an[p->data].dist=p->weight;
                    an[p->data].path=w;
                    q.push(make_pair(p->weight,p->data));
                }
                p=p->next;
            }
            an[w].flag= true;
        }
        int w=0;     //记录最小生成树的总权
        for(int i=1;i<=vnum;i++){
            if(an[i].path!=0){
                if(i>an[i].path)
                    cout<<"("<<an[i].path<<","<<i<<")"<<" 权:"<<an[i].dist<<endl;
                else
                    cout<<"("<<i<<","<<an[i].path<<")"<<" 权:"<<an[i].dist<<endl;
                w+=an[i].dist;
            }
        }
        cout<<"总权:"<<w;
        cout<<endl;
    }
```





`使用vector容器模拟优先队列`

```c++
struct edge{
    int v;    //顶点
    int weight;   //权
};
static bool cmp(const edge &a,const edge &b){
        return b.weight<a.weight;
    }
    void Prim(int v){
        an[v].dist=0;
        vector<edge>q;
        q.push_back({v,0});
        while (!q.empty()){
            sort(q.begin(),q.end(),cmp);
            int w=q.back().v;
            q.pop_back();
            listnode* p=an[w].next;
            if(an[w].flag) continue;
            while (p!= nullptr){
                //选取最小权的边而不是顶点到顶点的最短距离
                if(p->weight<an[p->data].dist&&!an[p->data].flag){
                    an[p->data].dist=p->weight;
                    an[p->data].path=w;
                    q.push_back({p->data,p->weight});
                }
                p=p->next;
            }
            an[w].flag= true;
        }
        int w=0;     //记录最小生成树的总权
        for(int i=1;i<=vnum;i++){
            if(an[i].path!=0){
                if(i>an[i].path)
                    cout<<"("<<an[i].path<<","<<i<<")"<<" 权:"<<an[i].dist<<endl;
                else
                    cout<<"("<<i<<","<<an[i].path<<")"<<" 权:"<<an[i].dist<<endl;
                w+=an[i].dist;
            }
        }
        cout<<"总权:"<<w;
        cout<<endl;
    }
```















#### Kruskal算法

**概念**：

- Kruskal(克鲁斯卡尔)算法是连续地按照最小的权选择边，并且当所选的边不产生圈时就把它作为最小生成树中的边。
- 该算法是在处理一个森林--树的集合。开始的时候，存在|V|棵单节点树，而添加一边则将两棵树合并成一颗树。当算法终止时，就只有一棵树，就是最小生成树。



##### 并查集

- 并：合并，查：查询连通关系，集：形成集合，**用于处理连通性问题**。

- 并查集：**集合中的元素组织成树的形式**：

1. **查找两个元素是否属于同一集合**：所在树的根结点是否相同

2. **合并两个集合**——将一个集合的根结点作为另一个集合根结点的孩子



**具体操作**：

- 该算法是根据**选取边**来进行生成最小生成树，那么我们就**将图的信息用一个边集结构表示**，我们**需要进行一个循环，循环条件就是当最小生成树的边达到N-1条时就退出(N为元素个数)**，每**次循环我们都需要选取最小权重的边**，并且**判断在树中加入这条边会不会形成圈**，如果**形成圈就不进行加入**，直到树的边条数达到N-1就形成了最小生成树。
- 该算法的关键是**判断在树中加入边会不会形成圈--也就是判断两个顶点是否位于两个连通分量**，这就需要**并查集**的操作：在图中我们**将每个顶点都当作一个集合**，我们**插入边**的时候，直接**判断这两个顶点是否处于一个集合中**，如何是**一个集合就不进行加入**，如果**不是一个集合，就需要将两个集合进行合并**，那么这**就需要一个存储每个节点的根(父亲)节点的数组parent**。我们将parent每个连通分量(集合)进行初始化为-1，表示没有父亲。



实现代码：

```c++
struct edge{
    int u,v,w;  //u，v为顶点的，w为权重,u为起始点，v为终点
};

static bool cmp(const edge &a,const edge &b){
        return a.w<b.w;
    }
    int findroot(int v,int parent[]){
        int t=v;
        while (parent[t]>-1){    //查找该集合的根节点。
            t=parent[t];
        }
        return t;
    }
    void Kruskal(int v){
        vector<edge>q;
        //存储每个连通变量的父亲节点的数组
        int parent[vnum+1];
        int w=0;     //记录最小生成树的总权
        memset(parent,-1, sizeof(int)*(vnum+1));
        //生成边集数组。
        for(int i=1;i<=vnum;i++) {
            listnode *p = an[i].next;
            while (p != nullptr) {
                if(i<p->data)
                    q.push_back({i, p->data, p->weight});
                p = p->next;
            }
        }
        //进行排序将最小权边放入第一位。
        sort(q.begin(),q.end(), cmp);
        for(int i=0,num=0;num<vnum-1;i++){
            int v1=findroot(q[i].u,parent);
            int v2= findroot(q[i].v,parent);
            //判断祖先节点是否相等--判断是否在一个集合.
            if(v1!=v2){
                cout<<"("<<q[i].u<<","<<q[i].v<<")"<<" 权:"<<q[i].w<<endl;
                w+=q[i].w;
                parent[v2]=v1;    //合并集合。
                num++;
            }
        }
        cout<<"总权:"<<w;
        cout<<endl;
    }
```





















### 深度优先算法(DFS)

**概念**：

- 深度优先算法(DFS)跟BFS算法一样是**用于遍历图的算法**，但是DFS并不像BFS算法一样，它搜索出来的路径**不具有最短性**，并且dfs算法**类似于枚举**，因此**DFS算法一般用于求出问题的所有路径(例如全排列)**。

- 深度优先算法就是**从起点出发，选择与其邻接的一条路径进行搜索**，**将该路径搜索完**(没有路了或者是个回路)，**再进行回退**，**重新选择**其他路径搜索。这样就需要**使用递归**实现，而**判断是否访问过顶点**就需要一个bool类型的**数组vis进行记录**。

- 对于**非强连通图**，那么可能在**某个节点开始的深度优先搜索可能访问不了所有的节点**，在这种情况，我们**选取某个未被访问的节点开始，再执行深度优先搜索。**

- dfs中最重要的算法思想是**回溯和剪枝**，dfs+回溯+剪枝也可以用于求解最短路径，但是BFS的时间复杂度更低。

  > 1. 回溯是一种选优搜索法，又称为试探法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。
  > 2. 剪枝，就是减小搜索树规模、尽早排除搜索树中不必要的分支的一种手段。形象地看，就好像剪掉了搜索树的枝条，故称之为“剪枝”





**具体操作**：

- 在**访问**图中某一**起始点v**后，**由v出发**，**访问它的任一邻接点w1;**
- **再从w1出发**，**访问与w1邻接但还未被访问过的顶点w2**；
- 然后再从w2出发，**进行类似的访问**....
- 如此进行下去，**直至到达所有的邻接顶点都被访问过的顶点u为止**。
- 接着，**退回一步，退到前一次刚访问过的顶点，看是否还有其他没有被访问的邻接顶点。**
- **如果有**，则访问此顶点，之后**再从此顶点出发**，进行与前述类似的访问；
- **如果没有**，就**再退回一步进行搜索**。重复上述过程，直到连通图中所有顶点都被访问过为止。







**实现代码**：

`邻接矩阵表示图的算法实现`

```c++
bool vis[g.vexnum];   //记录顶点访问信息，需要初始化为false

//图g为邻接矩阵类型，v为访问顶点
void dfs(Graph g,int v){
    cout<<v;
    vis[v]=true;
    //依次检查邻接矩阵v所在行。
    for(int w=0;w<g.vexnum;w++){
        //w是v的邻接点，如果w未访问，则递归调用dfs
        if(g.arcs[v][w]!=0&&!vis[w]){
            dfs(g,w);
        }
    }
}
```



`邻接表表示图的算法实现`

```c++
void DFS(int v){
        cout<<v;
        an[v].flag= true;
        listnode* p=an[v].next;
        while (p!= nullptr){
            if(!an[p->data].flag){
                DFS(p->data);
            }
            p=p->next;
        }
    }
```



















### 双连通性

**概念**：

- 双连通性就是当**删除图中的一个顶点**，使**图分割成两个图**，则**这个图就具有双连通性**，而**能导致图分割成多张图的顶点称为割点**
- **背向边**：当**一个顶点被访问**时，选**取该顶点其中一个未访问过的邻接顶点进行访问**，**没被选取到的邻接顶点与当前顶点形成的边称为背向边**



**寻找割点**：

- 从图中**任一顶点开始**，**执行深度优先搜索并在顶点被访问时给它们编号**。对于**每一个顶点v我们称其先序编号为Num(v)**;

- 对于深度优先搜索生成树上的每一个顶点v，**计算编号最低的顶点**，我们**称之为Low(v)**;对于求解每个顶点的Low，需要对深度优先生成树进行一次后序遍历算出，因为求出顶点v的Low的规则如下：

  > 1. Num(v)
  > 2. 所有背向边(v,w)中的最低Num(w)
  > 3. 树的所有边(v,w)中的最低Low(w)   --所以需要后序遍历
  > 4. Low(v)等于前面三个变量中的最小值。

- 如果一个**顶点v为割点**，需要满足**它的子节点w**的`Low(w)>=Num(v)`





实现代码：

```c++
struct listnode{
    int data;     //num
    bool flag;    //判断是否访问过
    int parent;     //父节点
    int low;
    listnode* next;
};

int count=1;

void findart(int v){
        an[v].flag= true;
        an[v].low=an[v].data=count++;
        listnode* p=an[v].next;
        while (p!= nullptr){
            if(!an[p->data].flag){
                an[p->data].parent=v;
                findart(p->data);
                if(an[p->data].low>=an[v].data){
                    cout<<"V"<<v<<"为割点"<<endl;
                }
                an[v].low=min(an[v].low,an[p->data].low);
            }else if(an[v].parent!=p->data){
                an[v].low=min(an[v].low,an[p->data].data);
            }
            p=p->next;
        }
    }
```











## 贪心算法

**概念**：

- **贪心算法是一种思想**，并不是一种算法，贪心算法是**分阶段地工作，在每一个阶段，可以认为所作决定是好的，而不考虑将来地后果。**
- 算法的**每个阶段总是选择当前阶段最优**，这种策略**希望当算法终止时，能够将每一次的局部最优变成全局最优。**













### 调度问题

**概念**：

- **调度问题**就是**安排一个完成任务的顺序使得全部任务完成的平均完成的时间能够最小化**。



**单个处理器**

- 调度任务的方式我们一般使用**非预占调度**：**一旦开始一个任务，就必须将这个任务运行到完成**
- 调度问题一般都是**最短任务最先进行**，这样将会**产生出每个阶段最优的调度，使得达到全局最优的调度。**
- 操作系统调用程序一般把优先权赋予那些更短的任务。





**多处理器**：

- 如果我们有多个处理器，并且任务是有序的(按照最短时间排序)，这个时候的任务调度问题需要进行小部分的改变，但跟单个处理器的思想是一样的
- 假设我们有**p个处理器**，则我们**选择前p个任务分配给各个处理器各一个**，然后**第p+1任务分配给第一个处理器**，然后**后面的就是按照这个规则分配。**
- 第二个最优解，是将**任务分组分配给各个处理器**，且**任务个数能整除处理器个数**，是**对于0<=i<N/p**，p为处理器个数，N为任务总数，i为处理器序号，我们**从任务i*p+1直到任务(i+1)\*p的每个任务放到编号为i的处理器中。**















### Huffman编码

**概念**：

- 哈夫曼(Huffman)编码是**一种压缩文件的编码**，根据**文件出现的字符使用一种将数据存在树叶上的二叉树来表示每个字符的二进制代码**。
- **每个字符通过从根节点开始用0指示左分支用1表示右分支而以记录路径的方法表示出来**。如果字符c<sub>i</sub>在深度d<sub>i</sub>处并且出现f<sub>i</sub>次，那么该字符代码的值为对d<sub>i</sub>f<sub>i</sub>的求和。
- 一个**最优的哈夫曼编码**是一种**满二叉树**：**所有的节点或者是树叶，或者有两个子节点。**
- 而贪心算法在这里就是**根据字符出现的频率找出总价值最小的满二叉树**，其中所有字符位于树叶。就是**将出现次数少的放在深度深的地方(编码位数较多)，将出现最多放在最浅的地方(编码位数较少)**
- 例如图10-9，字符a压缩后所表示的二进制代码为000

![image-20230808214706581](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230808214706581.png)









**哈夫曼算法**：

- 为了生成最优的哈夫曼编码树，哈夫曼提出了哈夫曼算法，这个算法也是使用了贪心的策略
- 假设**字符个数为C**，算法的描述如下：算法对一个由树组成的森林进行。**一棵树的权等于它的树叶(字符)的频率的和**。**任意选取最小权的两棵树T1和T2**，并**任意形成以T1和T2为子树的新树**，**将这样的过程进行C-1次**。在**算法的开始**，**存在C课单节点树**--每个字符一颗树。在**算法结束时得到一棵树**，这棵树就是最优哈夫曼编码树。





实现代码：

```c++
//树的结构体
struct tree{
    char data;   //存字符
    tree* left;
    tree* right;
    int weight;    //权重
};

//用来定义优先队列的比较规则
struct cmp{
    bool operator()(tree *a, const tree* b){
        return a->weight<b->weight;
    }
};

//需要将数据先存入优先队列中
priority_queue<tree*,vector<tree*>,cmp>pq;


tree* createNode(char data,int weight){
    tree* p=new tree;
    p->data=data;
    p->left= nullptr;
    p->right= nullptr;
    p->weight=weight;
    return p;
}

tree* merge(tree* &t1,tree* &t2){
    int n=t1->weight+t2->weight;
    tree* p= createNode(0,n);
    p->left=t1;
    p->right=t2;
    return p;
}

tree* Huffman(){
    tree* p;
    while (!pq.empty()){
        tree* t1=pq.top();
        pq.pop();
        tree* t2=pq.top();
        pq.pop();
        p=merge(t1,t2);
        pq.push(p);
    }
    return p;
}
```





















## 分治算法

**概念**：

- **分治算法**也是一种**思想策略**，分治算法就是**将大问题不断地分成小问题解决后再重新构建原问题地解**。一般地分治算法的时间复杂度为*O(NlogN)*
- **分**：**递归**解决较小的问题；**治**：然后，**从子问题的解构建原问题的解**。分治算法中我们一直**坚持子问题是不相交的(即基本不重叠)**













### 最近点问题

**概念**:

- 对于平面内存在一个点集P，找到点集P中的最小距离的点对(两个点的距离在点集中所有点产生的距离中最短)。
- 如果按照简单地方法解决就需要嵌套循环导致时间复杂度为O(N²)，但是这个时间复杂度太大了，因此我们就是用到分治







**解决方法**：

- 将**点集P按照x轴进行排序**。

  - 对于**每个递归操作**，**将点集P分成两个点集P<sub>L</sub>和P<sub>R</sub>**，**找出d<sub>L</sub>,d<sub>c</sub>,d<sub>R</sub>**，**求**这之间的**最小值**，然后**递归返回解得到最终问题的解**。

- **d<sub>L</sub>**是在**点集P<sub>L</sub>最短距离的点对的距离**，**d<sub>c</sub>**是**跨越点集P<sub>L</sub>和P<sub>R</sub>的最短距离的点对的距离**，**d<sub>R**</sub>是**在点集P<sub>R</sub>最短距离的点对的距离**。

- **d<sub>c</sub>的求法**：**令 δ=min(d<sub>L</sub>，d<sub>R</sub>)**，如果**出现d<sub>c</sub>更小的情况**，则**d<sub>c</sub>的两个点必然在分割线的左右各δ的距离之内**，我们将**这个区域叫做一条带**。我们**将**在**带的区域内的点按照y轴排序**，如果**两个点的y轴坐标相差大于δ，则d<sub>c</sub>>δ**，因此**就可以不进行判断直接跳过，处理下一对点对**。伪代码如下：

  ```c++
  //先将带区域内的点按照y轴排序
  //NumPoint为带区域的点集的点个数
  for(int i=0;i<NumPoint;i++){
      for(int j=i+1;j<Numpoint;j++){
          //判断点对的y轴距离是否大于δ
          if(diff(pi.y,pj.y)>δ){
              break;
          }else if(diff(pi,pj)<δ){    //判断pi到pj的距离是否小于δ
              δ=diff(pi,pj);
          }
      }
  }
  ```

  





















### 选择问题

**概念**：

- **选择问题要求我们找出含N个元素的表S中的第k个最小的元素**。
- 该问题的解法虽然使用了分治算法的策略，但是他在分之后只需要求解一个子问题，也不需要合并子问题求解，换句话来说，这个问题就是将大问题不断地分找到属于这个问题地解。



**具体做法**：

- **每次递归操作**，**选取一个枢纽元v**，**将集合S根据枢纽元分成S1，S2两个集合**，S1的元素小于枢纽元，S2的元素大于枢纽元
- 如果**k<=|S1|**  --**|S1|为集合S1的元素个数**，就**递归集合S1求解集合S中的第k个最小元素。**
- 如果**k=|S1|+1**，则**枢纽元就是第k个最小元素**。
- **否则**，**在S中的第k个最小元素是S2中的第(k-|S1|-1)个最小元素**。







**五分化中项法**：

- 这也是一个选取枢纽元的方法，这个算法的性能更高

**概念**：

- **把N个元素分成向下取整(N/5)组，5个元素一组，忽略(最多4个)剩余的元素**
- **找出每组的中项(中间值)**，**得到向下取整(N/5)个中项的表M**
- **求出M的中项，将其作为枢纽元v返回**

















## 字符串匹配算法



### KMP算法

**概念**：

- **KMP算法**是用于解决字符串匹配的问题的算法，也就是有**一个文本串和一个模式串**，**求解这个模式串是否在文本串中出现或者匹配**。
- 相对于暴力求解，KMP算法**使用了前缀表来进行匹配**，充分利用了之前匹配的字符，减少了重新匹配全部模式串的时间。
- 时间复杂度为O(m+n)，其中n为文本串长度，m为模式串长度。





**前缀表**：

例子：文本串：'aabaabaaf' ，模式串：'aabaaf'

- 前缀表也就是**记录模式串的各子串最长相等前后缀长度**(即字符串的前缀和后缀相等并且长度最长)的**数组**，而*在KMP算法中是对模式串求解前缀表*

- **前缀**：**字符串除了尾字符的子字符串**都是前缀，模式串的前缀有：a、aa、aab、aaba、aabaa

- **后缀**： **字符串除了首字符的子字符串**都是后缀，模式串的后缀有：f、af、aaf、baaf、abaaf

- ![image-20230917203005664](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230917203005664.png)

- 根据上述的例子可以列出表格：

  ![image-20230917203152483](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230917203152483.png)

- 这样就对应着：aabaaf  010120，这个就为前缀表，而**前缀表**在KMP算法中被称为`next数组`或者`prefix数组`。next的意思就是指通过这个数组可以知晓下一步指针会跳到哪一步。







**求解next数组**：

注：在**遍历模式串的各个子串**时，**i为当前子串的后缀末尾索引**，**j为当前字串的前缀末尾索引**并且为**数组索引小于等于i之前的子串的最长相等前后缀长度**。子串是连续的字符形成的

1. `初始化`：**j初始化为0**，因为模式串的第一个前缀子串为第一个字符，所以j索引指向0的位置，并且**next[0]=0**，**i初始化为1**，用**一个循环从索引i开始遍历模式串**。(因为只有一个字符的子串没有相等前后缀)
2. `前后缀不相同情况`：为了充分利用之前已经匹配的字符，我们将对发生冲突的地方也就是**前后缀末尾字符不匹配的时候**，我们将**对前缀末尾索引**进行**回溯到索引为next[j-1]的位置**。
3. `前后缀相同情况`：**当前后缀末尾字符相等的时候**，就可以**将j++**，不仅将当前子串更新到下一个子串，还**更新了当前子串的最长相等前后缀长度**也就是**next[i]=j**



实现代码:

```c++
void getnext(int *next,const string& s,int size){
    //初始化
    int j=0;
    next[0]=0;
    for(int i=1;i<size;i++){
        //前后缀不相等情况
        while (j>0&&s[i]!=s[j]){
            j=next[j-1];    //回溯找到相等位置或者回到0
        }
        //前后缀相同情况
        if(s[i]==s[j]) j++;
        next[i]=j;
    }
}
```







**KMP具体操作**：

1. `求解next数组`
2. 然后**利用求解next数组同等思路**，`求解文本串出现模式串位置的索引`，求解next数组是模式串前后缀末尾字符的比较，而文本串模式串匹配过程，是文本串与模式串的字符比较过程。
3. 当**j**也就是**文本串在索引大于等于i之前的子串与模式串最长匹配字符长度等于模式串的长度**，就**说明文本串出现了模式串**，然后**返回文本串中出现模式串的第一个字符的索引值**`(i-j+1)`。







KMP算法总体实现代码：

```c++
void getnext(int *next,const string& s,int size){
    //初始化
    int j=0;
    next[0]=0;
    for(int i=1;i<size;i++){
        //前后缀不相等情况
        while (j>0&&s[i]!=s[j]){
            j=next[j-1];    //回溯找到相等位置或者回到0
        }
        //前后缀相同情况
        if(s[i]==s[j]) j++;
        next[i]=j;
    }
}


int KMP(const string &text,const string &mode){
    int len=text.size();
    if(len==0) return 0;
    int size=mode.size();
    int j=0,next[size];
    getnext(next,mode,size);
    for(int i=0;i<len;i++){
        while (j>0&&text[i]!=mode[j]){
            j=next[j-1];
        }
        if(text[i]==mode[j]) j++;
        if(j==size) return (i-j+1);
    }
    return -1;    //未找到模式串
}
```

















## 动态规划(dp)

**概念**：

- 将**递归算法重新写成非递归算法**，让后者把**那些子问题的答案系统地记录在一个表(dp数组)内**，这种方法叫做**动态规划**
- 通常用于**求解具有最优性质的问题**(最优子结构&最优子问题)，希望找到具有最优值的解。
- 核心为穷举，动态规划问题往往具有最优子结构，重叠子问题和状态转移方程的特征。





**基本思想**：

- **适用于子问题不是独立的情况**，也就是各子问题包含公共的子问题，鉴于会重复的求解各个子问题，对每个问题只求一遍，将其保存在一张表中，从而避免重复计算。





**特征**：

- **最优子结构**：当问题的最优解包含了其子问题的最优解时，称该问题具有最优子结构性质。

- **重叠子问题**：在用递归算法自顶向下解问题时，每次产生的子问题并不总是新问题，有些子问题被反复计算多次。动态规划算法利用这个子问题重叠性质，对每一个问题只解一次，而后将其解保存在一个表格(dp数组)中，在以后尽可能多地利用这些子问题的解。

- **状态转移方程(最关键)**：

  > 1. 是动态规划中本阶段的状态往往是上一阶段状态和上一阶段决策的结果。如果给定了第K阶段的状态S**k**以及决策u**k**(S**k**)，则第K+1阶段的状态S**k+1**也就完全确定
  > 2. 也就是**递推方程，一个状态的解往往可以由前一个状态的解得出**
  > 3. 状态是由自己定义的通常可以认为**是函数参数，dp数组的索引**。
  > 4. **状态转移**就是**从一个状态变成另一个状态**，就例如本质为斐波那契数列的爬楼梯问题，从N-1阶或N-2的楼梯上到N阶的楼梯就称为状态转移.
  > 5. **状态压缩**：**有时候并不需要保存所有状态**，当**保存的状态减少，导致算法的空间复杂度降低的技巧**叫做状态压缩





**能解决的问题**：

1. 计数
2. 最值
3. 存在性(是和否的问题，例如01背包)





**解题步骤**：

- **明确状态**：`也就是原问题和子问题中会变化的变量,状态的种数决定dp数组的维度`。根据题意定义状态，这个状态可能是求解题目会变化的量，因为动态规划本质就是穷举，所以这个状态应该是穷举所有方案能够找到求解的目标
- **明确选择**：`也就是导致状态产生变化的行为`。选择就是限制，当我们需要求解问题时，就需要不断地更新选择限制中的数据，来不断地产生多个方案，从而从中找到最优方案。
- **明确dp函数/数组的定义**：就是求解的问题的函数，这个函数要求什么
- **base case**：初始状态，根据题意找到初始状态，然后写出状态转移方程然后写出自顶向下或者自底向上递推的解法



**分析问题**：

- 先分析问题，用备忘录消除重叠子问题，写出自顶向下解法
- 进一步，可以写出自底向上解法
- 再进一步，可能可以优化空间复杂度







**动态规划框架**：

```c++
//初始化 base case
dp[0][0][...]=base;
//进行状态转移
for 状态1 in 状态1的所有取值：
    for 状态2 in 状态2的所有取值：
        for ...
            dp[状态1][状态2][...]=求最值(选择1，选择2，...);
```











例子：

**零钱兑换问题**：

分析问题：

- 设F(n)为求解凑出目标金额为n的最少硬币数，通过分析问题，求解目标金额为n的最小硬币数F(n)=min(F(n-coin1),F(n-coin2)....)，当coins=[1,2,5]，目标金额为11时，则F(11)=min(F(11-1)，F(11-2),F(11-5))，然后依次递推下去，这样就形成了自顶向下的求法，但是会有重复计算，因此需要使用备忘录也就是记忆性递归来剪枝进行优化

![image-20230814232203982](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230814232203982.png)



- *自顶向下解法*：

```c++
class Solution {
    //因为这是自顶向下递推，初始化则只需要初始化为达不到的值就行了
    vector<int>v;
    int dp(vector<int> coins,int amount){
        if(amount==0) return 0;
        if(amount<0) return -1;
        if(v[amount]!=-2) return v[amount];
        int res=INT_MAX;
        for(int coin:coins){
            int sub=dp(coins,amount-coin);
            if(sub==-1) continue;
            res=min(res,sub+1);
        }
        //存到备忘录中
        v[amount]=(res==INT_MAX)?-1:res;
        return v[amount];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        v.assign(amount+1,-2);
        return dp(coins,amount);
    }
};
```





- *自底向上解法*：

```c++
class Solution {
public:
    //状态：目标金额 amount 因为每选择一枚硬币就会导致amount数值减少
    //选择：coins数组，包含着硬币面额，选择不同面额的硬币就会导致amount的不同，凑出amount的方案也不同
    //函数定义：coinChange函数，对于目标金额amount，至少需要coinChange(coins,amount)枚硬币
    //base case：当amount=0时，则最少需要0个硬币，当amount<0，则无法凑出目标金额

    int coinChange(vector<int>& coins, int amount) {
        //目标金额所用最多硬币数为amount，因为是求解最小硬币数问题,所以应该初始化比amount还大
        vector<int>dp(amount+1,amount+1);
        //base case
        dp[0]=0;
        //枚举所有状态
        for(int i=0;i<amount+1;i++){
            for(int j:coins){
                //判断当前amount是否小于选择的面额，如果小于就跳过
                if(i-j<0) continue;
                //状态转移，求出凑出当前面额i的最小硬币数
                dp[i]=min(dp[i],dp[i-j]+1);
            }
        }
        return (dp[amount]>=amount+1)?-1:dp[amount];
    }
};
```









**01背包问题**

**![image-20230819112844773](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230819112844773.png)**

- 经典的动态规划题目，01背包的01就对应着我是否将当前物品放入背包中，由题意可知，我们只需要求解dp[N] [W]就可以得到答案，分析题目对于选择i物品时，当前背包剩余重量为w时，我们将物品i放入背包则dp[i] [w]=dp[i-1] [w-wt[i-1]]+val[i-1]，我们不将物品i放入背包则dp[i] [w]=dp[i-1] [w]，因此我们取其最大值就可以求出对于前i个物品，当背包容量为w时，可以装的最大价值，因此状态转移方程为max(dp[i-1] [w],dp[i-1] [w-wt[i-1]]+val[i-1]);





```c++
#include <iostream>
using namespace std;

//状态：背包的空余容量剩多少，可选择的物品还有哪些
//选择：把这个物品是否放进背包
//dp[i][w]定义，对于前i个物品，当背包的容量为w时，可以装的最大价值是dp[i][w]
//base case:dp[0][...]=dp[...][0]=0,因为当选择物品为0的时候无论w多少都为0，当背包容量为0时，无论物品多少都无法放进
int main(){
    int N,W;
    cin>>N>>W;
    int val[N],wt[N];
    for(int i=0;i<N;i++){
        cin>>val[N]>>wt[N];
    }
    int dp[N+1][W+1];
    memset(dp,0, sizeof(int)*((N+1)*(W+1)));
    for(int i=1;i<=N;i++){
        for(int w=W;w>=wt[i-1];w--){
            dp[i][w]=max(dp[i-1][w],dp[i-1][w-wt[i-1]]+val[i-1]);
        }
    }
    cout<<dp[N][W];
    return 0;
}
```



























## 记忆化搜索



**概念**：

- 记忆化搜索就是深度优先搜索的一种优化策略，`记忆化搜索=深度优先搜索形式+动态规划思想`
- 由于dfs本质是暴力搜索，没有很好地处理重叠子问题，因此很低效
- 记忆化算法在求解地时候还是按照自顶向下的顺序，**但是每求解一个状态，就将它的解保存下来**
- **求解最优解问题**





**优点**：

- **解决了深度优先搜索中的重叠子问题要多次遍历的问题**
- 搜索还可以剪枝，可能剪去大量不必要的状态



**缺点**：

- 对于同样的问题，如果用动态规划解决而是用了记忆化搜索会使得效率有所降低







**dfs函数组成**：

1. 得有搜索边界即结束条件，以及处理
2. 对当前状态的检查，如果结果已经记录，则直接返回返回
3. 从当前状态到下一个状态的转移，当前状态最优解的记录
4. 对结果的返回
5. 核心点：状态转移方程的确定。dp[state]=optimal(dp[state],dfs(next state)+cost);







**代码模板**：

```c++
//type为类型，state为状态，在图论中一般都是横竖坐标
type dfs(state){
    if(结束条件){
        处理;
        return type; //返回对应类型的值
    }
    
    if(当前状态的解已被记录) return dp[state];
    //跟动态规划一样或者说跟dfs一样遍历下一个状态
    for each next state{
        if(检查当前状态是否符合约束条件){
            dp[state]=optimal(dp[state],dfs(next state)+cost);
        }
    }
    return dp[state];
}
```













**例题代码实现**：

- 蓝桥杯题：`滑行`

  ![image-20231112233942782](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20231112233942782.png)

  ```c++
  #include <iostream>
  using namespace std;
  
  int mp[105][105], n, m,dp[105][105];
  int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
  
  int dfs(int x,int y){
      if(dp[x][y]!=-1) return dp[x][y];
      dp[x][y]=1;
      for(int i=0;i<4;++i){
          int px=x+dx[i];
          int py=y+dy[i];
          if(px>=0&&py>=0&&px<n&&py<m&&mp[px][py]<mp[x][y]){
              dp[x][y]=max(dp[x][y],dfs(px,py)+1);
          }
      }
      return dp[x][y];
  }
  
  int main(){
      for(int i=0;i<n;++i){
          for(int j=0;j<m;++j){
              cin>>mp[i][j];
              dp[i][j]=-1;
          }
      }
      int cnt=1;
      for(int i=0;i<n;++i){
          for(int j=0;j<m;++j){
              cnt=max(cnt,dfs(i,j));
          }
      }
      cout<<cnt<<endl;
      return 0;
  }
  ```

  





















## ST表



**概念**：

- ST表**适用于解决区间最值的问题(RMQ问题)的数据结构**
- ST表**本质是dp算法**，只不过dp是对数组一排一排更新，而RMQ是对数组一列一列动态规划的





**操作**：

例题：给一个数组，有n个数，有m个left，right(left和right为区间边界)，求出这m个区间的最值

1. 首先引入状态f[i\][j]，**f[i\][j]表示从第i个元素开始的长度为2<sup>j</sup>个元素的最值**
2. 将第i个元素开始的2<sup>j</sup>个元素**分成长度相等的两部分，每部分的长度为2<sup>j-1</sup>**
3. `状态转移方程`就为：**f[i\][j]=max(f[i\][j-1]，f[i+2<sup>j-1</sup>\][j-1])**，即两部分的最大值
4. `边界条件`：**f[i\][0]=a[i]**
5. 要询问区间[L,R]的最大值，因区间[L,R]的长度为R-L+1，**求出log<sub>2</sub>(R-L+1)的值，设为x**
6. 因此区间[L,R]就可以分为[L,L+2<sup>x</sup>-1]和[R-2<sup>x</sup>+1,R]两个部分，根据状态转移方程可以得出`区间[L,R]的最大值`：**RMQ(L,R)=max(f[L\][x],f[R-2<sup>x</sup>+1\][x])**
7. **2<sup>x</sup>可以用移位运算1<<x提高效率**











```c++
int query(int l,int r){
    int x=(int)log(r-l+1)/log(2);    //在c++中log默认为以10为底，所以需要换底
    //或者直接使用log2函数
    int x=(int)log2(r-l+1);
    return max(f[l][x],f[r-(1<<x)+1][x]);
}
```







**代码**：

```c++
#include <iostream>
#include <math.h>
using namespace std;
//例子
const int N=1e6+10;
int f[N][20];  //20是由log2(n)+1算出来的
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

```







**例题**：

蓝桥杯2415：附近最小

![image-20231127130443086](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20231127130443086.png)



```c++
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


int n, k;

//ST算法
int query(int l, int r, vector<vector<int>> &f) {
    int x = (int)log2(r - l + 1);
    return min(f[l][x], f[r - (1 << x) + 1][x]);
}

int main() {
    cin >> n ;
    int logn = log2(n) + 1;
    vector<vector<int>>f(n + 1, vector<int>(logn));

    for (int i = 1; i <= n; ++i) {
        cin >> f[i][0];
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    cin >> k;
    for (int i = 1; i <= n; ++i) {
        int l = max(1, i - k);
        int r = min(n, i + k);
        cout << query(l, r, f) << " ";
    }
    cout << endl;
    return 0;
}
```























## 单调栈



**概念**：

- 单调栈是一种数据结构，但是因为经常使用就将其放入算法
- 单调栈就是**栈内的元素呈单调递增或者单调递减的(一般指栈顶到栈底)**
- 将一个元素插入单调栈时，为了维护栈的单调性，需要在保证将该元素插入到栈顶后整个栈**满足单调性的前提下弹出最少的元素**。
- 例如：例如，单调递增栈中自顶向下的元素为{0,11,45,81}，插入元素14时为了保持单调性需要依次弹出0、11，操作后栈变为{14,45,81}
- 时间复杂度为`O(n)`





**适用场景**：

- 单调栈可以**求解出某个元素左边或者右边第一个比它大或者小的元素**

- 可以将其分为具体四种问题：

  > 1. 寻找左侧第一个比当前元素大的元素
  > 2. 寻找左侧第一个比当前元素小的元素
  > 3. 寻找右侧第一个比当前元素大的元素
  > 4. 寻找右侧第一个比当前元素小的元素





**各问题解决做法**：

`总结`：

- 查找**比当前大的元素用单调递增栈**，查找**比当前小的元素用单调递减栈**
- 从**左侧**查找就**看插入栈时的栈顶元素**，从**右侧**查找就**看弹出栈时即将插入的元素**

1. `寻找左侧第一个比当前元素大的元素`：

   > - 构造一个**单调递增栈(从栈顶到栈底)**
   > - **从左到右遍历元素**
   > - 如果**当前元素大于栈顶元素**，则将其**加入**(也就是将栈里面小于当前元素的都弹出再插入)；
   > - 如果**小于**，则**当前栈顶元素就是当前遍历的元素左侧第一个比它大的元素**
   > - 如果插入时的**栈为空**，则**说明左侧不存在比当前元素大的元素**

2. `寻找左侧第一个比当前元素小的元素`：

   > - 构造一个**单调递减栈(从栈顶到栈底)**
   > - **从左到右遍历元素**
   > - 如果当前元素**小于**栈顶元素，就**加入**栈中
   > - 如果**大于**，则**当前栈顶元素就是当前遍历元素左侧第一个比它小的元素**
   > - 如果插入时的**栈为空**，则**说明左侧不存在比当前元素小的元素**

3. `寻找右侧第一比当前元素大的元素`：

   > - 构造一个**单调递增栈(从栈顶到栈底)**
   > - **从左到右遍历元素**
   > - 如果**当前遍历元素大于当前栈底元素**，则**当前栈顶元素的右侧第一个比它大的元素就是当前遍历元素**
   > - 如果**小于**，则将其**加入**栈中
   > - 如果在**栈中的元素没有被弹出**，说明栈中**剩下的元素没有右侧比它大的元素**

4. `寻找右侧第一个比当前元素小的元素`：

   > - 构造一个**单调递减栈(从栈顶到栈底)**
   > - **从左到右遍历元素**
   > - 如果**当前遍历元素小于当前栈顶元素**，则**当前栈顶元素的右侧第一个比它小的元素就是当前遍历元素**
   > - 如果**大于**，则**加入**栈中
   > - 如果在**栈中的元素没有被弹出**，说明栈中**剩下的元素没有右侧比它小的元素**







**模板代码**：

1. `单调递增栈`

   ```c++
   int main(){
       stack<int>st;
       for(int i=0;i<nums.size();++i){
           while(!st.empty()&&nums[i]>nums[st.top()]){
               st.pop();
           }
           st.push(i);
       }
   }
   ```

   

2. `单调递减栈`

   ```c++
   int main(){
       stack<int>st;
       for(int i=0;i<nums.size();++i){
           while(!st.empty()&&nums[i]<nums[st.top()]){
               st.pop();
           }
           st.push(i);
       }
   }
   ```

   



































## 滑动窗口



**概念**：

- 滑动窗口算法是由双指针来维护窗口进行滑动的算法

- 该算法适用于求解包含以下关键词的问题：

  > 1. 满足xxx条件(计算结果，出现次数，同时包含)
  > 2. 最长/最短
  > 3. 子串/子数组/子序列







**使用思路(寻找最长)**：

- `核心`：左右双指针(L,R)在起始点，R向右逐位滑动循环

- 每次滑动过程中：

  > 1. 如果**窗内元素满足条件**，`R向右扩大窗口`，并**更新最优结果**
  > 2. 如果窗内元素**不满足条件**，`L向右缩小窗口`

- 直到R到达结尾结束

- **代码模板**

```c++
初始化：左指针l,右指针r,当前结果res,最优结果bestres
while(右指针没有到结尾){
    窗口扩大，加入r对应的元素，更新当前res;
    while(res不满足条件){
        窗口缩小，移除l对应的元素，l右移;
    }
    更新最优结果bestres;
    r++;
}
```











**使用思路(寻找最短)**：

- `核心`：左右双指针(L,R)在起始点，R向右逐位滑动循环

- 每次滑动过程中：

  > 1. 如果窗内**元素满足条件**，`L向右缩小窗口`，并**更新最优结果**
  > 2. 如果窗内元素**不满足条件**，`R向右扩大窗口`

- 直到R到达结尾结束

- **代码模板**

```c++
初始化：左指针l,右指针r,当前结果res,最优结果bestres
while(右指针没有到结尾){
    窗口扩大，加入r对应的元素，更新当前res;
    while(res满足条件){
        更新最优结果bestres;
        窗口缩小，移除l对应的元素，l右移;
    }
    r++;
}
```





















## 回溯算法

**概念**:

- **回溯算法**是一种**进行选择搜索然后再回退到选择点选择其他路径然后形成一个决策树的算法**，例如在一个空间摆放家具就需要进行选择不同的家具然后看效果，如果选择其中一个家具的效果不好，则就回退到选择点选择除选择过以外的家具，如果客户认可就沿着这个路径继续搜索，然后达到一个穷举的效果。
- 回溯算法**一般用于求解所有可行性解问题，例如全排列，N皇后等问题**

- 回溯算法相当于穷举搜索的巧妙实现，但是**性能一般不理想，但是可以通过剪枝来提升性能**
- 回溯算法也是一种**暴力穷举算法**，穷举的过程就是**遍历一颗多叉树**的过程





**求解问题**：

- 用于**求解所有可行性解**的算法(例如全排列，组合，子集问题)









**回溯算法框架**：

```c++
List<value> result;  //用于存求解答案
void backtrack(路径,选择列表){
    if(满足结束条件){
        result.add(路径);
        return;
    }
    for(选择:选择列表){
        做选择;
        backtrack(路径,选择列表);
        撤销选择;
    }
}
```











**例题**：

`全排列`：给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。

代码：

```c++
vector<vector<int>>res;   //存储结果

vector<vector<int>> permute(vector<int>& nums) {
        vector<int>track;
        backtrack(nums,track);
        return res;
    }

//回溯算法
void backtrack(vector<int>&nums,vector<int>track){
    if(track.size()==nums.size()){
        res.push_back(track);
        return;
    }
    for(int num:nums){
        //避免重复选择
        if(find(track.begin(),track.end(),num)!=track.end()) continue;
        //做选择
        track.push_back(num);
        backtrack(nums,track);
        //撤销选择
        track.pop_back();
    }
}
```









`N皇后`：

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。**n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。给你一个整数 `n` ，返回所有不同的 **n 皇后问题** 的解决方案。每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。



代码：

```c++
vector<vector<string>>res;

vector<vector<string>> solveNQueens(int n) {
        //初始化棋局
        vector<string>track(n,string(n,'.'));
        //每行每行放置皇后
        backtrack(0,track,n);
        return res;
}

bool check(vector<string> track,int row,int col,int n){
    //因为我们是每行每行的放置，因此当前行数一下都没有放置皇后所以扫描当前行数以上的就行了
    for(int i=0;i<row;i++){
        if(track[i][col]=='Q') return false;
    }
    //同理扫描当前位置斜上方有没有放置皇后就行了(左上，右上)
    for(int i=row,j=col;i>=0&&j>=0;i--,j--){
        if(track[i][j]=='Q') return false;
    }
    for(int i=row,j=col;i>=0&&j<=n;i--,j++){
        if(track[i][j]=='Q') return false;
    }
    return true;
}

void backtrack(int row,vector<string>& track,int n){
    if(track.size()==row){
        res.push_back(track);
        return;
    }
    for(int col=0;col<n;col++){
        if(!check(track,row,col,n)) continue;
        track[row][col]='Q';
        backtrack(row+1,track,n);
        track[row][col]='.';
    }
}
```

