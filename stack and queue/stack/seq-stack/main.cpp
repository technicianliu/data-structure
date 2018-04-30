#include <iostream>
#include "seqstack.h"
#define for(i,a) for(i=0;i<a;i++)   //如果有多重循环，那么这里的宏定义会使代码量减小很多。
using namespace std;

int main()
{
    Seqstack<int> stack1(20);
    int i,a,val;
    cin>>a;
    for(i,a)
    {
        stack1.push(i+1);
    }
    stack1.pop(val);
    cout<<"退出栈顶元素："<<val<<endl;

    stack1.traverse();

    return 0;
}
