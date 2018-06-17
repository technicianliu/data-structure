//学习数据结构这段时间学到一个好的点是在处理问题的过程中为了方便
//或者是不破坏原有数据常常需要引入辅助变量来帮助自己解决问题。

#include <iostream>
using namespace std;

const int default_vertices=30;  //默认图中最多三十个顶点

typedef struct     //Kruskal算法存放边的辅助数组，把边从图的邻接矩阵中拿出来可以大大提高时间效率
{
    int v1,v2; //分别存放边的两个顶点
    int weight;    //存放边的权值
}Edge_set;
Edge_set edge_set[default_vertices*default_vertices];  //设置成全局变量，让各个函数都可以访问。
int n=0; //统计边的条数，传值给quick_sort()函数

typedef struct       //prim算法的辅助数组。
{
    int vex;        //存放边的一个顶点，vex在已产生的最小生成树顶点集合中
    int lowcost;    //边的代价
}Closedge[default_vertices];
Closedge closedge;
//类内成员函数可以使用外部的全局变量。也可以把上面这两个类型加在类里面成为类的成员数据



const int max_weight=999; //用999代表无穷大，该值表示顶点之间不存在边或者弧

template<class T,class E> class Graphmtx
{
     private:
        T *vertices_list; //顶点序列表
        E edge[default_vertices+1][default_vertices+1]; //邻接矩阵,序号从一开始
        int max_vertices; //图中最大顶点数
        int num_edges;  //当前边数
        int num_vertices; //当前顶点数
        int direction; //0:有向图；1:无向图
        int get_vertex_pos(T vertex)//给出当前结点vertex在图中位置
        {
            for(int i=1;i<=num_vertices;i++)
                if(vertices_list[i]==vertex)
                   return i;
            return -1; //表示没有找到
        }

     public:
        Graphmtx(int sz=default_vertices,int d=0); //构造函数，默认构造无向图
        ~Graphmtx() {delete []vertices_list;}
        int number_of_vertices() {return num_vertices;} //获取图中结点数
        int number_of_edges() {return num_edges;}
        T get_value(int i) const {return vertices_list[i];}
        E get_weight(int v1,int v2) const {return edge[v1][v2];} //取边(v1,v2)值
        int get_first_neighbor(int v) const; //取顶点v的第一个邻接点序号
        int get_next_neighbor(int v1,int v2) const; //取顶点v的临接点w的下一个邻接点序号
        bool insert_vertex(const T data);  //插入一个顶点v
        bool insert_edge(int v1,int v2,E cost); //插入边或者弧。
        bool remove_vertex(int v); //删除顶点及相关的边或者弧
        bool remove_edge(int v1,int v2); //删除边或者弧

        void prim(T vertex);  //用prim算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
        int32_t mininum(); //求closedge中lowlost的最小正值，并返回其在数组中的序号。

        void Kruskal();       //下面五个函数都是为了实现Kruskal算法，是自己思路
        void get_all_edge();  //下面三个函数是为了实现自己的想法所写。
        void quick_sort(Edge_set edge_set[],int s,int e);
        void Swap(Edge_set &a,Edge_set &b);
        void insert_sort(Edge_set edge_set[],int n); //这个插入排序是和书上的算法一致。

        void Dijkstra(const int v);  //求顶点v到其他顶点的最短路径

        void Floyd();     //这三个函数求解图中任意两个顶点之间的最短路径
        void display_path(int D[][default_vertices],int path[][default_vertices],int n);
        void p_path(int path[][default_vertices],int i,int j);




        friend istream& operator>>(istream& in,Graphmtx<T,E> &G)//建立图的邻接矩阵
        {
            int i,j,k,n,m;
            T e1,e2; E weight;
            cout<<"direction or unfirection?"<<endl;
            in>>G.direction;
            cout<<"input the number of vertex:"<<endl;
            in>>n;
            for(i=1;i<=n;i++)
            {
                cout<<"input"<<i<<":";
                in>>e1;
                G.insert_vertex(e1);
            }
            i=1;
            cout<<"input the number of edge:"<<endl;
            in>>m;
            while(i<=m)  //输入顶点和建立顶点联系分开比较容易处理。
            {
                cout<<"input two vertexs and weight:";
                in>>e1>>e2>>weight;
                j=G.get_vertex_pos(e1);
                k=G.get_vertex_pos(e2);
                G.insert_edge(j,k,weight);
                ++i;
            }
            return in;
        }

        friend ostream& operator<<(ostream& out,Graphmtx<T,E> &G)//输出图信息
        {
            int16_t i,j,n,m;
            T e1,e2;
            E w;
            n=G.number_of_vertices();
            m=G.number_of_edges();
            out<<"graph has"<<n<<"vertexs,"<<m<<"edges."<<endl;
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
               {
                   if(i==j)
                     continue;

                    w=G.get_weight(i,j);
                    if(w!=max_weight)
                    {
                         e1=G.get_value(i); e2=G.get_value(j);
                         if(G.direction)
                            out<<"("<<e1<<","<<e2<<","<<w<<")"<<endl;
                         else
                            out<<"("<<e1<<","<<e2<<","<<w<<")"<<endl;
                    }

               }
               return out;
        }

};


