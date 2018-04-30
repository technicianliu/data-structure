#include <iostream>
using namespace std;

template<class T> class linkquene;

template<class T> class linknode
{
    friend class linkquene<T>;  //�������ĺô��ǲ����ڽ�����������������������ҽ����ʹ������Ҳʮ�ַ���
    private:
        linknode<T> *link;  //�������ָ��������ӽ��
        T data;
    public:
        linknode(linknode<T> *ptr=NULL);
        linknode(const T item,linknode<T> *ptr=NULL);

};


template<class T> linknode<T>::linknode(linknode<T> *ptr)
{
    link=ptr;
}

template<class T> linknode<T>::linknode(const T item,linknode<T> *ptr):data(item),link(ptr)
{

}
