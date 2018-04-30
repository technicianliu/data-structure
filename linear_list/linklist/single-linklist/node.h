//书上的这种聚合两个类的方法值得学习
#include <iostream>
using namespace std;

template<class T> class linklist;

template<class T> class node
{
    friend class linklist<T>; //声明为友元后再给node写函数感觉有点多余,就像这个类仅仅是一个数据类型
    private:
        T data;
        node<T> *link;

    public:
        static int length;//这里用静态数据成员也有缺点，比如这个统计的时整个程序中的结点个数
        node();
        node(const T &item,node<T> *ptr=NULL):data(item),link(ptr){}
        //这两个构造函数的用处就在于动态生成结点时便于赋值

};

template<class T> int node<T>::length=0;//静态数据成员只能在类体外进行初始化,在模板里面这里也必须加上最前面那个东西

template<class T> node<T>::node()
{
    link=NULL;
}


