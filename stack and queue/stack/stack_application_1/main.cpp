/*������ǽ�ʮ������ת��Ϊ�������Ƶ�����
�����㷨�ǣ�
N=(N/d)*d+N%d,N=N/d ��˽�����ȥ��ֱ��N/d=0Ϊֹ
����˵����㷨�ʺ�ʮ���Ƶ�2~9���Ƶ�ת�������Ǵ�������˵��ȫ
����������ʮ����ת����ʮ������*/
#include <iostream>
#include "linkstack.h"
using namespace std;

int main()
{
    int n,d;
    linkedstack<int> stack1;
    cin>>n>>d;
    while(n/d)
    {
        stack1.push(n%d);
        n=n/d;
    }
    stack1.push(n);

    stack1.show();
    return 0;
}
