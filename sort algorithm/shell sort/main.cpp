//ϣ������
//(1)��ȡһ��С��n������d1��Ϊ��һ����������ȫ��Ԫ�ط�Ϊd1���飬����
//   ����Ϊd1�ı����ļ�¼����ͬһ�����鵱�С�
//(2)���ڸ����ڽ���ֱ�Ӳ�������
//(3)ȡ��t������dt�����ظ����飬�ظ�(2),ֱ����ȡ������dt=1�������м�¼
//   ����ͬһ�����н���ֱ�Ӳ�������Ϊֹ
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
    do    //��Ȼ���������������ѭ���ȽϺ���
    {
        gap=gap/3+1;
        for(i=1+gap;i<tmp.length();i++) //ÿ�����齻����д���
        {
            if(tmp[i]<tmp[i-gap])
            {
                 tmp[0]=tmp[i];
                 j=i-gap;
                  do  //���doѭ�����Ƕ�ĳһ�����ֱ�Ӳ���������
                  {
                     tmp[j+gap]=gap[j];
                     j=j-gap;

                   }while(j>1&&tmp[0]<tmp[j]);
                    tmp[j+gap]=tmp[0];
            }

        }
    }while(gap>1);  //gapΪ1ʱ����������
    tmp.print();
} */
