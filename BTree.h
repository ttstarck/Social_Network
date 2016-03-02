//
// BTree.h
// Social_Network
//

#ifndef BTREE_H
#define BTREE_H

#include <string>

class BTree{

 public:

  BTree();

  int insertRoot(std::string name, int profileDataPointer);

  // private:

  struct ItemNode{
    int profileDataPointer;
    std::string name;
    ItemNode(){
      profileDataPointer=-42;
      name="no name item";
    }
  };
  struct LeafNode{
    ItemNode** items;
    int itemCount;
    LeafNode(){
      items= new ItemNode*[L+1];
      itemCount=0;
    }
  };

  struct InternalNode{
    std::string* names;
    InternalNode** nextNodes;
    LeafNode** leaves;
    InternalNode* parentInternalNode;
    InternalNode(bool pointsToLeaf){
      names=new std::string[M];
      for(int i=0; i<M+1; i++)
	names[i]="no name index";
      if(pointsToLeaf==false){
	nextNodes=new InternalNode*[M+1];
	for(int i=0; i<M+2; i++)
	  nextNodes[i]=NULL;
	leaves=NULL;
      }
      else{
	nextNodes=NULL;
	leaves=new LeafNode*[M+1];
	for(int i=0; i<M+2; i++)
	  leaves[i]=NULL;
      }
    }
  };
 private:
  InternalNode* root;

  static int M;

  static int L;

  int numItemsInTree;


  int insert(std::string name, int profileDataPointer, InternalNode* currentNode);

  void splitInternalNode(InternalNode* node);

  int insertInternalNode(InternalNode* currentNode, InternalNode* firstInternalNode);

  void splitLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int LeafIndex);

  bool leafIsFull(LeafNode* leaf);
  
  void addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex);
  /*  
  void initializeItemNode(ItemNode* initialItem);

  void initializeLeafNode(LeafNode* initialLeaf);

  void initializeInternalNode(InternalNode* initialInternalNode, bool pointsToLeaf);*/
};

#endif //BTREE_H
