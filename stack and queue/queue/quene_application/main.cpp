/*输出杨辉三角形问题：
*/
#include <iostream>
#include "linkquene.h"
#include <iomanip>
using namespace std;
void yangvi(int n);
int main()
{
    int n;
    cin>>n;
    yangvi(n);
    return 0;
}

void yangvi(int n)
{
    linkquene<int> quene;
    quene.makeempty(); //就是说本来分配的空间里面的值是随机的，自己在顺序出队列时也不用删除，只要改变指示器就行。

    quene.enquene(1);
    quene.enquene(1);

    int s=0,k,j,t,i;
    for(i=1;i<=n;i++)
    {
        cout<<endl;
        quene.enquene(0);   //每行前补零。
        for(k=n-i-1;k>=0;k--)
        {
            cout<<" ";
        }

        for(j=1;j<=i+2;j++)
        {
            quene.dequene(t);
            quene.enquene(s+t);
            s=t;
            if(j!=i+2)
            {
                cout<<setw(5)<<s;
            }
        }
    }

}
