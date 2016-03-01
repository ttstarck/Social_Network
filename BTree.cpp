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
	  addToLeaf(name, profileDataPointer, currentNode, i);
	}
	else{                                                                     //do all the splitting if the leaf is full
	  for(int j=M; j>i;j--){                                                  //shift everything else down
	    currentNode->leaves[j+1]=currentNode->leaves[j];
	    currentNode->names[j]=currentNode->names[j-1];
	  }
	  LeafNode* addLeaf = splitLeaf(name, profileDataPointer, currentNode->leaves[i]);
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
  InternalNode* secondInternalNode= new InternalNode();
  secondInternalNode->names=new std::string[M+1];
  secondInternalNodes->isLeaf=false;
  if(firstInternalNodes->leaves==NULL){
    secondInternalNode->leaves=NULL;
    secondInternalNode->nextNodes=new InternalNode[M+2];
  }
  else{
    secondInternalNode->leaves= new LeafNode[M+2];
    secondInternalNode->nextNodes=NULL;}

  j=M/2-1;
  for(int i=M-1; i>M/2-1, i--){                                           //I split it by 2 and 3 because it is likely that he will want to insert in between but not above for many of these
    secondInternalNode->names[j]=firstInternalNode->names[i];
    int k=i+1;
    int l=j+1;
    if(firstInternalNode->leaves==NULL){
      secondInternalNode->nextNodes[l]=firstInternalNode->nextNodes[k];
      firstInternalNode->nextNodes[k]=NULL;
    }
    else{
      secondInternalNode->leaves[l]=firstInternalNode->nextNodes[k];
      firstInternalNode->nextNodes[k]=NULL;
    }
    j--;
  }
  //for the rest set them to null

  return secondInternalNode;
}

int BTree::insertInternalNode(InternalNode* currentNode, InternalNode* insertNode){
  //this one should be called recursively until the invariant of the size of the internalNodearray=M is held, or until it reaches the root, in which case it splits
  return -42;
}

LeafNode* BTree::splitLeaf(std::string name, int profileDataPointer, leafNode* firstLeaf){
  LeafNode secondLeaf = new LeafNode();
  secondLeaf->itemCount=0;
  secondLeaf->items=new itemNode[L];
  for(int i=0; i<L; i++){
    secondLeaf->items[i]=NULL;
  }

  //find the middle of the array of items of the firstLeaf
  int middle =L/2;
  int j=L/2;
  for(int i=middle; i<L; i++){
    secondLeaf->items[j]=firstLeaf->items[i];
    firstLeaf->items[i]=NULL;
    firstLeaf->itemCount--;
    secondLeaf->itemCount++;
    j--;
  }
  return secondLeaf;
}

bool BTree::leafIsFull(LeafNode* leaf){
  if((leaf->itemCount)==L) return true;
  else return false;
}

void BTree::addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex){
  //also, when i insert an item, I have to add the name to some part of the currentnode names array

  currentNode->leaves[leafNodeIndex]->items[currentNode->leaves[leafNodeIndex]->itemCount]->name=name;
  currentNode->leaves[leafNodeIndex]->items[currentNode->leaves[leafNodeIndex]->itemCount]->profileDataPointer=profileDataPointer;
  currentNode->leaves[leafNodeIndex]->itemCount++;
}
