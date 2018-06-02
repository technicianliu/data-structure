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
        treenode<T> *root,*current;  //�������͵�ǰָ����,���õ�ǰ�����Ϊ�������в�������
        void creat_tree(treenode<T> *&pointer,istream &in);
        void print_tree(treenode<T> *pointer,ostream &out);
        bool Find(treenode<T> *r,T value); //����rΪ�����������
        void removesubtree(treenode<T> *r); //ɾ����rΪ������
        bool FindParent(treenode<T> *t,treenode<T> *p);
    public:
        tree():root(NULL),current(NULL) {}
        tree(tree<T> &r);
        ~tree();

        bool isempty() {return root==NULL;}
        bool Firstchild(); //Ѱ�ҵ�ǰ����һ������ʹ���Ϊ��ǰ��㡣
        bool Nextsibing(); //Ѱ����һ���ֵ�ʹ���Ϊ��ǰ���
        bool Parent(); //Ѱ��˫�׽��ʹ���Ϊ��ǰ���
        bool Find(T value); //����ֵΪvalue�Ľ��

        void print_current(); //��ӡ����ǰ����е����ݡ�

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
         current=NULL; return false; //��������������̫�ã���current��Ϊ�ղ��籣��������
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
{ //����ǵڶ����Լ���ϰʱ��˼·
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

template<class T> bool tree<T>::Find(treenode<T> *r,T value)  //�Լ�д�Ĳ���ָ��ֵ���㷨
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
    return false;  //���û��������䣬�ͻ������
}

/**template<class T> void tree<T>::Find(treenode<T>* r,T value) //�������Ҳ���Լ�д�ģ����������Ҳ�ܲ鵽��
{                                                               //����������������޷��б�ģ�
    if(r)                                                       //���⣬������û�ж�Ӧ��㣬�������������������
    {                                                           //�����bool����ֵ������ã������Ǵ𰸻����Լ�д��
        current=r;
        return;
    }
    Find(r->nextsibing,value);
    Find(r->firstchild,value);
}**/
/**template<class T> bool tree<T>::Find(treenode<T> *r,T value)
{  //�ڡ���Ϊr�����������в��ҽ��ֵΪvalue�Ľ��
   //���ϵ�����㷨���ȱ�������Ů��㣬Ȼ���ٱ�����Ů�����ֵܽ�㣬�������Ƚϸߴ��ϡ�
    bool result=false;
    if(r->data==value)
    {
        result=true;
        current=r;
    }
    else
    {
        treenode<T> *q=r->firstchild;
        while(q&&!(result=Find(q,value)))  //������Ӳ����ڣ�����������Ҳ�����ڣ��������Ƚϸ�Ч
        {                                  //���Ҳ�����������ӻ���������ֵܣ����ܹ�ͨ�����ѭ������
            q=q->nextsibing;               //��Ϊ�ж���q�Ƿ�Ϊ�ա�b
        }
    }
    return result; //�������result���÷�Ҳ�Ƚ���
}**/

template<class T> bool  tree<T>::Find(T value)
{
    if(isempty())
        return  false;
    return Find(root,value);
    //�������û�������ĳ�Ա���ݣ�����bool���Ͷ��ڲ��һ�����а���
}

template<class T> bool tree<T>::FindParent(treenode<T> *t,treenode<T> *p)  //������֤������������ȷ��
{    //��������˼·���ȿ���һ�����ӣ�Ȼ����ȥ�鿴�����ĺ���
    treenode<T> *temp=t->firstchild;
    if(temp==p) //������Լ��ӵ�
    {
        current=t; //emm������ط���Ҿ�Ȼ��û������
        return true;
    }
    while(temp&&temp!=p)     //����ط�Ҳ�Ǻ�������temp�������Ǿ�û���ֵܣ�Ҳ�Ͳ���ȥ���ˡ�
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
    return false;  //������else��һ���֣��Լ������޸ĳ���������һ�����Ժ�ѧϰ���ݽṹʱ���ص���
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
//emmm,���Ľ����ͱ��������Լ�������ġ������ˣ��ҵĲ�
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
