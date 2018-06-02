#include <iostream>
using namespace std;

template<class T> class tree;

template<class T> class treenode
{
    private:
       treenode<T> *firstchild;
       treenode<T> *nextsibing;
       T data;
    public:
       treenode(T temp,treenode<T> *pt1=NULL,treenode<T> *pt2=NULL):data(temp),firstchild(pt1),nextsibing(pt2) {}
       friend class tree<T>;

       treenode<T>* Copy()
       {
           treenode<T> *newnode=NULL,*newfirst=NULL,*newnext=NULL;
           newnode=new treenode<T>(data,NULL,NULL);
           if(nextsibing!=NULL)
           {
               newnext=nextsibing->Copy();
           }
           if(firstchild!=NULL)
           {
               newfirst=firstchild->Copy();
           }
           newnode->firstchild=newfirst;
           newnode->nextsibing=newnext;

           return newnode;
       }
};

template<class T> class tree
{
    private:
        treenode<T> *root,*current;  //树根结点和当前指针结点,设置当前结点是为了在树中操作方便
        void creat_tree(treenode<T> *&pointer,istream &in);
        void print_tree(treenode<T> *pointer,ostream &out);
        bool Find(treenode<T> *r,T value); //在以r为根结点中搜索
        void removesubtree(treenode<T> *r); //删除以r为根的树
        bool FindParent(treenode<T> *t,treenode<T> *p);
    public:
        tree():root(NULL),current(NULL) {}
        tree(tree<T> &r);
        ~tree();

        bool isempty() {return root==NULL;}
        bool Firstchild(); //寻找当前结点第一个孩子使其成为当前结点。
        bool Nextsibing(); //寻找下一个兄弟使其成为当前结点
        bool Parent(); //寻找双亲结点使其成为当前结点
        bool Find(T value); //搜索值为value的结点

        void print_current(); //打印出当前结点中的数据。

        friend istream& operator>>(istream &in,tree<T> &tree)
        {
            tree.creat_tree(tree.root,in);
            return in;
        }
        friend ostream& operator<<(ostream &out,tree<T> &tree)
        {
            tree.print_tree(tree.root,out);
            return out;
        }

};


template<class T> tree<T>::tree(tree<T> &r)
{
    root=r.root->Copy();
}

template<class T> tree<T>::~tree()
{
    removesubtree(root);
}

template<class T> bool tree<T>::Firstchild()
{
     if(current==NULL||current->firstchild==NULL)
     {
         current=NULL; return false; //觉得书上这样不太好，把current置为空不如保留它不变
     }
    current=current->firstchild;
    return true;

}

template<class T> bool tree<T>::Nextsibing()
{
    if(current==NULL||current->nextsibing==NULL)
    {
        current=NULL;
        return false;
    }

    current=current->nextsibing;
    return true;
}

template<class T> void tree<T>::removesubtree(treenode<T> *r)
{
    if(r!=NULL)
    {
        removesubtree(r->nextsibing);
        removesubtree(r->firstchild);
        delete []r;
    }
}

/**template<class T> void tree<T>::removesubtree(treenode<T>* r)
{ //这个是第二次自己复习时的思路
    treenode<T> *temp1,*temp2;
    if(r)
    {
        temp1=r->nextsibing;
        temp2=r->firstchild;
        delete []r;
        removesubtree(temp1);
        removesubtree(temp2);
    }
}**/

template<class T> bool tree<T>::Find(treenode<T> *r,T value)  //自己写的查找指定值的算法
{
    if(r)
    {
         if(r->data==value)
          {
               current=r;
               return true;
          }

          if(Find(r->nextsibing,value)==true)
              return true;
          if(Find(r->firstchild,value)==true)
                return true;
          return false;
    }
    return false;  //如果没有这条语句，就会出问题
}

/**template<class T> void tree<T>::Find(treenode<T>* r,T value) //这个函数也是自己写的，如果结点存在也能查到，
{                                                               //但是如果不存在是无法判别的，
    if(r)                                                       //另外，不管有没有对应结点，它都会把整个树遍历完
    {                                                           //因此有bool返回值，会更好，不管是答案还是自己写的
        current=r;
        return;
    }
    Find(r->nextsibing,value);
    Find(r->firstchild,value);
}**/
/**template<class T> bool tree<T>::Find(treenode<T> *r,T value)
{  //在“根为r的子树”当中查找结点值为value的结点
   //书上的这个算法是先遍历长子女结点，然后再遍历子女结点的兄弟结点，看起来比较高大上。
    bool result=false;
    if(r->data==value)
    {
        result=true;
        current=r;
    }
    else
    {
        treenode<T> *q=r->firstchild;
        while(q&&!(result=Find(q,value)))  //如果长子不存在，那其他孩子也不存在，因此这个比较高效
        {                                  //而且不管是在最后长子还是在最后兄弟，都能够通过这个循环结束
            q=q->nextsibing;               //因为判断了q是否为空。b
        }
    }
    return result; //书上这个result的用法也比较巧
}**/

template<class T> bool  tree<T>::Find(T value)
{
    if(isempty())
        return  false;
    return Find(root,value);
    //有了引用或者是类的成员数据，返回bool类型对于查找或许会有帮助
}

template<class T> bool tree<T>::FindParent(treenode<T> *t,treenode<T> *p)  //经过验证发现这里是正确的
{    //这个代码的思路是先看第一个孩子，然后再去查看其他的孩子
    treenode<T> *temp=t->firstchild;
    if(temp==p) //这个是自己加的
    {
        current=t; //emm，这个地方大家竟然都没看出来
        return true;
    }
    while(temp&&temp!=p)     //这个地方也是很巧妙，如果temp不存在那就没有兄弟，也就不用去管了。
    {
        if(FindParent(temp,p)==true)
           return true;
        else
            temp=temp->nextsibing;
        if(temp&&temp==p)
        {
            current=t;
            return true;
        }
        /*else
        {
            current=NULL;
            return true;
        }*/
    }
    return false;  //书上是else那一部分，自己暂且修改成这样，这一部分以后学习数据结构时候重点解决
}

template<class T> bool tree<T>::Parent()
{
    treenode<T> *p=current;
    if(!current||current==root)
        return false;
    return FindParent(root,p);
}

template<class T> void tree<T>::creat_tree(treenode<T> *&pointer,istream &in)
{
    T temp;
    in>>temp;
    if(temp!='#')
    {
        pointer=new treenode<T>(temp,NULL,NULL);
        creat_tree(pointer->nextsibing,in);
        creat_tree(pointer->firstchild,in);
    }
}
//emmm,树的建立和遍历都是自己想出来的。厉害了，我的博
template<class T> void tree<T>::print_tree(treenode<T> *pointer,ostream &out)
{
    if(pointer)
    {
        out<<pointer->data<<" ";
        print_tree(pointer->nextsibing,out);
        print_tree(pointer->firstchild,out);
    }
}


template<class T> void tree<T>::print_current()
{
    cout<<current->data<<endl;
}