template<class T,class E> Graphmtx<T,E>::Graphmtx(int sz,int d)
{
    max_vertices=sz;
    direction=d;
    num_edges=0;
    num_vertices=0;
    vertices_list=new T[max_vertices+1];

    for(int i=1;i<=max_vertices;i++)
    {
        for(int j=1;j<=max_vertices;j++)
        {
            if(i==j)
                edge[i][j]=0;
            else
                edge[i][j]=max_weight;
        }
    }
}

template<class T,class E> int Graphmtx<T,E>::get_first_neighbor(int v) const
{
    //获取v的第一个临接点序号，若没有，返回-1；
    if(v<1||v>num_vertices)
        return -1;
    for(int i=1;i<=num_vertices;i++)
        if(edge[v][i]>0&&edge[v][i]<max_weight)
           return i;
    return -1;
}


template<class T,class E> int Graphmtx<T,E>::get_next_neighbor(int v1,int v2) const
{
    if(v1<1||v1>num_vertices||v2<1||v2>=num_vertices)
        return -1;
    for(int i=v2+1;i<num_vertices;i++)
        if(edge[v1][i]>0&&edge[v1][i]<max_weight)
          return i;
    return -1;
}

template<class T,class E> bool Graphmtx<T,E>::insert_vertex(const T data)
{
     if(num_vertices==max_vertices)
            return false;
     vertices_list[++num_vertices]=data;
     return true;
}

template<class T,class E> bool Graphmtx<T,E>::insert_edge(int v1,int v2,E cost)
{
    //这个操作要判断图的类型，对于无向图来说，在添加(v1,v2)的同时，要添加(v2,v1);
    //边或者弧总数都是增加一。无向图的邻接矩阵是对称矩阵。
    if(v1<1||v1>num_vertices||v2<1||v2>num_vertices)
    {
        return false;
    }
    if(direction==0)
    {
        edge[v1][v2]=cost;
        edge[v2][v1]=cost;
    }
    else
    {
        edge[v1][v2]=cost;
    }
    ++num_edges;
    return true;
}

/**template<class T,class E> bool Graphmtx<T,E>::insert_edge(int v1,int v2,E cost)
{
    if(v1>=1&&v1<=num_vertices&&v2>=1&&v2<=num_vertices&&edge[v1][v2]==max_weight)
    {
        if(!direction)
            edge[v2][v1]=cost;
        edge[v1][v2]=cost;
        return true;
        ++num_edges;
    }
    return false;
}**/

/**template<class T,class E> bool Graphmtx<T,E>::remove_vertex(int v)
{  //这是自己最初写的算法，这个完全错误，因为没有考虑到顶点序列表
   //和邻接矩阵的一一对应关系。
    if(v<1||v>num_vertices)
        return false;
    for(int i=v;i<num_vertices;i++)
    {
        vertices_list[i]=vertices_list[i+1];
    }
    --sum_vertices;

    if(!direction)
    {
        for(int i=1;i<=num_vertices;i++)
        {
            if(edge[i][v]!=0)
                num_edges--;
            edge[i][v]=0;
        }
    }
    for(int i=0;i<=num_vertices;i++)
    {
        if(edge[v][i]!=0)
            num_edges--;
        edge[v][i]=0;
    }
    return 0;
}**/
//这个操作很容易出错，需要小心处理
//(1)将顶点表中最后一个顶点替换原有的顶点
//(2)对于无向图，要删除与v相关的边;对于有向图，既要删除从v出去的出弧
//   又要删除进入v的入弧，删除同时边或者弧减一
//   这里的删除只是体现在边数或者弧数减值，邻接矩阵中元素并未改变
//(3)用最后一列替换第v列
//(4)顶点个数减一
//(5)用最后一行替代第v行
template<class T,class E> bool Graphmtx<T,E>::remove_vertex(int v)
{
    if(v<1||v>num_vertices)
        return false;
    vertices_list[v]=vertices_list[num_vertices];

    for(int i=1;i<=num_edges;i++)
    {
        if(edge[i][v]>0&&edge[v][i]<max_weight)
        {
             num_edges--;
             if(direction)
                num_edges--;
        }
    }

    for(int i=1;i<=num_vertices;i++)
    {
        edge[v][i]=edge[num_vertices][i];
    }
    for(int i=1;i<=num_vertices;i++)
    {
        edge[i][v]=edge[i][num_vertices];
           //num_edges++;这里不可以再增加了，再增加是多余的
    }

    num_vertices--;//减少顶点个数这个操作需要放在后面，不然就影响前面四步的操作了。
}

