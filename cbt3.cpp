
/*
    In a complete binary tree every level, except possibly the last, is completely filled,
    and all nodes in the last level are as far left as possible.
    It can have between 1 and 2h nodes at the last level h.
    An alternative definition is a perfect tree whose rightmost leaves (perhaps all) have been removed.
    Some authors use the term complete to refer instead to a perfect binary tree as defined above,
    in which case they call this type of tree an almost complete binary tree or nearly complete binary tree.
*/

/* NOTE: HOW THE CODE WORKS
Below is a shitty version of a complete binary tree for length changing filaments.

We need to know the maximum length the filament can reach beforehand to initialize the tree as all the 
values(# no of motors) of the filament subunits are ensured to be at the bottommost level of the tree.

To make things easier, we define a small struct called subunit.   

*/

#include<iostream>
#include<cmath>
#include<vector>
#include <boost/circular_buffer.hpp>
#include<algorithm>
using namespace std;

inline unsigned int id(unsigned int i, unsigned int j)
{
    return ((1<<i)^1) + j;
} 

struct subunit
{
    int data; // # of motors
    boost::circular_buffer<int>::iterator locp; // pointer to the tree position

    subunit(int key)
    {
        data = key;
    }

};

struct cbt
{
    int* tree; int depth; long long int size;
    boost::circular_buffer<int>::iterator next; 
    vector<subunit> ll; // ll = last level of the tree

    cbt(int max_size, int init_size) // max_size is the maximum length the filament can get
    {
        depth = (int) log2(max_size); int l;
        size = (long long int) pow(2,depth+1); size--;
        tree = new int[size];
        for(int i = 0; i < size; i++) tree[i] = 0;

        ll.resize(max_size, subunit(0));
        ll.resize(init_size, subunit(0));
    }

    void init_tree(boost::circular_buffer<int> &dq)
    {
        for(int i = 0; i < ll.size(); i++)
        {
            tree[id(depth,i/2)] += ll[i].data;
        }

        // for(int i = depth-1; i >= 0; i--)
        // {
        //     for(int j = 0; j < pow(2,i); j++)
        //     {
        //         tree[id(i,j)] = tree[id(i+1,2*j)] + tree[id(i+1,2*j + 1)];
        //     }
        // }

        for(int i = 0; i < ll.size(); i++)
        {
            ll[i].locp = dq.begin() + i;
        }
    }

    void update(int pos, int value)
    { 
        int diff = value - ll[pos].data;
        int p = pos>>1;

        for(int i = depth; i >= 0; i--)
        {
            tree[id(i,p)] += diff;
            p = p>>1;
        }

        ll[pos].data = value;
    }

    void update1(int pos, int value)
    { 
        int p = pos>>1;

        for(int i = depth; i >= 0; i--)
        {
            tree[id(i,p)] += value;
            p = p>>1;
        }

        ll[pos].data += value;
    }

    void insert(boost::circular_buffer<int> &dq)
    {
        ll.push_back(subunit(0));
        dq.push_back(ll.size()-1);
        ll[ll.size()-1].locp = dq.end() - 1;
        // update(ll.size()-1,0); // only call when the value is non-zero
    }

    void remove(boost::circular_buffer<int> &dq)
    {
        int pos = dq[0];
        ll[pos].locp = ll[ll.size()-1].locp;
        *ll[pos].locp = pos;
        //ll[ll.size()-1].locp = dq.begin();
        update(pos, ll[ll.size()-1].data);
        update(ll.size()-1, 0);
        dq.pop_front();
        ll.pop_back();
    }

    void transport(int &n, int &state, boost::circular_buffer<int> &dq)
    {
        int j = 0;
        for(int i = 0; i < depth; i++)
        {
            if(n <= tree[id(i+1,2*j)])
            {
                j = 2*j;
            }
            else
            {
                n -= tree[id(i+1,2*j)];
                j = 2*j + 1;
            } 
        }

        if(n <= ll[2*j].data) j = 2*j;
        else j = 2*j+1;

        next = ll[j].locp + 1; 
        update1(j,-1);
        if(next!=dq.end()) update1(*next,1);
        else state = 0;
    }

    // void display()
    // {
    //     for(int i=0;i<=depth;i++)
    //     {
    //         for(int j=0; j<pow(2,i);j++)
    //         {
    //             cout<<tree[i][j]<<'\t';
    //         }
    //         cout<<endl;
    //     }
    //     for(int i=0;i<ll.size();i++)
    //     {
    //         cout<<ll[i].data<<'\t';
    //     }
    //     cout<<endl;
        
    // }

    ~cbt()
    {
        delete tree;
    }

};
