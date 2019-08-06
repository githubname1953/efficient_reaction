#ifndef TREE_H__
#define TREE_H__
 
#include <list>
#include <iostream>
#include <cmath>
#include <functional> //less<T> <-> operator<
//you can #include <queue> and #include <stack> but no other STL
using std::list;
using std::cout;
using std::endl;
using std::less;
//function object used for comparison, default value is less
template <typename Comparable, typename Comparator=less<Comparable> >
class Tree
{
public:
  Tree();  //construct an empty tree
  Tree(const list<Comparable>&); //construct complete BST with min height based on list vals
  ~Tree(); //release all dynamically allocated memory
  void construct(const list<Comparable>&); //release own sources and get values from list
  const Comparable* findMin() const; //pointer to element that is minimal wrt Comparator,*implemented*
  const Comparable* findMax() const; //pointer to element that is maximal wrt Comparator,*implemented*
  const Comparable* getAddress(const Comparable&) const; //find pointer to element with given values
  bool contains(const Comparable*) const; //does this element with data exists in tree,*implemented*
  bool isEmpty() const; //is the tree empty,*implemented*
  void insert(const Comparable*); //insert if dereferenced argument's data is not present, update heights of those affected
  void remove(const Comparable*); //delete if dereferenced argument's data is present, update heights of those affected
  /* DO NOT FORGET TO CHECK BALANCE AND REBALANCE TREE IF NOT BALANCED AFTER INSERTION AND DELETION*/
  size_t getSize() const; //accessor to size,*implemented*
  int getHeight() const; //accessor  to height,*implemented*
  bool isBalanced() const; //accessor to balanced,*implemented*
  void print() const; //inorder print of dereferenced pointers held in nodes,*implemented*
  friend class MusicList; //MusicList class can access private parts of Tree
private:
  struct TreeNode  //scope Tree::TreeNode, thus is only public to Tree structure, no non-friend outsiders can see
  {                                             
    const Comparable* element; //adress of the item
    TreeNode* left; //pointer to the root of left subtree
    TreeNode* right; //pointer to the root of right subtree
    TreeNode* parent; //pointer to parent node, pay attention to this!
    size_t height; //height >= 0
    //constructor
    TreeNode(const Comparable* el,TreeNode* l, TreeNode* r, TreeNode* p)
    :element(el), left(l), right(r),parent(p)
    {
    }
    //you should separately set height values, no constructor is defined for them
  };
  TreeNode* root; //designated root
  /* isLessThan(const Comparable& lhs, const Comparable& rhs)
  * returns true if lhs<rhs and false otherwise*/
  Comparator isLessThan;
  size_t size; //number of nodes
  bool balanced;
  int myheight;
  /* uncopiable*/
  Tree(const Tree&); //disabled, provide no implementation
  Tree& operator=(const Tree&); //disabled, provide no implementation
  /* private utility functions*/
  TreeNode* sortedListToBST(typename list<Comparable>::const_iterator& , int , int ,int);
  TreeNode* sortedListToBSTtwo(typename list<const Comparable*>::const_iterator& , int , int ,int);
  void constructtwo(list<const Comparable*>& );
  TreeNode* findMin(TreeNode*) const; //recursively find min in (leftward) subtrees
  TreeNode* findMax(TreeNode*) const; //recursively find max in (rightward) subtrees
  void uphe(TreeNode*,int,int );
  int findmyHeight(TreeNode* );
  bool contains(const Comparable*, TreeNode*) const; //recursively search for an item
  TreeNode* traverseuph(TreeNode* t);
  TreeNode* mydelete(TreeNode* ,const Comparable* );
  bool isLeaf(TreeNode*) const; //isLeaf
  bool isFull(TreeNode*) const; //isFull
  void print(TreeNode*) const; //recursive print
  void destroy_tree(TreeNode*);
  int findmid(int);
  int bsttolist(TreeNode* ,list<const Comparable*>& ) ;
  const Comparable* findadd(TreeNode* t,const Comparable& item) const ;
   
   friend class MusicList;
  //define and use more as you may need
  template <typename T>  //templated max
  T max(T x, T y) { return x > y ? x : y; }                                              
  
}; //Do not modify method prototypes and data member names
 
 
//Below this point you should begin implementing the missing parts
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::Tree(){
  size = 0;
  balanced = 1;
  root=NULL;
}
 
