#include <iostream>
using namespace std;

template<class T> class linklist;

template<class T> class node
{
    friend class linklist<T>;
    private:
        T data1;
        T data2;
        node<T> *link;

    public:
        static int length;
        node();
        node(const T &item1,const T &item2,node<T> *ptr=NULL):data1(item1),data2(item2),link(ptr){}


};
template<class T> int node<T>::length=0;

template<class T> node<T>::node()
{
    link=NULL;
}
