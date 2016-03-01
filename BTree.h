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

 private:

  struct ItemNode{
    int profileDataPointer;
    std::string name;
    // I want to initialize the values of the struct when defining it    ItemNode(int profileDataPointer=-42, std::string="no name")
  };
  struct LeafNode{
    ItemNode** items;
    int itemCount;
  };

  struct InternalNode{
    std::string* names;
    InternalNode** nextNodes;
    bool isLeaf;
    LeafNode** leaves;
    //InternalNode* parentInternalNode;
  };

  InternalNode* root;

  int M;

  int L;

  int numItemsInTree;


  int insert(std::string name, int profileDataPointer, InternalNode* currentNode);

  void splitInternalNode(InternalNode* node);

  int insertInternalNode(InternalNode* currentNode, InternalNode* firstInternalNode);

  LeafNode* splitLeaf(std::string name, int profileDataPointer, LeafNode* firstLeaf);

  bool leafIsFull(LeafNode* leaf);
  
  void addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex);
  
};

#endif //BTREE_H
