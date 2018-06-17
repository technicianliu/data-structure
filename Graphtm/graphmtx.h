//ѧϰ���ݽṹ���ʱ��ѧ��һ���õĵ����ڴ�������Ĺ�����Ϊ�˷���
//�����ǲ��ƻ�ԭ�����ݳ�����Ҫ���븨�������������Լ�������⡣

#include <iostream>
using namespace std;

const int default_vertices=30;  //Ĭ��ͼ�������ʮ������

typedef struct     //Kruskal�㷨��űߵĸ������飬�ѱߴ�ͼ���ڽӾ������ó������Դ�����ʱ��Ч��
{
    int v1,v2; //�ֱ��űߵ���������
    int weight;    //��űߵ�Ȩֵ
}Edge_set;
Edge_set edge_set[default_vertices*default_vertices];  //���ó�ȫ�ֱ������ø������������Է��ʡ�
int n=0; //ͳ�Ʊߵ���������ֵ��quick_sort()����

typedef struct       //prim�㷨�ĸ������顣
{
    int vex;        //��űߵ�һ�����㣬vex���Ѳ�������С���������㼯����
    int lowcost;    //�ߵĴ���
}Closedge[default_vertices];
Closedge closedge;
//���ڳ�Ա��������ʹ���ⲿ��ȫ�ֱ�����Ҳ���԰��������������ͼ����������Ϊ��ĳ�Ա����



const int max_weight=999; //��999��������󣬸�ֵ��ʾ����֮�䲻���ڱ߻��߻�

template<class T,class E> class Graphmtx
{
     private:
        T *vertices_list; //�������б�
        E edge[default_vertices+1][default_vertices+1]; //�ڽӾ���,��Ŵ�һ��ʼ
        int max_vertices; //ͼ����󶥵���
        int num_edges;  //��ǰ����
        int num_vertices; //��ǰ������
        int direction; //0:����ͼ��1:����ͼ
        int get_vertex_pos(T vertex)//������ǰ���vertex��ͼ��λ��
        {
            for(int i=1;i<=num_vertices;i++)
                if(vertices_list[i]==vertex)
                   return i;
            return -1; //��ʾû���ҵ�
        }

     public:
        Graphmtx(int sz=default_vertices,int d=0); //���캯����Ĭ�Ϲ�������ͼ
        ~Graphmtx() {delete []vertices_list;}
        int number_of_vertices() {return num_vertices;} //��ȡͼ�н����
        int number_of_edges() {return num_edges;}
        T get_value(int i) const {return vertices_list[i];}
        E get_weight(int v1,int v2) const {return edge[v1][v2];} //ȡ��(v1,v2)ֵ
        int get_first_neighbor(int v) const; //ȡ����v�ĵ�һ���ڽӵ����
        int get_next_neighbor(int v1,int v2) const; //ȡ����v���ٽӵ�w����һ���ڽӵ����
        bool insert_vertex(const T data);  //����һ������v
        bool insert_edge(int v1,int v2,E cost); //����߻��߻���
        bool remove_vertex(int v); //ɾ�����㼰��صı߻��߻�
        bool remove_edge(int v1,int v2); //ɾ���߻��߻�

        void prim(T vertex);  //��prim�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
        int32_t mininum(); //��closedge��lowlost����С��ֵ�����������������е���š�

        void Kruskal();       //���������������Ϊ��ʵ��Kruskal�㷨�����Լ�˼·
        void get_all_edge();  //��������������Ϊ��ʵ���Լ����뷨��д��
        void quick_sort(Edge_set edge_set[],int s,int e);
        void Swap(Edge_set &a,Edge_set &b);
        void insert_sort(Edge_set edge_set[],int n); //������������Ǻ����ϵ��㷨һ�¡�

        void Dijkstra(const int v);  //�󶥵�v��������������·��

        void Floyd();     //�������������ͼ��������������֮������·��
        void display_path(int D[][default_vertices],int path[][default_vertices],int n);
        void p_path(int path[][default_vertices],int i,int j);




        friend istream& operator>>(istream& in,Graphmtx<T,E> &G)//����ͼ���ڽӾ���
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
            while(i<=m)  //���붥��ͽ���������ϵ�ֿ��Ƚ����״���
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

        friend ostream& operator<<(ostream& out,Graphmtx<T,E> &G)//���ͼ��Ϣ
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
    //��ȡv�ĵ�һ���ٽӵ���ţ���û�У�����-1��
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
    //�������Ҫ�ж�ͼ�����ͣ���������ͼ��˵�������(v1,v2)��ͬʱ��Ҫ���(v2,v1);
    //�߻��߻�������������һ������ͼ���ڽӾ����ǶԳƾ���
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
{  //�����Լ����д���㷨�������ȫ������Ϊû�п��ǵ��������б�
   //���ڽӾ����һһ��Ӧ��ϵ��
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
//������������׳�����ҪС�Ĵ���
//(1)������������һ�������滻ԭ�еĶ���
//(2)��������ͼ��Ҫɾ����v��صı�;��������ͼ����Ҫɾ����v��ȥ�ĳ���
//   ��Ҫɾ������v���뻡��ɾ��ͬʱ�߻��߻���һ
//   �����ɾ��ֻ�������ڱ������߻�����ֵ���ڽӾ�����Ԫ�ز�δ�ı�
//(3)�����һ���滻��v��
//(4)���������һ
//(5)�����һ�������v��
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
           //num_edges++;���ﲻ�����������ˣ��������Ƕ����
    }

    num_vertices--;//���ٶ���������������Ҫ���ں��棬��Ȼ��Ӱ��ǰ���Ĳ��Ĳ����ˡ�
}

