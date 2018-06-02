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
        treenode(T temp,treenode<T> *left=NULL,treenode<T> *right=NULL); //使用默认参数
        treenode<T>* Copy();  //复制结点
        void Release();       //释放结点
        void setleft(treenode<T> *left); //设置左链
        void setright(treenode<T> *right); //设置右链
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

template<class T> void treenode<T>::Release()  //将当前结点的所有子树删除,无法删除当前结点，自己的算法可以删除
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


/*在重新设置左右链，应先释放原有的左右链占用的空间。这里希望指针的两个子树是已经复制好了的*/
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
