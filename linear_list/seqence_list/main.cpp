#include <iostream>
#include "seqlist.h"
using namespace std;

int main()
{
    seqlist<int> La,Lb,Lc;
    int val;
    cin>>La>>Lb;
    Lc.mergelist(La,Lb);
    cout<<Lc;
    return 0;

}
