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
  };

  InternalNode* root;

  int M;

  int L;

  int numItemsInTree;

  void splitInternalNode(InternalNode* node);

  bool leafIsFull(LeafNode* leaf);


  int insert(std::string name, int profileDataPointer, InternalNode* currentNode);

  int insertInternalNode(std::string name, int profileDataPointer);

  leafNode* createLeaf(std::string name, int profileDataPointer, leafNode* firstLeaf);

  void addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex);

};

#endif //BTREE_H
