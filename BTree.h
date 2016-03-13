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
  // Constructor for BTree.
  BTree();

  // Calls insert with the root of the BTree.
  int insertRoot(std::string name, int profileDataPointer);

  // Runs multiple inserts and a final print on the BTree
  void tests();

  // Prints entire BTree
  void printBTree();

  // Public getRange function. Calls private getRange on root of BTree.
  void getRange(std::string name1, std::string name2, FSeeker* f);

  private:

    // Struct used to hold name and pointer to profile data on file.
  struct ItemNode{
    int profileDataPointer;
    std::string name;
    ItemNode(){
      profileDataPointer = -42;
      name = "no name item";
    }
  };

  // Struct used to hold an array of items and keep track of how many items are currently in the array.
  struct LeafNode{
    // Array of ItemNodes, kept sorted Alphabetically.
    ItemNode** items;
    int itemCount;
    LeafNode(){ // Initializes array of items and itemCount.
      // Made items hold one extra ItemNode than intended so that splitLeaf would be easier.
      items = new ItemNode*[L+1];
      for(int i = 0; i < L+1; i++){
        items[i] = new ItemNode();
      }
      itemCount = 0;
    }
  };

  // Struct for internal nodes in BTree.
  struct InternalNode{
    // Array of names, used to determine the correct path to take to reach the leaves.
    std::string* names;
    // Next layer of internal Nodes. Will be NULL if it is in the layer right about the leaves.
    InternalNode** nextNodes;
    // Array of leaf nodes. Will be NULL if it isn't in the layer right about the leaves.
    LeafNode** leaves;
    // Pointer to the parent internal Node. Will be NULL if internal Node is the root.
    InternalNode* parent;
    // Constructor for InternalNode that takes a bool as a parameter that determines whether to initialize leaves or nextNodes.
    InternalNode(bool pointsToLeaf){
      parent = NULL;
      // Made names hold one extra name so that splitInternal Node would be easier
      names = new std::string[M];
      for(int i = 0; i < M; i++)
        names[i] = "no name index";
      if(pointsToLeaf == false){
        // Made nextNodes hold one extra InternalNode so that splitInternal Node would be easier
        nextNodes = new InternalNode*[M+1];
        for(int i = 0; i < M+1; i++)
          nextNodes[i] = NULL;
        leaves=NULL;
      }
      else{
        nextNodes = NULL;
        // Made leaves hold one extra LeafNode so that splitInternal Node would be easier
        leaves = new LeafNode*[M+1];
        for(int i = 0; i < M+1; i++)
          leaves[i] = NULL;
      }
    }
  };

  // Root of BTree
  InternalNode* root;

  // Max number of Children that a root can point too.
  static const int M = 5;

  // Max number of Items a LeafNode can contain.
  static const int L = 3;


  //Helper Functions

  // Traverses BTree recursively to reach Last layer of InternalNodes, then calls addToLeaf.
  int insert(std::string name, int profileDataPointer, InternalNode* currentNode);

  // Adds person as an ItemNode into a LeafNode.
  void addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex);

  // Used if after inserting, a leaf has more than L items in it. Splits the leaf into two leaves,
  // then inserts the second leaf next to the first leaf in currentNode's leaves array.
  void splitLeaf(InternalNode* nameNode, int leafIndex);
  
  // Used if after inserting, a leaf was split and now there are more than M leaves in the InternalNode.
  // Splits the InternalNode into two InternalNodes, inserting the second internal node into the parent 
  // of the first internal node. If the parent has too many children, call splitInternalaNode on it.
  void splitInternalNode(InternalNode* node);

  // Gets the name of the left most item in the left most leaf of the subtree of nameNode.
  std::string getNameIndex(InternalNode* nameNode);

  //printing functions to test insert
  void printItem(ItemNode* item);

  // Prints all items in leaf
  void printLeafNode(LeafNode* leaf);

  // Prints names array, then recursively calls printInternalNode on allof internalNode's children.
  // Once it reaches the last layer of InternalNodes, call printLeafNode on all LeafNodes in leaves array.
  void printInternalNode(InternalNode* internalNode);

  // Private getRange function. Prints Profile Data stored on file of all people ranging alphabetically from name1 to name2.
  void getRange(std::string name1, std::string name2, InternalNode* node, FSeeker* f);
  
};

#endif //BTREE_H