template<class T,class E> bool Graphmtx<T,E>::remove_edge(int v1,int v2)
{
    if(v1>=1&&v1<=num_vertices&&v2>=1&&v2<=num_vertices)
    {
        if(!direction)
            edge[v2][v1]=max_weight; //����ͼҪɾ���ԳƱߡ�
        edge[v1][v2]=max_weight;
        --num_edges;
        return true;
    }
    return true;
}


//�������ֲ�����С���������㷨��������ֲ���ڽӱ���ȥ
/**template<class T,class E> void Graphmtx<T,E>::prim(T vertex)
{
     int u=get_vertex_pos(vertex);
     if(u<1||u>num_vertices)
        return;

     int i,j,k=u;
     for(j=1;j<=num_vertices;j++)  //���ڽӾ����ʼ���Ӷ���u�����ĸ�����ͨ��
     {
         closedge[j].vex=u;
         closedge[j].lowcost=get_weight(k,j);
     }
     closedge[k].lowcost=0;     //�����������

     for(i=1;i<=num_vertices-1;i++)
     {
         k=mininum();   //ȡ�ô�����С�ıߡ�
         cout<<"("<<vertices_list[closedge[k].vex]<<"---"
             <<vertices_list[k]<<")"<<" ";
         closedge[k].lowcost=0;   //��k���㲢��U��
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
     while(i<=num_vertices&&!closedge[i].lowcost) //�������ں����ⶨ��
     {
         ++i;
     }
     Min=closedge[i].lowcost;     //��һ����Ϊ0��ֵ
     k=i;
     for(j=i+1;j<=num_vertices;j++)
     {
         if(closedge[j].lowcost>0&&Min>closedge[j].lowcost)  //��k������С���۱߶�Ӧ����V-U�е��Ǹ����㡣
         {
             Min=closedge[j].lowcost;
             k=j;
         }
     }
     return k;

}**/


//������Լ����뷨������������ָ����ͼ�Ķ�Ӧ������
//�Լ���Ȼ����prim�㷨д��������Ҫ�ж��Ƿ���γɻ������⡣û���ú�MST���ʡ�

