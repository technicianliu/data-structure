/*ֻҪ֪���˸��������������Ϳ��Է���ĴӸ��������ҵ��������������µ���һ����㡣��ˣ����������а�������㣬������������������/ɾ����㣬�����������Լ����Һ���/˫�׵Ȳ���*/
#include <iostream>
#include <algorithm>
#include "treenode.h"
#include "stack.h"
#include "quene.h"
using namespace std;

template<class T> class binarytree
{

     friend istream& operator>>(istream &in,binarytree<T> &tree)//����������
    {
        cout<<"���������������˳������������еĽ��ֵ:"<<endl;

        tree.creatbinarytree(in,tree.root);
        return in;
    }
    friend ostream& operator<<(ostream &out,binarytree<T> &tree)//���������
    {
        out<<"�Թ���������������"<<endl;
        tree.printbinarytree(tree.root,out);
        out<<endl;
        return out;
    }

    private:
        treenode<T> *root; //�����������
        T refvalue; //��������ֹͣ��־
        void creatbinarytree(istream &in,treenode<T> *&tmp); //ǰ�����������
        void traverse(treenode<T> *tmp,ostream &out) const; //ǰ��������������
        void preorder(treenode<T> *tmp) const; //ǰ��������ݹ��㷨
        void inorder(treenode<T> *tmp) const;  //����������ݹ��㷨
        void postorder(treenode<T> *tmp) const; //����������ݹ��㷨
        int Size(treenode<T> *tmp) const; //�����Ϊtmp�Ķ������������ݹ��㷨
        int Height(treenode<T> *tmp) const; //�����Ϊtmp�Ķ�������ȵݹ��㷨
        void printbinarytree(treenode<T> *tmp,ostream &out); //�Թ������ʽ����������ݹ��㷨

    public:
        binarytree() {root=NULL;}
        binarytree(T flag):refvalue(flag),root(NULL){}  //����ն����������ñ�־
        binarytree(T flag,T value,treenode<T> *left,treenode<T> *right);
        ~binarytree();
        int Height() const {return Height(root);}
        int Size() const {return Size(root);} //���ض������н�����
        bool isempty() {return root==NULL;}
        treenode<T>* parent(treenode<T> *subtree,treenode<T> *pcurrent); //���ش�subtree������pcurrent����˫�׵�ַ
        treenode<T>* getroot() const {return root;} //��ȡ������λ��
        //void printbinarytree() const {printbinarytree(root);}  //�Թ������ʽ���������
        void preorder() const {preorder(root);} //ǰ�������������
        void inorder() const {inorder(root);} //�������������
        void postorder() const {postorder(root);} //���������������
        void levelorder() const;             //��α�����������
        void inorderstack();
};

template<class T> binarytree<T>::binarytree(T flag,T value,treenode<T> *left,treenode<T> *right)
{
    root=new treenode<T>(value,left,right);
    refvalue=flag;
}

template<class T> binarytree<T>::~binarytree()
{
    if(root)
    {
        root->Release();
        delete root;
        root=NULL;
    }

}

//��������Ľṹ��û��ָ��˫�µ�������ˣ����ҵ�ǰ����˫�ױ����ָ�����subtree��ʼ���������������������������������ж��������Ľ������Һ����Ƿ��뵥ǰ�������pcurrent��ͬ������ͬ����������Ľ�㣬��Ϊ��ǰ����˫�׽�㣻�����ͬ��������������������ָ��Ϊ�գ���˵����ǰ���Ϊ����㣬û��˫�׽�㡣
template<class T> treenode<T>* binarytree<T>::parent(treenode<T> *subtree,treenode<T> *pcurrent)
{
       if(!subtree)
             return NULL; //���һ�����Ǹ���㣬��һ������Ϊ�������������������û�������������ĵݹ���޷����У��Լ�д����������û�뵽�ȿ�����������Ȼ����ȥ������������

       if(subtree->leftchild==pcurrent||subtree->rightchild==pcurrent)
             return subtree;

       treenode<T> *temp;

       if((temp=parent(subtree->leftchild,pcurrent))!=NULL)  //���˼·���Ȱ������������꣬Ȼ���ٿ�����������������һ������temp��������ֱ�ӷ��أ�������������ֱ�ӷ���
             return temp;
       else
             return parent(subtree->rightchild,pcurrent);
}

