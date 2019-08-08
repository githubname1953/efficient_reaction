
/*
    C++ Program to create a Complete Binary Tree.
    -Ajinkya Sonawane [AJ-CODE-7]

    In a complete binary tree every level, except possibly the last, is completely filled,
    and all nodes in the last level are as far left as possible.
    It can have between 1 and 2h nodes at the last level h.
    An alternative definition is a perfect tree whose rightmost leaves (perhaps all) have been removed.
    Some authors use the term complete to refer instead to a perfect binary tree as defined above,
    in which case they call this type of tree an almost complete binary tree or nearly complete binary tree.
*/

#include<iostream>
#include<cmath>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;

struct subunit
{
    int data; // # of mototrs
    deque<int>::iterator locp; // pointer to the tree position

    subunit(int key)
    {
        data = key;
    }

};

struct cbt
{
    vector<vector<int>> tree; int depth;
    vector<subunit> ll; // ll = last level of the tree

    cbt(int max_size, int init_size) // max_size is the maximum length the filament can get
    {
        depth = (int) log2(max_size); int l; 

        for(int i = 0; i <= depth; i++)
        {
            l = (int) pow(2,i);
            tree.push_back(vector<int>(l,0));
        }

        ll.resize(max_size, subunit(0));
        ll.resize(init_size, subunit(0));
    }

    void init_tree(deque<int> &dq)
    {
        for(int i = 0; i < ll.size(); i++)
        {
            tree[depth][i/2] += ll[i].data;
        }

        for(int i = depth-1; i >= 0; i--)
        {
            for(int j = 0; j < tree[i].size(); j++)
            {
                tree[i][j] = tree[i+1][2*j] + tree[i+1][2*j + 1];
            }
        }

        for(int i = 0; i < ll.size(); i++)
        {
            ll[i].locp = dq.begin() + i;
        }
    }

    void update(int pos, int value)
    { 
        int diff = value - ll[pos].data;
        int p = pos/2;

        for(int i = depth; i >= 0; i--)
        {
            tree[i][p] += diff;
            p = p/2;
        }

        ll[pos].data = value;
    }

    void update1(int pos, int value)
    { 
        int p = pos/2;

        for(int i = depth; i >= 0; i--)
        {
            tree[i][p] += value;
            p = p/2;
        }

        ll[pos].data += value;
    }

    void insert(deque<int> &dq)
    {
        ll.push_back(subunit(0));
        dq.push_back(ll.size()-1);
        ll[ll.size()-1].locp = dq.end() - 1;
        // update(ll.size()-1,0); // only caal when the value is non-zero
    }

    void remove(deque<int> &dq)
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

    void display()
    {
        for(int i=0;i<=depth;i++)
        {
            for(int j=0; j<tree[i].size();j++)
            {
                cout<<tree[i][j]<<'\t';
            }
            cout<<endl;
        }
        for(int i=0;i<ll.size();i++)
        {
            cout<<ll[i].data<<'\t';
        }
        cout<<endl;
        
    }

};
