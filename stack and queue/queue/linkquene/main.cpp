#include <iostream>
#include "linkquene.h"
//#include "node.h" 在quene中已经包含此文件，这里再包含就会出现重复定义的问题
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
    cout<<"退出队列首元素为："<<val<<endl;
    cout<<"队列中还有"<<quene.length()<<"个元素"<<endl;
    quene.show();
    return 0;
}
