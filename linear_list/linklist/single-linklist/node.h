//���ϵ����־ۺ�������ķ���ֵ��ѧϰ
#include <iostream>
using namespace std;

template<class T> class linklist;

template<class T> class node
{
    friend class linklist<T>; //����Ϊ��Ԫ���ٸ�nodeд�����о��е����,��������������һ����������
    private:
        T data;
        node<T> *link;

    public:
        static int length;//�����þ�̬���ݳ�ԱҲ��ȱ�㣬�������ͳ�Ƶ�ʱ���������еĽ�����
        node();
        node(const T &item,node<T> *ptr=NULL):data(item),link(ptr){}
        //���������캯�����ô������ڶ�̬���ɽ��ʱ���ڸ�ֵ

};

template<class T> int node<T>::length=0;//��̬���ݳ�Աֻ������������г�ʼ��,��ģ����������Ҳ���������ǰ���Ǹ�����

template<class T> node<T>::node()
{
    link=NULL;
}