template<class T,class E> bool Graphmtx<T,E>::remove_edge(int v1,int v2)
{
    if(v1>=1&&v1<=num_vertices&&v2>=1&&v2<=num_vertices)
    {
        if(!direction)
            edge[v2][v1]=max_weight; //无向图要删除对称边。
        edge[v1][v2]=max_weight;
        --num_edges;
        return true;
    }
    return true;
}


//以下四种产生最小生成树的算法并不难移植到邻接表中去
/**template<class T,class E> void Graphmtx<T,E>::prim(T vertex)
{
     int u=get_vertex_pos(vertex);
     if(u<1||u>num_vertices)
        return;

     int i,j,k=u;
     for(j=1;j<=num_vertices;j++)  //用邻接矩阵初始化从顶点u出发的各个连通边
     {
         closedge[j].vex=u;
         closedge[j].lowcost=get_weight(k,j);
     }
     closedge[k].lowcost=0;     //顶点自身除外

     for(i=1;i<=num_vertices-1;i++)
     {
         k=mininum();   //取得代价最小的边。
         cout<<"("<<vertices_list[closedge[k].vex]<<"---"
             <<vertices_list[k]<<")"<<" ";
         closedge[k].lowcost=0;   //将k顶点并入U集
         for(j=1;j<=num_vertices;j++)
         {
             if(edge[k][j]<closedge[j].lowcost)
             {
                 closedge[j].vex=k;
                 closedge[j].lowcost=edge[k][j];
             }
         }
     }
}

template<class T,class E> int Graphmtx<T,E>::mininum()
{
     int i=1,j,k,Min;
     while(i<=num_vertices&&!closedge[i].lowcost) //该数组在函数外定义
     {
         ++i;
     }
     Min=closedge[i].lowcost;     //第一个不为0的值
     k=i;
     for(j=i+1;j<=num_vertices;j++)
     {
         if(closedge[j].lowcost>0&&Min>closedge[j].lowcost)  //用k保存最小代价边对应的在V-U中的那个顶点。
         {
             Min=closedge[j].lowcost;
             k=j;
         }
     }
     return k;

}**/


//这个是自己的想法，生成树就是指无向图的对应的树：
//自己虽然按照prim算法写，但是需要判断是否会形成环的问题。没有用好MST性质。

//虽然可以生成最小生成树，但是破坏了原有的图，解决方法是
//创建一个新的edge数组来存放原有的边，对新的数组操作
/**template<class T,class E> void Graphmtx<T,E>::prim(T vertex)
{
    int u=get_vertex_pos(vertex);
    if(u<1||u>num_vertices)
        return;

    int vest[num_vertices+1];
    for(int i=1;i<=num_vertices;i++)
        vest[i]=i;

    int U[default_vertices],k=0;  //U数组存放已经在生成树的顶点在图中的序号

    U[++k]=u;

    while(k<num_vertices)
    {
        int m,n,lowcost=max_weight; //在U中每一个顶点与外界顶点的集合中找出代价最小的边
        for(int i=1;i<=k;i++)
        {
            for(int j=1;j<=num_vertices;j++)
            {
                if(edge[U[i]][j]<=lowcost&&edge[U[i]][j]!=0)
                {
                  lowcost=edge[U[i]][j];
                  m=U[i];
                  n=j;
                }
            }
        }

        if(vest[m]!=vest[n])
        {
            vest[n]=vest[m];
            U[++k]=n;
            edge[m][n]=max_weight;
            edge[n][m]=max_weight;
            cout<<"("<<m<<"---"<<n<<")";
        }
        else
        {
            edge[m][n]=max_weight;
            edge[n][m]=max_weight;
        }
    }
    return;
}**/


