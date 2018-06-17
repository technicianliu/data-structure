#include <iostream>
using namespace std;

template<class K,class E> class search_list
{
     private:
        K *key;  //关键字表，关键码单独存放，增强查找灵活性
        int max_size;
        int legth;
        E *element;
        struct
        {
           K key;
           int a;
        }block[5]; //这里默认将数据分为5块。

     public:
        search_list(int sz=100);
        ~sarch_list() {delete []key; delete []element;}
        bool isempty() const {return length==0;}
        K get_key(int i) const;
        void set_key(K val,int i);
        int seq_search(const K val) const; //顺序查找
        bool Insert(K val,E &rec);
        bool Remove(K val,E &rec);
        int bin_search(const K val) const; //二分查找
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

            /**for(int i=0;i<=4;i++)  //在输入时将索引表建立好 为分块查找做准备
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
            //接下来是对索引块排序，拍完序之后就可以使用分块查找
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
      key[0]=val; //作为监视哨，根据关键字序号就能知道是否查找成功
      int i=length;

      while(key[i]!=val)
          i--;
      return i; //i==0则表中没有相关信息，
}

//二分查找要用向量作为存储结构,这里设有序表是递增的
template<class K,class E> int search_list<K,E>::bin_search(const K val) const  //二分查找仅仅适用于静态查找表
{
     int high=length,low=1;  //将关键字和数据区分开放置确实很方便
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


//使用分块查找对数据在顺序表中的排列有要求

//将关键字分为b块，前b-1块中关键字个数为s=n/b(大于n/b的最小整数)，第b块的关键字个数小于等于s
//每一块的关键字不一定有序，但前一块中的最大关键字必须小于后一块中的最小关键字
//其中索引表是一个递增有序表
//然后先在索引表中查找到相应的快，然后再去块中用二分查找或有序查找。
template<class K,class E> int block_search(const K val) const //假设索引表已经满足条件，这里确实高效了，但前面对索引表的建立和排序也会花去很多时间
{
     int j;
     for(int i=0;i<5;i++)  //先在块中查找
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
     while(low<=high) //接下来用二分查找，查找某一个块
     {
         int mid=low+(high-low)/2;
         if(key[mid]==val)
            return mid;
         else if(key[mid]<val)
            low=mid+1;
         else
            high=mid-1;
     }

     return -1; //查找失败
}