//������������ָ��ѭĳ�ִ������ζԶ�������ÿ���ڵ����һ���ҽ���һ�η��ʡ��Ӷ������Ķ����֪��һ�ŷǿյĶ������ɸ���㼰�����������������ֹ��ɡ���ˣ�����������Ľ���ϣ����԰�ĳ�ִ���ִ������������(1),���ʽ�㱾��(V).(2),�����ý���������(L).(3)�������ý���������(R).��������һ������������ˣ�����VLR(ǰ�����)��LVR(�������)��LRV(�������)���������ֱ�����ǰ���ֵľ���
template<class T> void binarytree<T>::preorder(treenode<T> *tmp) const //ǰ������ݹ��㷨
{
    if(tmp)
    {
        cout<<tmp->data<<" ";  //���ʸ����
        preorder(tmp->leftchild); //������������
        preorder(tmp->rightchild);
    }
}

template<class T> void binarytree<T>::inorder(treenode<T> *tmp) const
{
    if(tmp->leftchild)
        inorder(tmp->leftchild);

    cout<<tmp->data<<" ";

    if(tmp->rightchild)
        inorder(tmp->rightchild);
}

/*template<class T> void binarytree<T>::inorder(treenode<T> *tmp) const
{
    if(tmp)
    {
        inorder(tmp->leftchild);
        cout<<tmp->data<<" ";
        inorder(tmp->rightchild);
    }
}*/

template<class T> void binarytree<T>::postorder(treenode<T> *tmp) const
{
    if(tmp)
    {
        postorder(tmp->leftchild);
        postorder(tmp->rightchild);
        cout<<tmp->data<<" ";
    }
}

//������Ͳ�ͬ������ķ�ʽҲ��ͬ��Ϊ�����ӳ��������ԣ����ʽ��Ĳ�������һ������ָ����ʵ�֣��滻�����е�cout��䡣


//Ӧ�ö�������ǰ������ĵݹ��㷨���Խ���һ�Ŷ��������ڴ˹����У��������˳������Ӧ������ǰ����������˳�򣬲�Լ�������������в����ܳ��ֵ�ֵ��Ϊ�ݹ������־
//�㷨˼·��
//(1),���������ַ����ǽ�����ʶ�����ͽ���һ����㣬��ֵΪ������ַ���������Ϊ�գ�ת��(2);�����˳���ǰ�ĵݹ���ã����ϵͳջ���޽����ڣ��������ݹ���̽�����
//(2),�Խ����Ľ����Ϊ����㣬���ַͨ�������������Ͳ���tmpֱ����������Ϊʵ�ʲ�����ָ�뵱��
//(3),ת��(1),�ֱ��tmpָ��Ľ�㽨������������
//�������룺Mab##c##d#ef###. ���������־һ������������� ���Ҫ����ֹ���������������ͱ�����һ��#
 template<class T> void binarytree<T>::creatbinarytree(istream &in,treenode<T> *&tmp)
 {
     T temp;
     in>>temp;

     if(temp!=refvalue)
     {
         tmp=new treenode<T>(temp);

         if(tmp)
         {
             creatbinarytree(in,tmp->leftchild);
             creatbinarytree(in,tmp->rightchild);
         }

     }
     else
        tmp=NULL;
 }

 //����ǰ��������������������
 //�����������ù��Ǳ�������:�������Ϊ�����ı�������������������ɵı��ǰ�棬��������һ��Բ�����������ġ�

 //�㷨˼·��
 //(1),�������ǿգ������������ֵ�������˳���ǰ����
 //(2),����������ȫΪ��������������������������������������ǰҪ�ȴ�ӡ"(",�������������Ҫ��ӡ��)����(������������������������Ҫ��ӡ��)��)��������������η���������
 //   ~���������ǿգ���Ѹý����Ϊ����㣬ת��(2)���������ݹ�����������Ρ��������������������һ�����������ֽڷ�","��
 //   ~���������ǿգ���Ѹý����Ϊ����㣬ת��(2)���������ݹ������������

 template<class T> void binarytree<T>::printbinarytree(treenode<T> *tmp,ostream &out)
 {
     if(tmp)
     {
         out<<tmp->data;
         if(tmp->leftchild||tmp->rightchild)
         {
             out<<"(";
             if(tmp->leftchild)
             {
                 printbinarytree(tmp->leftchild,out);

                 if(tmp->rightchild)  //�����б�Ҫ��һ���жϣ���Ȼ�ָ�����������Ƕ���ġ�
                    out<<",";
             }

             printbinarytree(tmp->rightchild,out);
             out<<")";
         }
     }
     else
        return;
 }

