#include <iostream>
#include "quene.h"
using namespace std;

int main()
{
    seqquene<int> quene(10);
    int val,i;
    for(i=0;i<10;i++)
    {
        quene.enquene(i+1);
    }
    cout<<quene.length()<<endl;
    quene.dequene(val);
    cout<<val<<endl;
    cout<<quene.length()<<endl;
    quene.getfront(val);
    cout<<val<<endl;
    return 0;
}
