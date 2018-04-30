/*这道题是将十进制数转化为其他进制的数，
所用算法是：
N=(N/d)*d+N%d,N=N/d 如此进行下去，直到N/d=0为止
书上说这个算法适合十进制到2~9进制的转换，但是从理论上说完全
可以用来将十进制转换到十六进制*/
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
