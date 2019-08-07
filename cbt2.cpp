
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
using namespace std;

struct subunit
{
    int data; // # of mototrs
    int loc; // pointer to the tree position

    subunit(int key)
    {
        data = key;
    }

};

struct cbt
{
    vector<vector<int>> tree; int depth;

    cbt(int max_size) // max_size is the maximum length the filament can get
    {
        depth = (int) log2(max_size); int l; 

        for(int i = 0; i <= depth; i++)
        {
            l = (int) pow(2,i);
            tree.push_back(vector<int>(l,0));
        }
    }

    void init_tree(vector<subunit> &v)
    {
        for(int i = 0; i < v.size(); i++)
        {
            tree[depth][i/2] += v[i].data;
            v[i].loc = i/2;
        }

        for(int i = depth-1; i >= 0; i--)
        {
            for(int j = 0; j < tree[i].size(); j++)
            {
                tree[i][j] = tree[i+1][2*j] + tree[i+1][2*j + 1];
            }
        }
    }
};
