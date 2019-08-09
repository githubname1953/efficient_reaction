#include<iostream>
#include<cmath>
#include<vector>
#include<deque>
#include<algorithm>
#include "cbt2.cpp"
using namespace std;

int main()
{
    int N=2; int s=1;
    deque<int> fil(10);
    for(int i=0; i<10; i++) fil[i]=i;
    cbt graph(18,10);
    graph.init_tree(fil);

    graph.display();
    for(int i=0; i<10; i++) cout<<fil[i]<<'\t';
    cout<<endl;

    cout<<endl;
    graph.update1(fil[5],1);

    graph.display();
    for(int i=0; i<10; i++) cout<<fil[i]<<'\t';
    cout<<endl;

    cout<<endl;
    graph.update1(fil[0],1);

    graph.display();
    for(int i=0; i<10; i++) cout<<fil[i]<<'\t';
    cout<<endl;

    cout<<endl;
    graph.transport(N,s,fil);

    graph.display();
    for(int i=0; i<10; i++) cout<<fil[i]<<'\t';
    cout<<endl;

    cout<<endl;
    graph.remove(fil);

    graph.display();
    for(int i=0; i<fil.size(); i++) cout<<fil[i]<<'\t';
    cout<<endl;
    cout<<*(graph.ll[0].locp)<<endl;

    cout<<endl;
    graph.remove(fil);

    graph.display();
    for(int i=0; i<fil.size(); i++) cout<<fil[i]<<'\t';
    cout<<endl;

    cout<<endl;
    graph.insert(fil);

    graph.display();
    for(int i=0; i<fil.size(); i++) cout<<fil[i]<<'\t';
    cout<<endl;
    cout<<*(graph.ll[graph.ll.size()-1].locp)<<endl;

    return 0;
}