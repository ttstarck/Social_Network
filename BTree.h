//
// BTree.h
// Social_Network
//

#ifndef BTREE_H
#define BTREE_H

#include "FSeeker.h"

#include <string>
#include <iostream>

class BTree{

 public:

  BTree();

  int insertRoot(std::string name, int profileDataPointer);

  void tests();

  void printBTree();

  void getRange(std::string name1, std::string name2, FSeeker* f);

  private:

  struct ItemNode{
    int profileDataPointer;
    std::string name;
    ItemNode(){
      profileDataPointer = -42;
      name = "no name item";
    }
  };
  struct LeafNode{
    ItemNode** items;
    int itemCount;
    LeafNode(){
      items = new ItemNode*[L+1];
      for(int i = 0; i < L+1; i++){
        items[i] = new ItemNode();
      }
      itemCount = 0;
    }
  };

  struct InternalNode{
    std::string* names;
    InternalNode** nextNodes;
    LeafNode** leaves;
    InternalNode* parent;
    InternalNode(bool pointsToLeaf){
      parent = NULL;
      names = new std::string[M];
      for(int i = 0; i < M; i++)
        names[i] = "no name index";
      if(pointsToLeaf == false){
        nextNodes = new InternalNode*[M+1];
        for(int i = 0; i < M+1; i++)
          nextNodes[i] = NULL;
        leaves=NULL;
      }
      else{
        nextNodes = NULL;
        leaves = new LeafNode*[M+1];
        for(int i = 0; i < M+1; i++)
          leaves[i] = NULL;
      }
    }
  };
  //private:
  InternalNode* root;

  static const int M = 5;

  static const int L = 3;

  int numItemsInTree;

  //helper functions
  int insert(std::string name, int profileDataPointer, InternalNode* currentNode);

  void addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex);

  void splitLeaf(InternalNode* nameNode, int leafIndex);
  
  void splitInternalNode(InternalNode* node);

  std::string getNameIndex(InternalNode* nameNode);

  //printing functions to test insert
  void printItem(ItemNode* item);

  void printLeafNode(LeafNode* leaf);

  void printInternalNode(InternalNode* internalNode);

  void getRange(std::string name1, std::string name2, InternalNode* node, FSeeker* f);
  
};

#endif //BTREE_H