/**template<class T,class E> void Graphmtx<T,E>::get_all_edge()    //下面四个函数是自己实现的，用来实现Kruskal算法
{
    for(int i=1;i<=num_vertices;i++)
    {
        for(int j=1;j<=num_vertices;j++)
        {
            if(edge[i][j]!=0&&edge[i][j]!=max_weight)
            {
                edge_set[++n].v1=i;
                edge_set[n].v2=j;
                edge_set[n].weight=edge[i][j];
                edge[j][i]=0;    //这样可能会破坏原有的图，但是很容易修复。而且这一部分数据要不要都无所谓
            }
        }
    }
}

template<class T,class E> void Graphmtx<T,E>::Swap(Edge_set &a,Edge_set &b)
{
    Edge_set temp;
    temp=a;
    a=b;
    b=temp;
}

template<class T,class E> void Graphmtx<T,E>::quick_sort(Edge_set edge_set[],int s,int e)
{
    if(s<e)
    {
        int i=s,j=e;
        Edge_set k;
        k=edge_set[s];
        while(i!=j)
        {
            while(i<j&&edge_set[j].weight>=k.weight)
                j--;

            Swap(edge_set[i],edge_set[j]);

            while(i<j&&edge_set[i].weight<k.weight)
                i++;

            Swap(edge_set[i],edge_set[j]);

        }

        quick_sort(edge_set,s,i-1);
        quick_sort(edge_set,i+1,e);
    }
    return;
}

template<class T,class E> void Graphmtx<T,E>::Kruskal()
{
    get_all_edge();
    quick_sort(edge_set,1,n);

    //for(int i=1;i<=n;i++)    //利用打印中间结果的方法，找到错误原因。
      //cout<<edge_set[i].v1<<" "<<edge_set[i].v2<<" "<<edge_set[i].weight<<endl;

    int vest[num_vertices+1];
    for(int i=1;i<=num_vertices;i++)  //将其初始化，这样就有num_vertices个连通分量
        vest[i]=i;
    int key=num_vertices; //key表示生成树中连通分量的个数，如果key==1，说明最小生成树已经完成。
    for(int i=1;i<=n&&key!=1;i++)  //一共有n条边，全都访问看看
    {
        if(vest[edge_set[i].v1]!=vest[edge_set[i].v2])   //对于自己来说这一部分也很容易出错，调试很长时间
        {                                                //不管怎么说，不看书自己写还是很有成就感的
            cout<<"("<<vertices_list[edge_set[i].v1]<<"---"<<vertices_list[edge_set[i].v2]<<")"<<" ";
            for(int j=1;j<=num_vertices;j++)
            {
                if(vest[j]==vest[edge_set[i].v2])
                {
                   vest[j]=vest[edge_set[i].v1];
                }
            }
            key--;
        }


    }

    return;
}**/           //自己这个想法与书上的差不多，只是在实现细节上有一些差异。

template<class T,class E> void Graphmtx<T,E>::insert_sort(Edge_set edge_set[],int n)
{
    int i,j;
    Edge_set temp;
    for(i=2;i<=n;i++)
    {
        j=i-1;
        temp=edge_set[i];
        while(j>=1&&edge_set[j].weight>=temp.weight)
        {
            edge_set[j+1]=edge_set[j];
            --j;
        }
        edge_set[j+1]=temp;
    }
}

template<class T,class E> void Graphmtx<T,E>::Kruskal()
{
    int k=0;
    for(int i=1;i<=num_vertices;i++)  //先把边拿出来，自己写了一个函数来实现，这里利用矩阵对称性简化
    {
        for(int j=i+1;j<=num_vertices;j++)
        {
            if(edge[i][j]!=0&&edge[i][j]!=max_weight)
            {
                 edge_set[++k].v1=i;  //k就表示了边的条数
                 edge_set[k].v2=j;
                 edge_set[k].weight=edge[i][j];
            }
        }
    }



    int vest[num_vertices+1];
    for(int i=1;i<=num_vertices;i++)
        vest[i]=i;

    insert_sort(edge_set,k);

    k=0;  int j=1;
    int u,v;
    while(k<=num_vertices-1)  //书上判断最小生成树处理完成的方式和自己所想的不一样
    {
        u=edge_set[j].v1;
        v=edge_set[j].v2;
        if(vest[u]!=vest[v])
        {
            cout<<"("<<vertices_list[u]<<"---"<<vertices_list[v]<<")"
                <<" ";
            ++k;

            for(int i=1;i<=num_vertices;i++)
            {
                if(vest[i]==vest[v])
                    vest[i]=vest[u];
            }
        }
        ++j; //while循环特别容易忘记这一步
    }
}


