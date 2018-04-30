
#include <iostream>
#include "double-linklist.h"
using namespace std;

int main()
{
    linklist<int> list1;
    int val;
    cin>>list1;
    linklist<int> list2(list1);
    list1.Insert(3,10);
    list1.output();

    list2.Remove(3,val);
    list2.output();
    cout<<val<<endl;
    return 0;
}
