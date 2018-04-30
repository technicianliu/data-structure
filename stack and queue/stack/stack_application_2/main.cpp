/*括号匹配问题，在扫描语句时用，按照嵌套层次，由外到内依次得到
每个左括号；而在匹配过程中，要由内层到外层依次匹配每个括号，所以
此问题适合用栈来解决

1、括号的匹配过程与栈的特点一致，因此在算法中设置一个空栈。
2、每读入一个括号，若是右括号，则或者使至于栈顶的最急迫的期待得以消解，
或者是缺少左括号；若是左括号，则作为一个新的更急迫的期待压入栈中，自然
使原有栈中所有未消解的期待的急迫性都降了一级
3、重复2，直到读入结束。如果栈为空，则说明括号匹配成功，否则缺少左括号*/
#include <iostream>
#include "linkstack.h"
using namespace std;
//书上针对一种括号的情况使用swicth语句,若是三种情况都考虑，那个语句就显得很难处理。
int main()
{
    char ch[100],val;
    int i=0;
    linkedstack<char> stack1;
    cin.getline(ch,100);
    while(ch[i]!='\0')
    {
        if(ch[i]=='('||ch[i]==91||ch[i]==123)
        {
            stack1.push(ch[i]);
        }
        if(ch[i]==')'||ch[i]==93||ch[i]==125)
        {
            stack1.gettop(val);
            if((val==40&&ch[i]==41)||(val==91&&ch[i]==93)||(val==123&&ch[i]==125))
                stack1.pop(val);
        }
        i++;
    }

    if(stack1.isempty())
    {
        cout<<"macth well!"<<endl;
    }
    else
    {
        cout<<"don't macth well!"<<endl;
    }
    return 0;
}
