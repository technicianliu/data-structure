#include <iostream>
#include "doublestack.h"
using namespace std;

int main()
{
    int i,val;
    doublestack<int> stack1(20);
    for(i=0;i<10;i++)
    {
        stack1.push(1,i+1);
    }
    for(i=10;i<20;i++)
    {
        stack1.push(2,i+1);
    }

    stack1.pop(1,val);
    cout<<"��һ��ջ��ջԪ��Ϊ��"<<val<<endl;

    stack1.pop(2,val);
    cout<<"�ڶ���ջ��ջԪ��Ϊ��"<<val<<endl;

    stack1.gettop(1,val);
    cout<<"��һ��Ԫ����ջ��ջ��Ԫ���ǣ�"<<val<<endl;

    stack1.traverse();
    return 0;
}
