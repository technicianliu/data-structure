#include <iostream>
#include "linkquene.h"
//#include "node.h" ��quene���Ѿ��������ļ��������ٰ����ͻ�����ظ����������
using namespace std;

int main()
{
    linkquene<int> quene;
    int i,val;
    for(i=0;i<10;i++)
    {
        quene.enquene(i+1);
    }

    quene.dequene(val);
    cout<<"�˳�������Ԫ��Ϊ��"<<val<<endl;
    cout<<"�����л���"<<quene.length()<<"��Ԫ��"<<endl;
    quene.show();
    return 0;
}
