#include <iostream>
#include "Node.cpp"
using namespace std;

class RBtree
{
  node *root;
  node *nil;
  
  public:
  RBtree()
  {
    root=NULL;
    nil= new node(0,0);         //Sentinel node
  }

  // ---------------------Initialize the RBTree in O(n)--------------------------------------
  void initialize(node** arrNode, long n)
  {
    root=arrayToRBTree(arrNode,0,n-1);        //  initialize BBST from sorted array
    initalizeColor();                         //  convert BBST to RBTree
  }

  node* arrayToRBTree(node** arr, long start, long end)         //Converts a sorted array to Balanced binary tree in O(n)
  {
    if (start > end) return NULL;

    long mid = start+((end-start)/2);
    node *midNode = arr[mid];
    
    node *l = arrayToRBTree(arr, start, mid-1);
    if(l!=NULL)
      l->parent=midNode;
    midNode->left = l;
    
    node *r = arrayToRBTree(arr, mid+1, end);
    if(r!=NULL)
      r->parent=midNode;
    midNode->right = r;

    return midNode;
  }

  void initalizeColor(){
    long depth=maxDepth(root);              //Find max Depth of tree
    if(depth>1)
      colorNodes(root,1,depth);             // color last nodes red
  }

  long maxDepth(node* n) 
  {
    if(n==NULL) 
      return 0;

    long leftDepth = maxDepth(n->left);
    long rightDepth = maxDepth(n->right);
      
    // Put Sentinel node instead of NULL nodes
    if(n->left==NULL)       
      n->left=nil;
    if(n->right==NULL)
      n->right=nil;
    
    if (leftDepth > rightDepth) 
      return(leftDepth+1);
    else 
      return(rightDepth+1);
  } 

  void colorNodes(node* n,long curr,long depth)
  {
    if (n==NULL || n==nil) 
      return;
    else if(curr==depth)              //color the valid nodes at last level as red
      n->color='r';
    else
    {
      colorNodes(n->left,curr+1,depth);
      colorNodes(n->right,curr+1,depth);
    }
  }

  // ---------------------RBTree operations--------------------------------------
  void insertFixUp(node *t)
  {
    while(t->parent->color=='r')
    {
      if(t->parent->parent->left==t->parent)
      {
        node *u=t->parent->parent->right;
        if(u->color=='r')
        {
          t->parent->color='b';
          u->color='b';
          t->parent->parent->color='r';
          t=t->parent->parent;
        }
        else if(t->parent->right==t)
        {
          t=t->parent;
          leftrotate(t);
        }
        t->parent->color='b';
        t->parent->parent->color='r';
        rightrotate(t->parent->parent);
      }
      else
      {
        node *u=t->parent->parent->left;
        if(u->color=='r')
        {
          t->parent->color='b';
          u->color='b';
          t->parent->parent->color='r';
          t=t->parent->parent;
        }
        else if(t->parent->left==t)
        {
          t=t->parent;
          rightrotate(t);
        }
        t->parent->color='b';
        t->parent->parent->color='r';
        leftrotate(t->parent->parent);

      }     
    }
    root->color='b';
  }

  void deleteFixUp(node *x)
  {
    node *w;
    while(x!=root && x->color=='b')
    {
      if(x->parent->left==x)
      {
        w=x->parent->right;
        if(w->color=='r')
        {
          w->color='b';
          x->parent->color='r';
          leftrotate(x->parent);
          w=x->parent->right;
        }
        if(w->right->color=='b' && w->left->color=='b')
        {
          w->color='r';
          x=x->parent;
        }
        else
        {
          if(w->right->color=='b')
          {
            w->left->color=='b';
            w->color='r';
            rightrotate(w);
            w=x->parent->right;
          }
          w->color=x->parent->color;
          x->parent->color='b';
          w->right->color='b';
          leftrotate(x->parent);
          x=root;
        }
      }
      else
      {
        w=x->parent->left;
        if(w->color=='r')
        {
          w->color='b';
          x->parent->color='r';
          rightrotate(x->parent);
          w=x->parent->left;
        }
        if(w->left->color=='b' && w->right->color=='b')
        {
          w->color='r';
          x=x->parent;
        }
        else
        {
          if(w->left->color=='b')
          {
            w->right->color='b';
            w->color='r';
            leftrotate(w);
            w=x->parent->left;
          }
          w->color=x->parent->color;
          x->parent->color='b';
          w->left->color='b';
          rightrotate(x->parent);
          x=root;
        }
      }
      x->color='b';
      root->color='b';
    }
  }

  // ---------------------Perform problem specific operations on RBTree--------------------------------------
  int increase(int id,int value)
  {
    node *p=root,*q=nil;  
    while(p!=nil)           //Try to find node
    {
      q=p;
      if(p->id==id)
      {
        p->count=p->count+value;          // If found, increment the count and return
        return p->count;
      }
      else if(p->id < id)
        p=p->right;
      else
        p=p->left;
    }
    // If not found, create new node and insert
    node *t=new node;
    t->id=id;
    t->count=value;
    t->left=nil;
    t->right=nil;
    t->color='r';
    t->parent=q;

    if(q!=nil)
    {
      if(q->id < id)
        q->right=t;
      else
        q->left=t;
    }
    else
      root=t;

    insertFixUp(t);         //perform rotations to remove violations to RBTree
    return value;
  }

