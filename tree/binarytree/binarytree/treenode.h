#include <iostream>
using namespace std;

template<class T> class binarytree;

template<class T> class treenode
{
    friend class binarytree<T>;
    private:
        T data;
        treenode<T> *leftchild,*rightchild;
    public:
        treenode();
        treenode(T temp,treenode<T> *left=NULL,treenode<T> *right=NULL); //ʹ��Ĭ�ϲ���
        treenode<T>* Copy();  //���ƽ��
        void Release();       //�ͷŽ��
        void setleft(treenode<T> *left); //��������
        void setright(treenode<T> *right); //��������
};

template<class T> treenode<T>::treenode():leftchild(NULL),rightchild(NULL) {}

template<class T> treenode<T>::treenode(T temp,treenode<T> *left,treenode<T> *right)
{
    data=temp;
    leftchild=left;
    rightchild=right;
}

/*template<class T> treenode<T>* treenode<T>::Copy()
{

     if(rightchild==NULL&&leftright==NULL)
     {
         treenode<T> *temp=new treenode<T>;
         temp->data=data;
         temp->rightchild=NULL;
         temp->leftchild=NULL;
         return tenp;
     }
     else
     {
          treenode<T> *temp=new treenode<T>(data,NULL,NULL);
          if(leftchild!=NULL)
          {
              treenode<T> *L=leftchild->Copy();
              temp->leftchild=L;
          }
          if(rightchild!=NULL)
          {
              treenode<T> *R=rightchild->Copy();
              temp->rightchild=R;
          }
            return temp;

     }
}*/

template<class T> treenode<T>* treenode<T>::Copy()
{
    treenode<T> *newleft,*newright;
    if(leftchild)
        newleft=leftchild->Copy();
    else
        newleft=NULL;
    if(rightchild)
        newright=rightchild->Copy();
    else
        newright=NULL;

    treenode<T> *temp=new treenode<T>(data,newleft,newright);
    if(temp)
        return temp;
    else
        return NULL;
}

/*template<class T> void treenode<T>::Release()
{
    if(leftchild==NULL&&right==NULL)
    {
         delete this;
         return;
    }
    else
    {
        if(leftchild!=NULL)
        {
            treenode<T> *temp1=leftchild;
            temp1->Release();
        }
        if(rightchild!=NULL)
        {
            treenode<T> *temp2=rightchild;
            temp2->Release();
        }
        delete this;
    }
    return;
}*/

template<class T> void treenode<T>::Release()  //����ǰ������������ɾ��,�޷�ɾ����ǰ��㣬�Լ����㷨����ɾ��
{
    if(leftchild)
    {
        leftchild->Release();
        delete leftchild;
        leftchild=NULL;
    }
    if(rightchild)
    {
        rightchild->Release();
        delete rightchild;
        rightchild=NULL;
    }
}


/*������������������Ӧ���ͷ�ԭ�е�������ռ�õĿռ䡣����ϣ��ָ��������������Ѿ����ƺ��˵�*/
template<class T> void treenode<T>::setleft(treenode<T> *left)
{
    if(leftchild)
    {
        leftchild->Release();
    }
    leftchild=left;
}

template<class T> void treenode<T>::setright(treenode<T> *right)
{
    if(rightchild)
        rightchild->Release();

    rightchild=right;
}
