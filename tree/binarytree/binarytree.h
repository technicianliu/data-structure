/*只要知道了根结点的左右链，就可以方便的从根结点出发找到他的左右子树下的任一个结点。因此，二叉树类中包括根结点，操作包括建树，插入/删除结点，遍历二叉树以及查找孩子/双亲等操作*/
#include <iostream>
#include <algorithm>
#include "treenode.h"
#include "stack.h"
#include "quene.h"
using namespace std;

template<class T> class binarytree
{

     friend istream& operator>>(istream &in,binarytree<T> &tree)//重载输入流
    {
        cout<<"按二叉树先序遍历顺序输入二叉树中的结点值:"<<endl;

        tree.creatbinarytree(in,tree.root);
        return in;
    }
    friend ostream& operator<<(ostream &out,binarytree<T> &tree)//重载输出流
    {
        out<<"以广义表输出二叉树："<<endl;
        tree.printbinarytree(tree.root,out);
        out<<endl;
        return out;
    }

    private:
        treenode<T> *root; //二叉树根结点
        T refvalue; //数据输入停止标志
        void creatbinarytree(istream &in,treenode<T> *&tmp); //前序遍历次序建树
        void traverse(treenode<T> *tmp,ostream &out) const; //前序遍历输出二叉树
        void preorder(treenode<T> *tmp) const; //前序遍历结点递归算法
        void inorder(treenode<T> *tmp) const;  //中序遍历结点递归算法
        void postorder(treenode<T> *tmp) const; //后序遍历结点递归算法
        int Size(treenode<T> *tmp) const; //计算根为tmp的二叉树结点个数递归算法
        int Height(treenode<T> *tmp) const; //计算根为tmp的二叉树深度递归算法
        void printbinarytree(treenode<T> *tmp,ostream &out); //以广义表形式输出二叉树递归算法

    public:
        binarytree() {root=NULL;}
        binarytree(T flag):refvalue(flag),root(NULL){}  //构造空二叉树，设置标志
        binarytree(T flag,T value,treenode<T> *left,treenode<T> *right);
        ~binarytree();
        int Height() const {return Height(root);}
        int Size() const {return Size(root);} //返回二叉树中结点个数
        bool isempty() {return root==NULL;}
        treenode<T>* parent(treenode<T> *subtree,treenode<T> *pcurrent); //返回从subtree出发，pcurrent结点的双亲地址
        treenode<T>* getroot() const {return root;} //获取根结点的位置
        //void printbinarytree() const {printbinarytree(root);}  //以广义表形式输出二叉树
        void preorder() const {preorder(root);} //前序遍历二叉树。
        void inorder() const {inorder(root);} //中序遍历二叉树
        void postorder() const {postorder(root);} //后序遍历二叉树。
        void levelorder() const;             //层次遍历二叉树。
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

//二叉链表的结构中没有指向双新的链，因此，查找当前结点的双亲必须从指定结点subtree开始，对其左右子树进行搜索，在搜索中判断搜索到的结点的左右孩子是否与单前给定结点pcurrent相同，若相同，搜索到达的结点，即为当前结点的双亲结点；如果不同，则继续搜索。如果搜索指针为空，则说明当前结点为根结点，没有双亲结点。
template<class T> treenode<T>* binarytree<T>::parent(treenode<T> *subtree,treenode<T> *pcurrent)
{
       if(!subtree)
             return NULL; //这个一方面是根结点，另一方面是为了下面的左子树遍历，没有这个条件下面的递归就无法进行，自己写不出来就是没想到先考虑左子树，然后再去考虑右子树。

       if(subtree->leftchild==pcurrent||subtree->rightchild==pcurrent)
             return subtree;

       treenode<T> *temp;

       if((temp=parent(subtree->leftchild,pcurrent))!=NULL)  //这个思路是先把左子树遍历完，然后再考虑右子树，必须有一个变量temp，不可以直接返回，但右子树可以直接返回
             return temp;
       else
             return parent(subtree->rightchild,pcurrent);
}
//这个是自己写出的寻找双亲的代码
/*tempalte<class T> treenode<T>* binarytree<T>::parent(treenode<T> *subtree,treenode<T> *current)
{
     treenode<T> *temp=NULL;
     if(subtree)
     {
          if(subtree->leftchild==current||subtree->rightchild==tree)
               return temp=subtree;
          temp=parent(->subtree->leftchild,current);
          if(temp!=NULL)
               return temp;
          temp=parent(subtree->rightchild,current)
     }
     return temp;
}*/

//二叉树遍历是指遵循某种次序，依次对二叉树中每个节点均做一次且仅做一次访问。从二叉树的定义可知，一颗非空的二叉树由根结点及左右子树这三个部分构成。因此，在任意给定的结点上，可以按某种次序执行三个操作：(1),访问结点本身(V).(2),遍历该结点的左子树(L).(3)，遍历该结点的右子树(R).二叉树是一种有序树，因此，仅有VLR(前序遍历)，LVR(中序遍历)，LRV(后序遍历)，另外三种遍历是前三种的镜像。
template<class T> void binarytree<T>::preorder(treenode<T> *tmp) const //前序遍历递归算法
{
    if(tmp)
    {
        cout<<tmp->data<<" ";  //访问根结点
        preorder(tmp->leftchild); //遍历左右子树
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

//结点类型不同，输出的方式也不同。为了增加程序的灵活性，访问结点的操作可用一个函数指针来实现，替换代码中的cout语句。


//应用二叉树的前序遍历的递归算法可以建立一颗二叉树。在此过程中，输入结点的顺序必须对应二叉树前序遍历后结点的顺序，并约定以输入序列中不可能出现的值作为递归结束标志
//算法思路：
//(1),如果读入的字符不是结束标识符，就建立一个结点，其值为读入的字符，左右链为空，转到(2);否则，退出当前的递归调用，如果系统栈中无结点存在，则整个递归过程结束。
//(2),以建立的结点作为根结点，其地址通过函数的引用型参数tmp直接链传到作为实际参数的指针当中
//(3),转入(1),分别对tmp指向的结点建立左右子树。
//关于输入：Mab##c##d#ef###. 这里结束标志一定是连续输入的 因此要想终止继续生成左子树就必须有一个#
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

 //利用前序遍历输出二叉树的树形
 //二叉树可以用广仪表来描述:根结点作为广义表的表名放在由左右子树组成的表的前面，而表是用一对圆括号括起来的。

 //算法思路：
 //(1),当根结点非空，则输出根结点的值；否则，退出当前遍历
 //(2),若左右子树全为空则无需输出；否则，在输出左子树或者右子树前要先打印"(",在输出右子树后要打印“)”，(若无右子树，输出左子树后就要打印“)”)输出左右子树树形分两步处理
 //   ~若左子树非空，则把该结点作为根结点，转至(2)对左子树递归输出子树树形。若存在右子树，则添加一个左右子树分节符","。
 //   ~若右子树非空，则把该结点作为根结点，转至(2)对右子树递归输出子树树形

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

                 if(tmp->rightchild)  //这里有必要做一下判断，不然分隔符的输出就是多余的。
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
        out<<tmp->data<<" ";  //访问根结点
        traverse(tmp->leftchild); //遍历左右子树
        traverse(tmp->rightchild);
    }
 }


 /*二叉树遍历的非递归算法。通过事例分析递归算法的执行过程，观察栈的变化，直接写出它的非递归算法*/


//利用栈实现二叉树中的中序遍历非递归算法
//二叉树遍历的非递归算法就是运用栈这种数据结构将递归的中序遍历转换成为非递归的中序遍历
//从中序遍历递归算法执行过程中递归工作栈的状态可以得出，保存结点和访问结点的次序恰好相反，所以在递归转换过程中，必须借助栈来得到二叉树的非递归算法


//算法思路：   用数据结构上的栈来模拟递归调用的栈，以此来实现非递归算法。
//(1),初始化栈(栈中的元素的类型应为结点地址，即二叉链)，指针p指向根结点
//(2),如果栈空，并且p也为空，说明没有结点可以访问，则中序遍历结
//    束；否则，如果p非空，则转向(3)；如果p为空而栈非空，则转向(4);
//(3),p所指结点的所有非空左链依次进栈(p沿着左链移动)，当p为空，说明
//    栈顶指针所指的左子树遍历结束，就应该出栈并且访问此根结点，接着
//    p指向根结点的右子树，转向(2),继续遍历该右子树
//(4),表明从右子树返回，则当前层的遍历结束，应继续出栈并访问此根结点，接着p
//    指向根结点的右子树，转向(2),继续遍历该右子树。
template<class T> void binarytree<T>::inorderstack()
{
    Seqstack<treenode<T>*> S; //栈中元素为结点的指针类型
    treenode<T> *p;
    if(!root)
        return;
    p=root;
    while(!S.isempty()||p)
    {
        while(p)            //从左子树到根结点的机制是当左子树访问完毕，p结点为空，于是直接弹出根结点，之后p为右子树的根结点
        {
            S.push(p);
            p=p->leftchild;
        }
        if(!S.isempty())
        {
            S.pop(p);
            cout<<p->data<<" ";
        }

        p=p->rightchild;  //开始访问某一个根结点的右子树。
    }
}

/*二叉树的后序遍历非递归算法比较复杂，在遍历完左子树后不能访问根结点，需要再遍历右子树，右子树遍历完才可以访问根结点，所以，必须再设置一个栈或标志同时记录结点是从左子树还是从右子树返回，即当结点指针进出栈时，标志也同时进出栈*/


//二叉树的层次遍历:从根结点开始，自上而下，同层自左向右
//算法思路：
//(1)若根结点非空，则根结点进队列；否则，遍历结束
//(2)若队列不空队列中一个结点指针出队列，并访问指针所指结点。若该结点的左子树也非空，将左子树根结点进队列；
//   若该结点的右子树非空，则将右子树根结点指针入队列
//(3),重复(2),直至队列空为止

template<class T> void binarytree<T>::levelorder() const
{
    seqquene<treenode<T>*> S;
    treenode<T> *temp;
    if(!root)
        return;
    temp=root;
    S.enquene(temp);
    while(!S.isempty())  //队列空为算法结束条件。
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
