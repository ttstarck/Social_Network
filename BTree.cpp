//
// BTree.cpp
// Social_Network
//

#include "BTree.h"

#include <iostream>
#include <cstring>

BTree::BTree(){
  //STUB!!!
}

int BTree::insertRoot(std::string name, int profileDataPointer){
  //start at the root
  //if the root is empty start a new tree

  insert(name, profileDataPointer, root);
}

int BTree::insert(std::string name, int profileDataPointer, InternalNode* currentNode){
  // STUB!!!

  for(int i=0; i<M; i++){
    if(name<currentNode->names[i]||(name>=currentNode->names[i]&&i==M-1)){
      //get to the next level
      if(currentNode->leaves==NULL) insert(name, profileDataPointer, currentNode->nextNodes[i]);
      else{                                                                       //if it points to a leaf node level, then 
	if(!leafIsFull(currentNode->leaves[i])){                               //if leaf isn't full append to the end of the leaf
	  addToLeaf(name, profileDataPointer, currentNode; i);
	}
	else{                                                                     //do all the splitting if the leaf is full
	  for(int j=M; j>i;j--){                                                  //shift everything else down
	    currentNode->leaves[j+1]=currentNode->leaves[j];
	    currentNode->names[j]=currentNode->names[j-1];
	  }
	  LeafNode addLeaf = createLeaf(name, profileDataPointer, currentNode->leaves[i]);
	  currentNode->leaves[i+1] = addLeaf;

	  if(currentNode->leaves[M+1]!=NULL){
	    InternalNode* addNode =splitInternalNode(currentNode);
	    insertInternalNode(currentNode, addNode);
	  }
	} 
      }

    }
    return -42;
  }
}

InternalNode* BTree::splitInternalNode(InternalNode* firstInternalNode){
  InternalNode* secondInternalNode;
  return secondInternalNode;
}

int BTree::insertInternalNode(InternalNode* currentNode, InternalNode* insertNode){
  //this one should be called recursively until the invariant of the size of the internalNodearray=M is held, or until it reaches the root, in which case it splits
  return -42;
}

LeafNode* BTree::createLeaf(std::string name, int profileDataPointer, leafNode* firstLeaf){
  LeafNode secondLeaf = new LeafNode();
  secondLeaf->itemCount=0;
  secondLeaf->items=new itemNode[L];
  for(int i=0; i<L; i++){
    secondLeaf->items[i]=NULL;
  }

  //find the middle of the array of items of the firstLeaf
  int middle =L/2;
  int j=0;
  for(int i=middle; i<L; i++){
    secondLeaf->items[j]=firstLeaf->items[i];
    firstLeaf->items[i]=NULL;
    firstLeaf->itemCount--;
    secondLeaf->itemCount++;
    j++;
  }
  return secondLeaf;
}

bool BTree::leafIsFull(LeafNode* leaf){
  if((leaf->itemCount)==L) return true;
  else return false;
}

void BTree::addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex){
  currentNode->leaves[leafNodeIndex]->items[itemCount]->name=name;
  currentNode->leaves[leafNodeIndex]->items[itemCount]->profileDataPointer=profileDataPointer;
  currentNode->leaves[i]->itemCount++;
}
