/*本程序为输入两个多项式，输出它们的和*/
#include <iostream>
#include "linklist.h"
using namespace std;

int main()
{
    linklist<int> list1,list2,list3;
    cout<<"请输入第一个多项式："<<endl;
    list1.creatlist();
    cout<<"请输入第二个多项式："<<endl;
    list2.creatlist();
    list1.listplus(list2,list3);
    cout<<"第一个多项式为："<<endl;
    list1.showlist();
    cout<<"第二个多项式为："<<endl;
    list2.showlist();
    cout<<"两个多项式的和为："<<endl;
    list3.showlist();
    return 0;
}
