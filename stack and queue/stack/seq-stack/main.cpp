#include <iostream>
#include "seqstack.h"
#define for(i,a) for(i=0;i<a;i++)   //����ж���ѭ������ô����ĺ궨���ʹ��������С�ܶࡣ
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
    cout<<"�˳�ջ��Ԫ�أ�"<<val<<endl;

    stack1.traverse();

    return 0;
}
