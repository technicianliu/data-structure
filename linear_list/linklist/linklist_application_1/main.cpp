/*������Ϊ������������ʽ��������ǵĺ�*/
#include <iostream>
#include "linklist.h"
using namespace std;

int main()
{
    linklist<int> list1,list2,list3;
    cout<<"�������һ������ʽ��"<<endl;
    list1.creatlist();
    cout<<"������ڶ�������ʽ��"<<endl;
    list2.creatlist();
    list1.listplus(list2,list3);
    cout<<"��һ������ʽΪ��"<<endl;
    list1.showlist();
    cout<<"�ڶ�������ʽΪ��"<<endl;
    list2.showlist();
    cout<<"��������ʽ�ĺ�Ϊ��"<<endl;
    list3.showlist();
    return 0;
}
