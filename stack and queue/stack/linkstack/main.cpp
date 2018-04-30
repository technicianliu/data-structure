/*一直存在一个问题，就是头文件换成cpp后总出错。*/
#include <iostream>
#include "linkstack.h"
using namespace std;

int main()
{
    int i,val;
    linkedstack<int> stack1;

    for(i=0;i<10;i++)
    {
        stack1.push(i+1);
    }

    stack1.pop(val);
    cout<<"退栈元素为："<<val<<endl;

    stack1.gettop(val);
    cout<<"退栈后栈顶元素为："<<val<<endl;

    cout<<"输出栈中所有元素："<<endl;
    stack1.show();

    stack1.makeempty();
    return 0;

}
