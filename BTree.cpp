//
// BTree.cpp
// Social_Network
//

#include "BTree.h"

#include <iostream>
#include <cstring>

BTree::BTree(){
  M=5;
  L=3;
  //STUB!!!
}

int BTree::insertRoot(std::string name, int profileDataPointer){
  //start at the root
  //if the root is empty start a new tree
  if(root==NULL){
    root= new InternalNode(true);
  }

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
	  splitLeaf(name, profileDataPointer, currentNode, i);

	  if(currentNode->leaves[M+1]!=NULL){
	    splitInternalNode(currentNode);

	  }
	} 
      }

    }
    return -42;
  }
}

void BTree::splitInternalNode(InternalNode* firstInternalNode){
  /*  InternalNode* secondInternalNode= new InternalNode();
  secondInternalNode->names=new std::string[M+1];
  secondInternalNodes->isLeaf=false;
  if(firstInternalNode->leaves==NULL){
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

  //for the rest of the leaves in the secondInternalNode set them to null
  for(int i=M/2; i<M; i++){
    secondInternalNode->names[i]=NULL;
    int k=i+1;
    if(firstInternalNode->leaves==NULL){
      secondInternalNode->nextNodes[k]=NULL;
    }
    else{
      secondInternalNode->leaves[k]=NULL;
    }

  }

  //i want to add the secondInternal node in the parent node where it belongs
  insertInternalNode(currentNode, secondInternalNode);//this should not but the current node, but the parent of current node*/
}

int BTree::insertInternalNode(InternalNode* currentNode, InternalNode* insertNode){
  //this one should be called recursively until the invariant of the size of the internalNodearray=M is held, or until it reaches the root, in which case it splits
  return -42;
}

void BTree::splitLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafIndex){
  LeafNode* secondLeaf = new LeafNode();
  secondLeaf->itemCount=0;
  secondLeaf->items=new ItemNode*[L];
  for(int i=0; i<L; i++){
    secondLeaf->items[i]=NULL;
  }

  //find the middle of the array of items of the firstLeaf
  int middle =L/2;
  int j=L/2;
  for(int i=middle; i<L; i++){
    secondLeaf->items[j]=currentNode->leaves[leafIndex]->items[i];
    currentNode->leaves[leafIndex]->items[i]=NULL;
    currentNode->leaves[leafIndex]->itemCount--;
    secondLeaf->itemCount++;
    j--;
  }

  currentNode->leaves[leafIndex+1] = secondLeaf;
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
/*
void BTree::initializeItemNode(ItemNode* initialItem){
  initialItem->profileDataPointer=-42;
  initialItem->name="no name";
}

void BTree::initializeLeafNode(LeafNode* initialLeaf){
  initialLeaf->items= new ItemNode[L+1];
  for(int i=0; i<L;i++)
    initialLeaf->items[i]=new ItemNode();
  initialLeaf->itemCount=0;
}
void BTree::initializeInternalNode(InternalNode* initialInternalNode, bool pointsToLeaf){
  initialInternalNode->names=new std::string[M];
  if(pointsToLeaf==true){
    initialInternalNode->nextNodes=NULL;
    initialInternalNode->leaves= new LeafNode[M+1];
    for(int i=0; i<M+1; i++)
      initializeLeafNode(initialInternalNode->leaves[i]);
  }
  else{
    initialInternalNode->nextNodes= new initialInternalNode[M+1];
    for(int i; i<M+1; i++) 
      initializeInternalNode(initialInternalNode->nextNodes[i],false);
    initialInternalNode->leaves=NULL;
  }
}
*/