//Complete the body of the constructor
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::Tree(const list<Comparable>& data){
 
  root = NULL;
  size = data.size();
  balanced = 1;
    int lstsize = data.size()-1;
    typename list<Comparable>::const_iterator itr=data.begin();
    root = sortedListToBST(itr,0,lstsize,ceil(log2(lstsize+1))-1);
    traverseuph(root);
}
//Complete the body of the constructor
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::construct(const list<Comparable>& data)
{
if(root!=NULL)
destroy_tree(root);
  root = NULL;
  size = data.size();
  balanced = 1;
    int lstsize = data.size()-1;
    typename list<Comparable>::const_iterator itr=data.begin();
    root = sortedListToBST(itr,0,lstsize,ceil(log2(lstsize+1))-1);
    traverseuph(root);
}                                               
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::sortedListToBST(typename list<Comparable>::const_iterator& copylist, int start, int end,int myheight) {
  if (start > end) return NULL;
  int mid =start +  findmid(end-start);
  TreeNode *leftChild = sortedListToBST(copylist, start, mid-1,myheight-1);
  TreeNode *giris = new TreeNode(&(*copylist),NULL,NULL,NULL);
  giris->left = leftChild;
  giris->height = myheight;
  if(leftChild!=NULL)
  leftChild->parent = giris;
  copylist++;
  giris->right = sortedListToBST(copylist, mid+1, end,myheight-1);
  if(giris->right!=NULL)
    giris->right->parent=giris;
  return giris;
}
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::constructtwo(list<const Comparable*>& data)
{
  root = NULL;
  size = data.size();
  balanced = 1;
    int lstsize = data.size()-1;
    typename list<const Comparable*>::const_iterator itr=data.begin();
    root = sortedListToBSTtwo(itr,0,lstsize,ceil(log2(lstsize+1))-1);
    traverseuph(root);
}
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::sortedListToBSTtwo(typename list<const Comparable*>::const_iterator& copylist, int start, int end,int myheight) {
  if (start > end) return NULL;
  int mid =start +  findmid(end-start);
  TreeNode *leftChild = sortedListToBSTtwo(copylist, start, mid-1,myheight-1);
  TreeNode *giris = new TreeNode((*copylist),NULL,NULL,NULL);
  giris->left = leftChild;
  giris->height = myheight;
  if(leftChild!=NULL)
  leftChild->parent = giris;
  copylist++;
  giris->right = sortedListToBSTtwo(copylist, mid+1, end,myheight-1);
  if(giris->right!=NULL)
    giris->right->parent=giris;
  return giris;
}                                               
 
template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::findmid(int n){
  int myh;
  int mid;
  n=n+1;
  myh=(log2(n+1));
  int x=pow(2,myh+1)-1;
  if(x>n){
    int nodeatmaxheight=pow(2,myh);
    int premax=pow(2,myh)-1;
    int artik= n-premax;
    if(artik>nodeatmaxheight/2)
      mid=premax/2+nodeatmaxheight/2;
    else
      mid=premax/2+artik;
  } else {
      mid = n/2;
  }
  return mid;
}
 
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::destroy_tree(TreeNode* t)
{
  if(t!=NULL)
  {
      destroy_tree(t->left);
      destroy_tree(t->right);
      if(t->left==NULL and t->right==NULL)
      delete t;
  }
}
 
 
template <typename Comparable, typename Comparator>
Tree<Comparable,Comparator>::~Tree()
{                                               
  destroy_tree(root);
}
 
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::uphe(TreeNode* t,int lh,int rh){ //update heights when new node inserted
  if((t->left==t->parent->left and lh>rh) or (t->right==t->parent->right and rh>lh) or rh==lh){
  t=t->parent;
  while(t->parent!=NULL){ //update heights up to root
    t->height=t->height+1;
    t=t->parent;
  }
  t->height = t->height+1;
  }
  int rooth = findmyHeight(root);
  root->height=rooth;
}
template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::findmyHeight(TreeNode* t) {
    if (t == NULL) {
        return -1;
    }
    int lefth = findmyHeight(t->left);
    int righth = findmyHeight(t->right);
    if (lefth > righth) {
        return lefth + 1;
    } else {
        return righth + 1;
    }
}
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::traverseuph(TreeNode* t) {
  if(t==NULL)
    return NULL;
  t->height=findmyHeight(t);
  if(t->left != NULL )
    t->left->parent = t;
  if(t->right != NULL )
    t->right->parent = t;
  traverseuph(t->left);
  traverseuph(t->right);
  return NULL;
}                                               
 
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::insert(const Comparable* data)
{
  if(!contains(data)){
  TreeNode* leaf;
  leaf = root;
  int lhh,rhh;
  if(root!=NULL){
  lhh=findmyHeight(root->left);
    rhh=findmyHeight(root->right);
  }
  if(root){
        while(leaf->right != NULL or leaf->left != NULL){
          if(isLessThan(*data,*(leaf->element))){
          if(leaf->left == NULL)
            break;
          leaf = leaf->left;
          }
          else{
          if(leaf->right == NULL)
            break;
          leaf = leaf->right;
          }
        }
        if(isLessThan(*data,*(leaf->element)))
        {
        leaf->left=new TreeNode(&(*data),NULL,NULL,leaf);
        leaf->left->height=0;
        uphe(leaf->left,lhh,rhh); 
        } else {
        leaf->right=new TreeNode(&(*data),NULL,NULL,leaf);
        leaf->right->height=0;
        uphe(leaf->right,lhh,rhh); 
        }
        size++;
  } else {                                              
    root = new TreeNode(&(*data),NULL,NULL,leaf);
    root->height = 0;
    size++;
  }
  //imbalance check
  if(size>1){
  int imb = findmyHeight(root)>=2*floor(log2(size));
  if(imb){
  list<const Comparable*> mlist;  
  bsttolist(root,mlist);
  destroy_tree(root);
  constructtwo(mlist);
  } else {
    traverseuph(root);
  }
  }
  }
} 
template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::bsttolist(TreeNode* t, list<const  Comparable*>& copylist) 
{
  if(t==NULL)
    return -1;
  bsttolist(t->left,copylist);
  copylist.push_back(t->element);
  bsttolist(t->right,copylist);
  return -1;
}
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::remove(const Comparable* data)
{
    if (contains(data))
    {
        if (size == 1 and (!isLessThan(*data, *root->element) and !isLessThan(*(root->element), *data)))
        {
            delete root;
            size = 0;
            balanced = 1;
            root = NULL;
        }
        else
        {
            size--;
            root = mydelete(root, data);
            traverseuph(root);
            root->parent = NULL;
            if (size > 1)
            {
                int imb = findmyHeight(root) >= 2 * floor(log2(size));
                if (imb)
                {
                    list<const Comparable *> mlist;
                    bsttolist(root, mlist);
                    destroy_tree(root);
                    constructtwo(mlist);
                }
            }
        }
        //postorder(root);
    }
}
 
 
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::mydelete(TreeNode* root,const Comparable* data) {
 
  if(root==NULL) return NULL;
  if(isLessThan(*data,*root->element))
    root->left = mydelete(root->left,data);
  else if(isLessThan(*root->element,*data))
    root->right = mydelete(root->right,data);
  else {
    if(root->left==NULL){
      TreeNode * temp = root->right;
      delete root;
      return temp;
    }
    else if(root->right==NULL){
      TreeNode * temp = root->left;
      delete root;
      return temp;
    }                                               
    TreeNode * temp = findMin(root->right);
    root->element = temp->element;
    root->parent = NULL;
    root->right = mydelete(root->right,temp->element);
  }
  root->parent = NULL;
  return root;
}
 
 
 
