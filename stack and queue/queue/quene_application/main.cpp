/*���������������⣺
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
    quene.makeempty(); //����˵��������Ŀռ������ֵ������ģ��Լ���˳�������ʱҲ����ɾ����ֻҪ�ı�ָʾ�����С�

    quene.enquene(1);
    quene.enquene(1);

    int s=0,k,j,t,i;
    for(i=1;i<=n;i++)
    {
        cout<<endl;
        quene.enquene(0);   //ÿ��ǰ���㡣
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
