#include <iostream>
#include "tree.h"
using namespace std;

int main()
{
    tree<char> Tree;
    cin>>Tree;
    cout<<Tree;
    cout<<endl;
    char value='i';
    Tree.Find(value);
    Tree.print_current();
    Tree.Parent();
    Tree.print_current();
    return 0;
}