template<class T> int binarytree<T>::Size(treenode<T> *tmp) const
{
    if(!tmp)
        return 0;
    else
        return Size(tmp->leftchild)+Size(tmp->rightchild)+1;
}

template<class T> int binarytree<T>::Height(treenode<T> *tmp) const
{
    int leftheight,rightheight;
    if(!tmp)
        return 0;
    else
    {
         leftheight=Height(tmp->leftchild);
         rightheight=Height(tmp->rightchild);
         return max(leftheight,rightheight)+1;
    }
}

template<class T> void binarytree<T>::traverse(treenode<T> *tmp,ostream &out) const
 {
     if(tmp)
    {
        out<<tmp->data<<" ";  //���ʸ����
        traverse(tmp->leftchild); //������������
        traverse(tmp->rightchild);
    }
 }


 /*�����������ķǵݹ��㷨��ͨ�����������ݹ��㷨��ִ�й��̣��۲�ջ�ı仯��ֱ��д�����ķǵݹ��㷨*/


//����ջʵ�ֶ������е���������ǵݹ��㷨
//�����������ķǵݹ��㷨��������ջ�������ݽṹ���ݹ���������ת����Ϊ�ǵݹ���������
//����������ݹ��㷨ִ�й����еݹ鹤��ջ��״̬���Եó���������ͷ��ʽ��Ĵ���ǡ���෴�������ڵݹ�ת�������У��������ջ���õ��������ķǵݹ��㷨


//�㷨˼·��   �����ݽṹ�ϵ�ջ��ģ��ݹ���õ�ջ���Դ���ʵ�ַǵݹ��㷨��
//(1),��ʼ��ջ(ջ�е�Ԫ�ص�����ӦΪ����ַ����������)��ָ��pָ������
//(2),���ջ�գ�����pҲΪ�գ�˵��û�н����Է��ʣ������������
//    �����������p�ǿգ���ת��(3)�����pΪ�ն�ջ�ǿգ���ת��(4);
//(3),p��ָ�������зǿ��������ν�ջ(p���������ƶ�)����pΪ�գ�˵��
//    ջ��ָ����ָ��������������������Ӧ�ó�ջ���ҷ��ʴ˸���㣬����
//    pָ���������������ת��(2),����������������
//(4),���������������أ���ǰ��ı���������Ӧ������ջ�����ʴ˸���㣬����p
//    ָ���������������ת��(2),������������������
template<class T> void binarytree<T>::inorderstack()
{
    Seqstack<treenode<T>*> S; //ջ��Ԫ��Ϊ����ָ������
    treenode<T> *p;
    if(!root)
        return;
    p=root;
    while(!S.isempty()||p)
    {
        while(p)            //���������������Ļ����ǵ�������������ϣ�p���Ϊ�գ�����ֱ�ӵ�������㣬֮��pΪ�������ĸ����
        {
            S.push(p);
            p=p->leftchild;
        }
        if(!S.isempty())
        {
            S.pop(p);
            cout<<p->data<<" ";
        }

        p=p->rightchild;  //��ʼ����ĳһ����������������
    }
}

/*�������ĺ�������ǵݹ��㷨�Ƚϸ��ӣ��ڱ��������������ܷ��ʸ���㣬��Ҫ�ٱ�����������������������ſ��Է��ʸ���㣬���ԣ�����������һ��ջ���־ͬʱ��¼����Ǵ����������Ǵ����������أ��������ָ�����ջʱ����־Ҳͬʱ����ջ*/


//�������Ĳ�α���:�Ӹ���㿪ʼ�����϶��£�ͬ����������
//�㷨˼·��
//(1)�������ǿգ�����������У����򣬱�������
//(2)�����в��ն�����һ�����ָ������У�������ָ����ָ��㡣���ý���������Ҳ�ǿգ������������������У�
//   ���ý����������ǿգ��������������ָ�������
//(3),�ظ�(2),ֱ�����п�Ϊֹ

template<class T> void binarytree<T>::levelorder() const
{
    seqquene<treenode<T>*> S;
    treenode<T> *temp;
    if(!root)
        return;
    temp=root;
    S.enquene(temp);
    while(!S.isempty())  //���п�Ϊ�㷨����������
    {
        S.dequene(temp);
        cout<<temp->data<<" ";
        if(temp->leftchild)
        {
            S.enquene(temp->leftchild);
        }
        if(temp->rightchild)
        {
            S.enquene(temp->rightchild);
        }

    }

    cout<<endl;
}