template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::getAddress(const Comparable& item) const
{ 
  return findadd(root,item);
}
 
template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::findadd(TreeNode* t,const Comparable& item) const
{
    if(t == NULL)
    return NULL;
  else if(isLessThan(item,(*t->element)))
    return findadd(t->left,item);
  else if(isLessThan((*t->element),item))
    return findadd(t->right,item);
  else
    return &(*t->element);
}
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::contains(const Comparable* item) const
{  
  return contains(item, root);
}
 
template <typename Comparable, typename Comparator>
size_t Tree<Comparable,Comparator>::getSize() const
{                                               
  return size;
}
 
template <typename Comparable, typename Comparator>
int Tree<Comparable,Comparator>::getHeight() const
{
  if(isEmpty())
    return -1;  //convention: empty tree has height -1
  else
    return root->height; //>= 0
}
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::isEmpty() const
{
  return (root == NULL);
}
 
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::print() const
{
  print(root);
  cout << endl;  
}
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::isBalanced() const
{
  return balanced;
}
 
template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::findMin() const
{
  if(isEmpty())
    return NULL;
  return findMin(root)->element; //call in to recursive utility function
}                                               
 
template <typename Comparable, typename Comparator>
const Comparable* Tree<Comparable,Comparator>::findMax() const
{
  if(isEmpty())
    return NULL;
  return findMax(root)->element;
}
 
/* private utility functions 
* define and use as many as you deem required
* some are provided for the already implemented 
* part of the public interface
*/
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::findMin(TreeNode* t) const
{
  if(t == NULL)
    return NULL;
 
  if(t->left == NULL)
    return t;
 
  return findMin(t->left);
}
 
template <typename Comparable, typename Comparator>
typename Tree<Comparable,Comparator>::TreeNode*
Tree<Comparable,Comparator>::findMax(TreeNode* t) const
{
  if(t != NULL)
    while(t->right != NULL)
      t = t->right;
  return t;
}                                               
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::contains(const Comparable* item,TreeNode* t) const
{
  if(t == NULL)
    return false;
  else if(isLessThan(*item,*(t->element)))
    return contains(item, t->left);
  else if(isLessThan(*(t->element),*item))
    return contains(item, t->right);
  else
    return true;
}
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::isLeaf(TreeNode* t) const
{
  return ((t->left == NULL)&& (t->right == NULL));
}
 
template <typename Comparable, typename Comparator>
bool Tree<Comparable,Comparator>::isFull(TreeNode* t) const
{
  return ((t->left != NULL)&& (t->right != NULL));
}
 
template <typename Comparable, typename Comparator>
void Tree<Comparable,Comparator>::print( TreeNode * t ) const
{
  if( t && t->left != NULL )
  {
    cout << '[';
    print( t->left );
  }
  else if( t && t->left == NULL && t->right != NULL )
  {                                             
    cout << "[";
  }
  if( t != NULL )
  {
    if( isLeaf( t ))
    {
      cout << '(' << *( t->element ) << ')';
    }
    else if( !isLeaf( t ) )
    {
      cout << *( t->element );
    }
  }
  if( t && t->right != NULL )
  {
    print( t->right );
    cout << ']';
  }
  else if( t && t->left != NULL && t->right == NULL )
  {
    cout << "]";
  }
}
 
#endif                           