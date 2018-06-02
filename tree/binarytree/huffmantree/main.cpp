#include <iostream>
#include "huffman.h"
using namespace std;

int main()
{
    HuffmanTree<char> H;
    HuffmanCode code;
    char a[10];
    char data[]={' ','a','b','c','d','e','f'};
    unsigned weight[]={0,1,2,3,4,5,6};
    H.CreatHuffmanTree(data,weight,6);
    H.HuffmanCoding(code,6);
    H.HuffmanUncoding(code,6,a);
    H.PrintHuffmanTree(code,6);
    cout<<endl;
    for(int i=1;i<=6;i++)
        cout<<a[i]<<" ";
}


