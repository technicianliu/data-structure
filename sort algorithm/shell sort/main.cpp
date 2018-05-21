//希尔排序
//(1)先取一个小于n的整数d1作为第一个增量，将全部元素分为d1分组，所有
//   距离为d1的倍数的记录放在同一个分组当中。
//(2)现在各组内进行直接插入排序
//(3)取第t个增量dt进行重复分组，重复(2),直至所取的增量dt=1，即所有记录
//   放在同一个组中进行直接插入排序为止
#include <iostream>

using namespace std;

void shell_sort(int a[],int n);
int main()
{
    int i,a[10]={98,45,67,43,87,12,34,88,40,69};
    shell_sort(a,10);
    for(i=0;i<10;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}

void shell_sort(int a[],int n)
{
    int gap=n,i,j,temp;
    do
    {
        gap=gap/3+1;
        for(i=0+gap;i<n;i++)
        {
            if(a[i]<a[i-gap])
            {
                temp=a[i];
                j=i-gap;
                do
                {
                    a[j+gap]=a[j];
                    j=j-gap;
                }while(j>1&&a[j]>temp);
                a[j+gap]=temp;
            }
        }
    }while(gap>1);
}

/*template<class T,class othertype> void shell_sort(datalist<T,othertype> &tmp)
{
    int gap=tmp.length(),i,j;
    do    //显然，这个过程用这种循环比较合适
    {
        gap=gap/3+1;
        for(i=1+gap;i<tmp.length();i++) //每个分组交替进行处理
        {
            if(tmp[i]<tmp[i-gap])
            {
                 tmp[0]=tmp[i];
                 j=i-gap;
                  do  //这个do循环就是对某一组进行直接插入排序了
                  {
                     tmp[j+gap]=gap[j];
                     j=j-gap;

                   }while(j>1&&tmp[0]<tmp[j]);
                    tmp[j+gap]=tmp[0];
            }

        }
    }while(gap>1);  //gap为1时，结束排序。
    tmp.print();
} */