//��Ȼ����������С�������������ƻ���ԭ�е�ͼ�����������
//����һ���µ�edge���������ԭ�еıߣ����µ��������
/**template<class T,class E> void Graphmtx<T,E>::prim(T vertex)
{
    int u=get_vertex_pos(vertex);
    if(u<1||u>num_vertices)
        return;

    int vest[num_vertices+1];
    for(int i=1;i<=num_vertices;i++)
        vest[i]=i;

    int U[default_vertices],k=0;  //U�������Ѿ����������Ķ�����ͼ�е����

    U[++k]=u;

    while(k<num_vertices)
    {
        int m,n,lowcost=max_weight; //��U��ÿһ����������綥��ļ������ҳ�������С�ı�
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


/**template<class T,class E> void Graphmtx<T,E>::get_all_edge()    //�����ĸ��������Լ�ʵ�ֵģ�����ʵ��Kruskal�㷨
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
                edge[j][i]=0;    //�������ܻ��ƻ�ԭ�е�ͼ�����Ǻ������޸���������һ��������Ҫ��Ҫ������ν
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

    //for(int i=1;i<=n;i++)    //���ô�ӡ�м����ķ������ҵ�����ԭ��
      //cout<<edge_set[i].v1<<" "<<edge_set[i].v2<<" "<<edge_set[i].weight<<endl;

    int vest[num_vertices+1];
    for(int i=1;i<=num_vertices;i++)  //�����ʼ������������num_vertices����ͨ����
        vest[i]=i;
    int key=num_vertices; //key��ʾ����������ͨ�����ĸ��������key==1��˵����С�������Ѿ���ɡ�
    for(int i=1;i<=n&&key!=1;i++)  //һ����n���ߣ�ȫ�����ʿ���
    {
        if(vest[edge_set[i].v1]!=vest[edge_set[i].v2])   //�����Լ���˵��һ����Ҳ�����׳������Ժܳ�ʱ��
        {                                                //������ô˵���������Լ�д���Ǻ��гɾ͸е�
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
}**/           //�Լ�����뷨�����ϵĲ�ֻ࣬����ʵ��ϸ������һЩ���졣

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
    for(int i=1;i<=num_vertices;i++)  //�Ȱѱ��ó������Լ�д��һ��������ʵ�֣��������þ���Գ��Լ�
    {
        for(int j=i+1;j<=num_vertices;j++)
        {
            if(edge[i][j]!=0&&edge[i][j]!=max_weight)
            {
                 edge_set[++k].v1=i;  //k�ͱ�ʾ�˱ߵ�����
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
    while(k<=num_vertices-1)  //�����ж���С������������ɵķ�ʽ���Լ�����Ĳ�һ��
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
        ++j; //whileѭ���ر�����������һ��
    }
}


//Dijkstra�㷨��ⵥԴ���·����
template<class T,class E> void Graphmtx<T,E>::Dijkstra(const int v)
{
    int u;
    int S[default_vertices];   //�ж϶����Ƿ����ҵ����·��
    int dist[default_vertices]; //���v��������������·��
    int path[default_vertices]; //���·���ж���ǰ���Ǹ���������

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
            if(!S[j]&&edge[u][j]<max_weight&&edge[u][j]+dist[u]<dist[j])  //����ֻ����Щ��û�������·���Ķ�����и���
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

//Floyed�㷨���ÿ�Զ���֮������·�������ƵĶ�̬�滮�㷨
//��������ͼG=(V,E)�����ڽӾ���洢ͼ�Ķ���ͱߵ���Ϣ
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
                    cout<<"�Ӷ���"<<vertices_list[i]<<"������"<<vertices_list[j]<<"û��·����"<<endl;
                }
            }
            else
            {
                if(i!=j)
                {
                     cout<<"�Ӷ���"<<vertices_list[i]<<"������"<<vertices_list[j]<<"���·����"<<D[i][j];
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
    if(k==-1)  //��ʾ��������֮��û�б�ĵ�
        return;
    p_path(path,i,k);
    cout<<vertices_list[k]<<"--->";
    p_path(path,k,j);
}


