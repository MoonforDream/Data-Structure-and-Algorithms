# 栈(stack)

## 概念

- **栈(stack)**是限制插入和删除只能在一个位置上的进行的表，而这个模型唯一的开口位置是表的**末端**，叫做**栈顶(top)**，相反表的首部，叫做**栈底**。对于栈的基本操作有**Push(进栈)**和**Pop(出栈)**，前者相当于插入，后者则是删除表中最后一个元素(也就是处在栈顶位置的元素)。
- *栈是一个先进后出的模型*



**注意事项**：

- 虽然这里将栈放在线性表外，但是栈模型也属于线性表。

- **栈**是既可以用数组实现也可以用链表实现

  > - 如果栈的大小已知且固定，或者对随机访问元素效率有较高要求，使用**数组**实现栈可能更合适。
  > - 如果栈的大小不确定，或者插入和删除操作频繁且在栈顶之外发生，使用**链表**实现栈可能更有优势。

  

  

  

![image-20230706002351136](C:\Users\me\AppData\Roaming\Typora\typora-user-images\image-20230706002351136.png)

**链表实现代码**：

```c++
struct Node{
    int data;
    Node *next;
};
typedef Node* Stack;

Stack createStack(int data){
    struct Node* p=new struct Node;
    p->data=data;
    p->next=NULL;
    return p;
}

//进栈
void Push(Stack &head,int data){
    Stack add= createStack(data);
    if(head==NULL){
        head=add;
    }else{
        Node* p=head;
        add->next=p;
        head=add;
    }
}

//出栈
void Pop(Stack &head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
        return;
    }
    Node* p=head;
    head=p->next;
    delete p;
}

//获取栈顶元素
int top(Stack head){
    return head->data;
}


//打印栈
void printStack(Stack head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
        return;
    }
    Node* p=head;
    while (p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

//获取栈的大小
int Size(Stack head){
    Node* p=head;
    int cnt=0;
    if(p->data&&p->next==NULL){
        cnt=1;
    } else{
        while (p!=NULL){
            cnt++;
            p=p->next;
        }
    }
    return cnt;
}

//判断栈是否为空
bool empty(Stack head){
    if (head!=NULL){
        return false;
    }else{
        return true;
    }
}

//清空栈
void destroy(Stack &head){
    if(head==NULL){
        cout<<"栈中没有数据"<<endl;
        return;
    }
    Node* tail=head->next;
    while (head!=NULL){
        delete head;
        head=tail;
        if(tail!=NULL)
            tail=tail->next;
        else
            return;
    }
}
```









**数组实现代码：**

```c++
class stack{
public:
    //入栈
    void Push(int data){
        head.push_back(data);
    }

    //出栈
    void Pop(){
        if(head.empty()){
            cout<<"栈中没有数据！"<<endl;
            return;
        } else
            head.pop_back();
    }

    //获取栈顶元素
    int top(){
        if(head.empty()){
            cout<<"栈中没有数据！"<<endl;
            return NULL;
        }
        return head.back();
    }

    //打印栈
    void printstack(){
        if(head.empty()){
            cout<<"栈中没有数据"<<endl;
            return;
        }else{
            for(vector<int>::const_iterator it=head.end()-1;it>=head.begin();it--){
                cout<<*it<<" ";
            }
            cout<<endl;
        }
    }

    //清空栈
    void destory(){
        head.clear();
    }

    //获取栈的大小
    int Size(){
        return head.size();
    }

    //判断栈是否为空
    bool empty(){
        if(head.empty()){
            return true;
        } else{
            return false;
        }
    }
private:
    vector<int>head;
};
```











## 逆波兰转换式

**概念**：

- 一种**后缀表达式**，例如a+b+c*d，转换成逆波兰表达式就为：a b + c d * +，然后我们将逆波兰表达式压入栈中(*将元素压入栈中遇到运算符号就将栈中的两个元素进行出栈在进行运算，运算完后再压入栈中，重复操作就能得到逆波兰表达式的结果*)，逆波兰表达式中没有括号！

- 转换成逆波兰表达式，需要一个空栈跟一个临时输出区(但不直接输出)，将**运算元素放进临时输出区**，将**运算符号压入栈**中。

  > - 如果运算符的优先级大于上一个运算符，就进行入栈。
  > - 如果运算符的优先级小于等于上一个运算符，就将前面的运算符出栈放在临时输出区，再将该运算符入栈。
  > - 如果栈中有左括号，后面入栈的运算符不是右括号的话，左括号就不出栈，而是继续重复上两个规则，直到右括号出现就将左括号出栈，但括号不放入临时输出区
  > - 当运算元素都放入临时输出区时，栈区还有运算符就直接出栈放入临时存放区，最终将临时存放区按顺序输出出来就是转换的逆波兰表达式



**代码**：

```c++
bool flag(char a,char b){
    int a1,b1;
    if(a=='+'||a=='-'){
        a1=1;
    }else if(a=='*'||a=='/'){
        a1=2;
    }else if(a=='('||a==')'){
        a1=3;
    }
    if(b=='+'||b=='-'){
        b1=1;
    }else if(b=='*'||b=='/'){
        b1=2;
    }else if(b=='('||b==')'){
        b1=3;
    }
    return a1>=b1;
}

vector<char> reversePolan(char *an,int len){
    stack<char>s;
    vector<char>v;
    int cnt=0;
    for(int i=0;i<len;i++){
        if(an[i]!='+'&&an[i]!='-'&&an[i]!='*'&&an[i]!='/'&&an[i]!='('&&an[i]!=')'){
            v.push_back(an[i]);
        }else if(an[i]=='+'||an[i]=='-'||an[i]=='*'||an[i]=='/'||an[i]=='('||an[i]==')'){
            if(s.empty()){
                s.push(an[i]);
            }else if(an[i]=='('){
                s.push(an[i]);
                cnt=1;
            }else if(an[i]==')'&&cnt==1){
                while (s.top()!='('){
                    v.push_back(s.top());
                    s.pop();
                }
                s.pop();
                cnt=0;
            } else if(flag(s.top(),an[i])){
                while (!s.empty()){
                    if(s.top()=='('){
                        break;
                    }
                    v.push_back(s.top());
                    s.pop();
                }
                s.push(an[i]);
            }else{
                s.push(an[i]);
            }
        }
    }
    if(!s.empty()){
        while (!s.empty()){
            v.push_back(s.top());
            s.pop();
        }
    }
    return v;
}


int main() {
    char an[]={'a','+','b','*','c','+','(','d','*','e','+','f',')','*','g'};
    int len= sizeof(an)/ sizeof(an[0]);
    auto a= reversePolan(an,len);
    for(char i:a){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
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

   

