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
//这个的输出还需要完善 没有区分有向和无向；
