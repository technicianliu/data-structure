/*һֱ����һ�����⣬����ͷ�ļ�����cpp���ܳ���*/
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
    cout<<"��ջԪ��Ϊ��"<<val<<endl;

    stack1.gettop(val);
    cout<<"��ջ��ջ��Ԫ��Ϊ��"<<val<<endl;

    cout<<"���ջ������Ԫ�أ�"<<endl;
    stack1.show();

    stack1.makeempty();
    return 0;

}