//Dijkstra算法求解单源最短路径。
template<class T,class E> void Graphmtx<T,E>::Dijkstra(const int v)
{
    int u;
    int S[default_vertices];   //判断顶点是否已找到最短路径
    int dist[default_vertices]; //存放v到各个顶点的最短路径
    int path[default_vertices]; //存放路径中顶点前面那个顶点的序号

    for(int i=1;i<=num_vertices;i++)
    {
        S[i]=0;
        dist[i]=edge[v][i];
        if(i!=v&&edge[v][i]<max_weight&&edge[v][i]>0)
            path[i]=v;
        else
            path[i]=-1;
    }

    S[v]=1;

    for(int i=1;i<=num_vertices-1;i++)
    {
        int Min=max_weight;
        for(int j=1;j<=num_vertices;j++)
        {
            if(!S[j]&&dist[j]<Min)
            {
                Min=dist[j];
                u=j;
            }
        }

        S[u]=1;

        for(int j=1;j<=num_vertices;j++)
        {
            if(!S[j]&&edge[u][j]<max_weight&&edge[u][j]+dist[u]<dist[j])  //这里只对那些还没有求到最短路径的顶点进行更新
            {
                 dist[j]=dist[u]+edge[u][j];
                 path[j]=u;
            }
        }
    }

    for(int j=1;j<=num_vertices;j++)
    {
        if(j!=v)
        {
            cout<<j<<"("<<vertices_list[j]<<","<<dist[j]<<")-->";

            for(u=path[j];u!=-1;u=path[u])
            {
                cout<<u<<"("<<vertices_list[u]<<")"<<"-->";
            }
        }
        cout<<endl;
    }

    return;
}

//Floyed算法求解每对顶点之间的最短路径，递推的动态规划算法
//假设有向图G=(V,E)采用邻接矩阵存储图的顶点和边的信息
template<class T,class E> void Graphmtx<T,E>::Floyd()
{
    int D[default_vertices][default_vertices];
    int path[default_vertices][default_vertices];

    for(int i=1;i<=num_vertices;i++)
    {
        for(int j=1;j<=num_vertices;j++)
        {
            D[i][j]=edge[i][j];
            path[i][j]=-1;
        }
    }

    for(int k=1;k<=num_vertices;k++)
    {
        for(int i=1;i<=num_vertices;i++)
        {
            for(int j=1;j<=num_vertices;j++)
            {
                if(D[i][j]>D[i][k]+D[k][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=k;
                }
            }
        }
    }

    display_path(D,path,num_vertices);
}

template<class T,class E> void Graphmtx<T,E>::display_path(int D[][default_vertices],int path[][default_vertices],int n)
{
    for(int i=1;i<=num_vertices;i++)
    {
        for(int j=1;j<=num_vertices;j++)
        {
            if(D[i][j]==max_weight)
            {
                if(i!=j)
                {
                    cout<<"从顶点"<<vertices_list[i]<<"到顶点"<<vertices_list[j]<<"没有路径！"<<endl;
                }
            }
            else
            {
                if(i!=j)
                {
                     cout<<"从顶点"<<vertices_list[i]<<"到顶点"<<vertices_list[j]<<"最短路径是"<<D[i][j];
                     cout<<"("<<vertices_list[i]<<"--->";
                     p_path(path,i,j);
                     cout<<vertices_list[j]<<")"<<endl;
                }
            }
        }
    }
}

template<class T,class E> void Graphmtx<T,E>::p_path(int path[][default_vertices],int i,int j)
{
    int k=path[i][j];
    if(k==-1)  //表示这两个点之间没有别的点
        return;
    p_path(path,i,k);
    cout<<vertices_list[k]<<"--->";
    p_path(path,k,j);
}


