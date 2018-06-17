#include <iostream>
using namespace std;

template<class K,class E> class search_list
{
     private:
        K *key;  //�ؼ��ֱ��ؼ��뵥����ţ���ǿ���������
        int max_size;
        int legth;
        E *element;
        struct
        {
           K key;
           int a;
        }block[5]; //����Ĭ�Ͻ����ݷ�Ϊ5�顣

     public:
        search_list(int sz=100);
        ~sarch_list() {delete []key; delete []element;}
        bool isempty() const {return length==0;}
        K get_key(int i) const;
        void set_key(K val,int i);
        int seq_search(const K val) const; //˳�����
        bool Insert(K val,E &rec);
        bool Remove(K val,E &rec);
        int bin_search(const K val) const; //���ֲ���
        int block_search(const K val) const;
        friend istream& operator>>(istream &in,search_list<K,E> &in_list)
        {
            K val;
            E elem;
            while(in>>val)
            {
                in>>elem;
                in_list.key[++in_list.length]=val;
                in_list.element[in_list.length]=elem;
            }

            /**for(int i=0;i<=4;i++)  //������ʱ������������ Ϊ�ֿ������׼��
            {
                block[i]=1+i*(length/5);
            }

            for(int i=0;i<5;i++)
            {
                if(i!=4)
                {
                    for(j=1+i*(length/5),block[i]=key[j];j<1+(i+1)*(length/5);j++)
                    {
                        if(key[j]>block[i])
                            block[i]=key[j];
                    }
                }
                else
                {
                    for(j=1+i*(length/5),block[i]=key[j];j<=length;j++)
                    {
                        if(block[i]<key[j])
                            block[i]=key[j];
                    }
                }
            }**/
            //�������Ƕ�����������������֮��Ϳ���ʹ�÷ֿ����
            return in;
        }

        friend ostream& operator<<(ostream &out,search_list<K,E> &out_list)
        {
            for(int i=1;i<=out_list.length;i++)
            {
                out<<out_list.key[i]<<"\t"<<out_list.element[i]<<endl;

            }
            return out;
        }
};


template<class K,class E> search_list<K,E>::search_list(int sz)
{
    max_size=sz;
    length=0;

    key=new K[max_size+1];
    element=new E[max_size+1];
}

template<class K,class E> K search_list<K,E>::get_key(int i) const
{

    return key[i];
}

template<class K,class E> void search_list<K,E>::set_key(K val,int i)
{

    if(i>=1&&i<=length)
        key[i]=val;
}

/**template<class K,class E> int search_list<K,E>::seq_search(const K val) const
{
    for(int i=1;i<=length;i++)
        if(key[i]==val)
          return i;

    return -1;
}**/

template<class K,class E> bool search_list<K,E>::Insert(K val,E &rec)
{
    if(length==max_size)
        return false;
    key[++length]=val;
    element[length]=rec;
}

template<class K,class E> bool search_list<K,E>::Remove(K val,E &rec)
{

    int i;
    for(i=1;i<=length)
        if(key[i]==val)
          break;
    if(i==length+1)
        return false;
    rec=element[i];

    for(int j=i;i<length;j++)
    {
        key[j]=key[j+1];
        element[j]=element[j+1];
    }
    length--;

    return true;
}

template<class K,class E> int search_list<K,E>::seq_search(const K val) const
{
      key[0]=val; //��Ϊ�����ڣ����ݹؼ�����ž���֪���Ƿ���ҳɹ�
      int i=length;

      while(key[i]!=val)
          i--;
      return i; //i==0�����û�������Ϣ��
}

//���ֲ���Ҫ��������Ϊ�洢�ṹ,������������ǵ�����
template<class K,class E> int search_list<K,E>::bin_search(const K val) const  //���ֲ��ҽ��������ھ�̬���ұ�
{
     int high=length,low=1;  //���ؼ��ֺ��������ֿ�����ȷʵ�ܷ���
     while(low<=high)
     {
         int mid=low+(high-low)/2;
         if(val>key[mid])
              low=mid+1;
         else if(val<key[mid])
              high=mid-1;
         else
            return mid;
     }
     return -1;
}


//ʹ�÷ֿ���Ҷ�������˳����е�������Ҫ��

//���ؼ��ַ�Ϊb�飬ǰb-1���йؼ��ָ���Ϊs=n/b(����n/b����С����)����b��Ĺؼ��ָ���С�ڵ���s
//ÿһ��Ĺؼ��ֲ�һ�����򣬵�ǰһ���е����ؼ��ֱ���С�ں�һ���е���С�ؼ���
//������������һ�����������
//Ȼ�������������в��ҵ���Ӧ�Ŀ죬Ȼ����ȥ�����ö��ֲ��һ�������ҡ�
template<class K,class E> int block_search(const K val) const //�����������Ѿ���������������ȷʵ��Ч�ˣ���ǰ���������Ľ���������Ҳ�Ứȥ�ܶ�ʱ��
{
     int j;
     for(int i=0;i<5;i++)  //���ڿ��в���
     {
         if(val<=block[i].key)
         {
             j=block[i].a;
             break;
         }
     }

     int low=j,high;
     if(j==1+4*length)
         high=length;
     else
        high=low+length/5-1;
     while(low<=high) //�������ö��ֲ��ң�����ĳһ����
     {
         int mid=low+(high-low)/2;
         if(key[mid]==val)
            return mid;
         else if(key[mid]<val)
            low=mid+1;
         else
            high=mid-1;
     }

     return -1; //����ʧ��
}

