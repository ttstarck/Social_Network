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

int BTree::insert(std::string name, int profileDataPointer){
  //start at the root
  //if the root is empty start a new tree

  insert(name, profileDataPointer, root);
}

int BTree::insert(std::string name, int profileDataPointer, InternalNode* currentNode){
	// STUB!!!

  for(int i=0; i<M; i++){
    if(name<currentNode->names[i]||(name>=currentNode->names[i]&&i==M-1)){
      //get to the next level
      if(currentNode->leafNodes==NULL) insert(name, profileDataPointer, currentNode->nextNodes[i]);
      else{                                                                       //if it points to a leaf node level, then 
	if(!leafIsFull(currentNode->leafNodes[i])){                               //if leaf isn't full append to the end of the leaf
	  addToLeaf(name, profileDataPointer, currentNode; i);
	}
	else{                                                                     //do all the splitting if the leaf is full
	  for(int j=M; j>i;j--){                                                  //shift everything else down
	    currentNode->leafNodes[j+1]=currentNode->leafNodes[j];
	    currentNode->names[j]=currentNode->names[j-1];
	  }
	  leafNode addLeaf = createLeaf(name, profileDataPointer, currentNode->leafNodes[i]);
	  currentNode->leafNodes[i+1] = addLeaf;
	}
      } 
    }

  }
	return -42;
}


void BTree::splitInternalNode(InternalNode* node){

}

leafNode BTree::createLeaf(std::string name; int profileDataPointer, leafNode* firstLeaf){
  leafNode secondLeaf = new leafNode();
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

void BTree::addToLeaf(std::string name; int profileDataPointer; InternalNode* currentNode; int leafNodeIndex){
  currentNode->leafNodes[leafNodeIndex]->items[itemCount]->name=name;
  currentNode->leafNodes[leafNodeIndex]->items[itemCount]->profileDataPointer=profileDataPointer;
  currentNode->leafNodes[i]->itemCount++;
}
