#include <iostream>
using namespace std;

class node
{
public:
  long id;
  long count;
  char color;
  node *parent;
  node *left;
  node *right;

  node(){
    color='b';
    parent=NULL;left=NULL;right=NULL;
  }

  node(long vid,long vcount){
    color='b';
    id=vid;
    count=vcount;
    parent=NULL;left=NULL;right=NULL;
  }

  void print(){
    cout<<id<<" "<<count<<"\n";
  }
};