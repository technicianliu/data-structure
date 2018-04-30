#include <iostream>
#include "linklist.h"
using namespace std;


int main()
{
   int val;
   linklist<int> list1;
   list1.creatlist();


   list1.listdelete(3,val);
   cout<<list1;
   cout<<val;


   return 0;
}
