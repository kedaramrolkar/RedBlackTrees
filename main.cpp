#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <fstream>
#include "RedBlackTree.cpp"
using namespace std;

void parseInput(string, RBtree*);

int main(int argc, char** argv)
{
  if (argc < 2 || argc>2)  exit(1);       //only allow 2 argc (function name and inputFileLocation)
  
  string fileLocation=argv[1]; 
  RBtree *rbTree=new RBtree();
  
  parseInput(fileLocation,rbTree);        //grab the initial list and initialize tree in O(n)
  
  string command;
  const char *s;
  int i,j;
  while (getline(cin, command))           // Grab commands one by one from std in
  {
    if(command=="quit")
      break;

    else if(command.substr(0,5)=="count")
    {
      s=command.substr(6).c_str();;
      sscanf(s,"%d",&i);
      cout<<rbTree->count(i)<<"\n";
    }
    else if(command.substr(0,8)=="increase")
    {
      s=command.substr(9).c_str();;
      sscanf(s,"%d %d",&i,&j);
      cout<<rbTree->increase(i,j)<<"\n";
    }
    else if(command.substr(0,6)=="reduce")
    {
      s=command.substr(7).c_str();;
      sscanf(s,"%d %d",&i,&j);
      cout<<rbTree->reduce(i,j)<<"\n";
    }
    else if(command.substr(0,4)=="next")
    {
      s=command.substr(5).c_str();;
      sscanf(s,"%d",&i);
      node* x=rbTree->next(i);
      x->print();
    }
    else if(command.substr(0,8)=="previous")
    {
      s=command.substr(9).c_str();;
      sscanf(s,"%d",&i);
      node *x=rbTree->previous(i);
      x->print();
    }
    else if(command.substr(0,7)=="inrange")
    {
      s=command.substr(8).c_str();;
      sscanf(s,"%d %d",&i,&j);
      cout<<rbTree->inRange(i,j)<<"\n";
    }
  }
  return 1;
};

void parseInput(string fileLocation, RBtree* rbTree)
{
  ifstream fin;
  fin.open(fileLocation.c_str());
  if(!fin.good())                                     //If cannot find/open the file
  {
    cout<<"Error: File '" << fileLocation<<"' could not be found.";
    exit(1);
  }

  long n;
  fin>>n;
  node **arrNode = (node**)malloc(sizeof(node*) * n);       //Initializa array of pointers to node
  long id,count;
  for (long i = 0; i < n; ++i)
  {
    fin>>id>>count;
    arrNode[i]=new node(id,count);                    // For each entry, create node
  }
  rbTree->initialize(arrNode,n);                      // Initialize RBTree with these newly created nodes
}