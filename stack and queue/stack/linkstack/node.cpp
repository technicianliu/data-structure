#include <iostream>
#include "node.h"
using namespace std;

template<class T> linkednode<T>::linkednode(linkednode<T> *ptr)
{
    link=ptr;
}

template<class T> linkednode<T>::linkednode(const T &item,linkednode<T> *ptr)
{
    data=item;
    link=ptr;
}



