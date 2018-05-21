//自己按照直接插入排序所写的代码
#include <iostream>
using namespace std;

void d_insert_sort(int a[],int n);

int main()
{
   int i,a[10]={34,59,12,71,54,39,99,56,78,1};
   d_insert_sort(a,10);
   for(i=0;i<10;i++)
    cout<<a[i]<<" ";
   return 0;
}

void d_insert_sort(int a[],int n)
{
    int i,j,temp;
    for(i=1;i<n;i++)
    {
        temp=a[i];
        for(j=i-1;j>=0;j--)
        {
            if(a[j]>temp)
            {
                a[j+1]=a[j];
                if(j==0)  //这个判断必不可少
                    a[j]=temp;
            }
            else
            {
                a[j+1]=temp;
                break;
            }
        }
    }
}


//把书上的类实现之后拿过去。
template<class T,class othertype> void d_insert_sort(datalist<T,othertype> &List)
{  //非递减排序。
    int i,j;
    for(i=2;i<=List.length();i++)
    {
        List[0]=List[i];
        j=i-1;
        while(List[0]<List[j])
        {
            List[j+1]=List[j];
            j--;
        }
        List[j+1]=List[0];
    }
    List.print();
}
