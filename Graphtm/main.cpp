#include <iostream>
#include "graphmtx.h"
using namespace std;

int main()
{
    Graphmtx<int,int> G;
    cin>>G;
    //cout<<G;
    cout<<endl;
    //G.Kruskal();
    //G.Dijkstra(1);
    G.Floyd();
    return 0;
}
//������������Ҫ���� û���������������
