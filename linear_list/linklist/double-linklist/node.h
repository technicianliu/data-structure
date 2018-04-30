
#include <iostream>
using namespace std;

template<class T> class linklist;

template<class T> class node
{
   friend class linklist<T>;
   private:
       node<T> *prior,*next;
       T data;
   public:
       node(){prior=NULL;next=NULL;}
       node(T &item,node<T> *pt1,node<T> *pt2):data(item),prior(pt1),next(pt2){}

};