  int reduce(int id, int value)
  {
    node *z=root;
    int found=0;
    while(z!=nil)                   // Try to find the node
    {
      if(z->id==id)
      {
        found=1;
        break;
      }
      else if(z->id < id)
        z=z->right;
      else
        z=z->left;
    }

    if(found==0)                // If not found
      return 0;

    if(z->count > value)        // If found and count is still above 0
    {
      z->count-=value;
      return z->count;
    }
    // if found but need to delete the node
    node* y=z,*x=nil;
    char ycolor=y->color;
    if(z->left==nil)
    {
      x=z->right;
      transplant(z,z->right);
    }
    else if(z->right==nil)
    {
      x=z->left;
      transplant(z,z->left);
    }
    else{
      y=treeMin(z->right);
      ycolor=y->color;
      x=y->right;
      if(y->parent==z)
      {
        x->parent==y;
      }
      else{
        transplant(y,y->right);
        y->right=z->right;
        y->right->parent=y;
      }
      transplant(z,y);
      y->left=z->left;
      y->left->parent=y;
      y->color=z->color;
    }

    if(ycolor=='b')
      deleteFixUp(x);         //perform rotations to remove violations to RBTree
    return 0;
  }

  int count(int x)
  {
    node *p=find(x);
    if(p==NULL)
      return 0;
    else
      return p->count;
  }

  int inRange(int i,int j)
  {
    int ans=0;
    node *x=find(i);
    if(x!=NULL)
      ans+=x->count;
    while(i<=j){
      node* x=next(i);
      if(x==nil)
        break;
      i=x->id;
      if(i<=j)
        ans+=x->count;
    }
    return ans;
  }

  node* next(int id)
  {
    node* p = root;
    node* q = NULL;
    
    while(p != nil)
    {
      q=p;
      if(p->id == id)     // if first id is found
        break;
      else if(p->id > id)
        p = p->left;          
      else
        p = p->right;
    }

    if(p!=nil)
    {
      node* s = successor(p);      //id found
      if(s==NULL)
        return nil;
      else
        return s;
    }
    else          // id not found
    {
      if(q->id > id)
        p = q;
      else
        p = successor(q);
      
      if(p==NULL)
        return nil;
      else
        return p;
    }
  }

  node* previous(int id)
  {
    node* p = root,*q = NULL;
    
    while(p!=nil)
    {
      q = p;
      if(p->id == id)     // if first id is found
        break;
      else if(p->id > id)
        p = p->left;          
      else
        p = p->right;
    }
    
    if(p!=nil){
      node* s = predecessor(p);   //id found
      if(s==NULL)
        return nil;
      else
        return s;
    }
    else          // id not found
    {
      if(q->id < id)
        p = q;
      else
        p = predecessor(q);
      
      if(p==NULL)
        return nil;
      else
        return p;
    }    
  } 

  //-------------------------------Binary tree operations--------------------------
  void transplant(node *u,node *v)            // Insert one subtree in place of another subtree
  {
    if(u->parent==NULL)
      root=v;
    else if(u==u->parent->left){
      u->parent->left=v;
    }
    else{
      u->parent->right=v;
    }
    v->parent=u->parent;
  }

  node* treeMin(node *n)              // Find the min node in subtree
  {
    while(n->left!=nil) 
      n = n->left;
    return n;
  }

  node* treeMax(node *n)               // Find the max node in subtree
  {
    while(n->right != nil) 
      n = n->right;
    return n;
  }

  void leftrotate(node *p)                //Rotate the subtree rooted at given node
  {
    if(p->right==NULL)
      return;

    node *y=p->right;
    if(y->left!=NULL)
    {
      p->right=y->left;
      y->left->parent=p;
    }
    else
      p->right=NULL;

    if(p->parent!=NULL)
      y->parent=p->parent;

    if(p->parent==NULL)
      root=y;
    else
    {
      if(p==p->parent->left)
        p->parent->left=y;
      else
        p->parent->right=y;
    }
    y->left=p;
    p->parent=y;
  }

  void rightrotate(node *p)                      //Rotate the subtree rooted at given node
  {
    if(p->left==NULL)
      return ;
    
    node *y=p->left;
    if(y->right!=NULL)
    {
      p->left=y->right;
      y->right->parent=p;
    }
    else
      p->left=NULL;
    
    if(p->parent!=NULL)
      y->parent=p->parent;
    
    if(p->parent==NULL)
      root=y;
    else
    {
      if(p==p->parent->left)
        p->parent->left=y;
      else
        p->parent->right=y;
    }
    y->right=p;
    p->parent=y;
  }
  
  node* successor(node* n)                // Returns the successor node in inorder traversal
  {
    if (n->right != nil) 
      return treeMin(n->right);
    node* p = n->parent;
        
    while (p != NULL && n == p->right) 
    {
      n = p;
      p = p->parent;
    }
    return p;
  }

  node* predecessor(node* n)               // Returns the predecessor node in inorder traversal
  {
    if( n->left != nil )
      return treeMax(n->left);
    node* p = n->parent;
        
    while (p != NULL && n == p->left) 
    {
      n = p;
      p = p->parent;
    }
    return p;
  }

  node* find(int x)                       //Tries to find node with given id, if not found return NULL
  {    
    node *temp = root;
    while (temp != NULL)
    {
      if (temp->id == x){
        return temp;
      }
      else if (x > temp->id)
        temp = temp->right;
      else
        temp = temp->left;
    }
    return temp;
  }
};
