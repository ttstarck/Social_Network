//
// BTree.cpp
// Social_Network
//

#include "BTree.h"

#include <iostream>
#include <cstring>

BTree::BTree(){
  root=NULL;
  numItemsInTree = 0;
}

int BTree::insertRoot(std::string name, int profileDataPointer){
  //if the root is empty start a new tree
  if(root==NULL){
    root= new InternalNode(true);
  }
  //then add the information to the tree
  return insert(name, profileDataPointer, root);
}

int BTree::insert(std::string name, int profileDataPointer, InternalNode* currentNode){
  //look through all the names and find the spot
  for(int i=0; i<M; i++){
    if((currentNode->names[i]=="no name index")||(currentNode->names[i]!="no name index" &&name<currentNode->names[i])||(name>=currentNode->names[i]&&i==M-1)){
      if(currentNode->leaves==NULL){
        insert(name, profileDataPointer, currentNode->nextNodes[i]);           //if there is another layer of nodes, go to the next layer
      }
      else{
        addToLeaf(name, profileDataPointer, currentNode, i);
	if(name=="Victor") std::cout<<"after addingtoLeaf Victor"<<std::endl;
        if(currentNode->leaves[i]->itemCount>L){           //if when I add the element to the leaf, I surpass the limit for the number of elements in the leaf
          splitLeaf(currentNode, i);
          if(currentNode->names[M-1]!="no name index"){                //if when I split the leaf I now surpassed the limit to the number of elements in the Node
            splitInternalNode(currentNode);
          }
        }
        break;
      }
    }
  }
  return 1;
}
  

void BTree::addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex){
  if(currentNode->leaves[leafNodeIndex]==NULL){
    currentNode->leaves[leafNodeIndex]= new LeafNode();
  }
  //add to the end of the array

  int numItems = currentNode->leaves[leafNodeIndex]->itemCount;
  if(name=="Victor") std::cout<<numItems<<std::endl;
  if(name=="Victor") std::cout<<currentNode->leaves[leafNodeIndex]->items[numItems-1]->name<<std::endl;
  printLeafNode(currentNode->leaves[leafNodeIndex]);
  if(currentNode->leaves[leafNodeIndex]->items[numItems]==NULL){
    currentNode->leaves[leafNodeIndex]->items[numItems]=new ItemNode();
  }
  std::cout<<numItems<<std::endl;
  //after this it doesn't add in Victor to the new spot at numItems
  printItem(currentNode->leaves[leafNodeIndex]->items[numItems]);
  if(name!="Victor") currentNode->leaves[leafNodeIndex]->items[numItems]->name=name;
  currentNode->leaves[leafNodeIndex]->items[numItems]->profileDataPointer=profileDataPointer;
  if(name=="Victor"){ 
    std::cout<<std::endl<<std::endl; 
    printLeafNode(currentNode->leaves[leafNodeIndex]);
    std::cout<<std::endl;}
  currentNode->leaves[leafNodeIndex]->itemCount++;

  numItems++;

  //if we are at the beginning, sort them
  //if(leafNodeIndex==0){

  for(int i=numItems-1; i>=1; i--){
    if(currentNode->leaves[leafNodeIndex]->items[i]->name<currentNode->leaves[leafNodeIndex]->items[i-1]->name){
      ItemNode* temp= new ItemNode();
      temp->name=currentNode->leaves[leafNodeIndex]->items[i]->name;
      temp->profileDataPointer=currentNode->leaves[leafNodeIndex]->items[i]->profileDataPointer;
      currentNode->leaves[leafNodeIndex]->items[i]->name=currentNode->leaves[leafNodeIndex]->items[i-1]->name;
      currentNode->leaves[leafNodeIndex]->items[i]->profileDataPointer=currentNode->leaves[leafNodeIndex]->items[i-1]->profileDataPointer;
      currentNode->leaves[leafNodeIndex]->items[i-1]->name=temp->name;
      currentNode->leaves[leafNodeIndex]->items[i-1]->profileDataPointer=temp->profileDataPointer;
      delete temp; //does this work for a struct?
      //  }
    }

  }

}

void BTree::splitLeaf(InternalNode* currentNode, int leafIndex){
  LeafNode* secondLeaf = new LeafNode();
  secondLeaf->itemCount=0;
  secondLeaf->items=new ItemNode*[L];
  
  //find the middle of the array of items of the firstLeaf
  int middle =L/2+1;
  int j=0;
  for(int i=middle; i<L+1; i++){
    secondLeaf->items[j]=currentNode->leaves[leafIndex]->items[i];
    currentNode->leaves[leafIndex]->items[i]=NULL;
    currentNode->leaves[leafIndex]->itemCount--;
    secondLeaf->itemCount++;
    currentNode->leaves[leafIndex]->itemCount--;
    j++;
  }

  //now I insert the second leaf into the internalNode
  //swap all the nodes to make space for the new leafNode
  for(int i=M-1; i>leafIndex; i--){
    currentNode->names[i]=currentNode->names[i-1];
    currentNode->leaves[i+1]=currentNode->leaves[i];
  }
  //swap the last for the names
  currentNode->names[leafIndex+1]=currentNode->names[leafIndex];
  
  //insert the secondLeaf
  currentNode->names[leafIndex]=secondLeaf->items[0]->name;
  if(leafIndex-1>=0){
    currentNode->names[leafIndex-1]=currentNode->leaves[leafIndex]->items[0]->name;
  }
  currentNode->leaves[leafIndex+1]=secondLeaf;
  printInternalNode(root);
}

void BTree::splitInternalNode(InternalNode* firstInternalNode){
  //split into the firstInternalNode and secondInternalNode
  InternalNode* secondInternalNode;
  if(firstInternalNode->leaves==NULL)
    secondInternalNode = new InternalNode(false);
  else
    secondInternalNode = new InternalNode(true);
  
  //initialize the first half of the secondinternalNode
  int secondIndex = 0;
  int namesIndex;
  for(int i=M/2+1 ;i<M+1; i++){
    namesIndex=i-1;
    if(i!=M)                                                                    //so it doesn't try to reference the 6th element of the names array
      secondInternalNode->names[secondIndex]= firstInternalNode->names[i];
    if(firstInternalNode->leaves!=NULL){
      secondInternalNode->leaves[secondIndex]=firstInternalNode->leaves[i];
      firstInternalNode->leaves[i]=NULL;
    }
    else{
      secondInternalNode->nextNodes[secondIndex]=firstInternalNode->nextNodes[i];
      firstInternalNode->nextNodes[i]=NULL;
    }
    secondIndex++;
  }
  
  firstInternalNode->names[M/2]="no name index";

  //if the node is the root then make a new root
  if(firstInternalNode==root){
    InternalNode* newRoot = new InternalNode(false);
    newRoot->names[0]=getNameIndex(secondInternalNode);
    newRoot->nextNodes[0]=firstInternalNode;
    firstInternalNode->parent=newRoot;
    newRoot->nextNodes[1]=secondInternalNode;
    secondInternalNode->parent=newRoot;
    root=newRoot;
  }
  //else go into the parent and insert the secondInternalNode
  for(int i=M+1; i>1; i--){
    if(i!=M+1)
      firstInternalNode->parent->nextNodes[i+1]=firstInternalNode->parent->nextNodes[i];
    if(firstInternalNode->parent->nextNodes[i-1]==firstInternalNode){
      firstInternalNode->parent->nextNodes[i]=secondInternalNode;
      secondInternalNode->parent=firstInternalNode->parent;
      firstInternalNode->parent->names[i-1]=getNameIndex(secondInternalNode);
      break;
    }
  }
    
  //if the parent doesn't pass the M invariant then call splitInternalNode again
  if(firstInternalNode->parent->names[M-1]=="no name index")
    splitInternalNode(firstInternalNode->parent);
}


std::string BTree::getNameIndex(InternalNode* nameNode){
  while(nameNode->leaves==NULL){
    nameNode= nameNode->nextNodes[0];
  }
  return nameNode->names[0];
}


void BTree::printItem(ItemNode* item){
  std::cout<< item->profileDataPointer<< " "<< item->name;
}

void BTree::printLeafNode(LeafNode* leaf){
  for(int i=0; i<L; i++){
    if(leaf->items[i]!=NULL){
      printItem(leaf->items[i]);
      std::cout<<std::endl;
    }
  }
  std::cout<<std::endl;
}
void BTree::printInternalNode(InternalNode* internalNode){
  //print nameIndexes
  std::string nameString="";
  for(int i=0; i<M; i++){
    nameString+=internalNode->names[i]+" ";
  }
  std::cout<<nameString<<std::endl;
  for(int i=0; i<M+1; i++){
    if(internalNode->leaves!=NULL){
      if(internalNode->leaves[i]!=NULL)
	printLeafNode(internalNode->leaves[i]);
    }
    else
      if(internalNode->nextNodes[i]!=NULL)
	printInternalNode(internalNode->nextNodes[i]);
  }
}

void BTree::tests(){
  /* LeafNode* leafTest = new LeafNode();
     leafTest->items[0]=new ItemNode();
     leafTest->items[1]=new ItemNode();
     leafTest->items[2]=new ItemNode();
     leafTest->items[3]=new ItemNode();
     leafTest->items[0]->name="Kelly";
     leafTest->items[0]->profileDataPointer=1;

     InternalNode* internalTest= new InternalNode(true);

     internalTest->names[0]="Kelly";
     internalTest->leaves[0]=leafTest;
     printInternalNode(internalTest);*/

  insertRoot("Kelly", 1);
  insertRoot("Tristan",2);
  insertRoot("David", 3);
  insertRoot("Amr", 4);
  insertRoot("Omeed", 5);
  insertRoot("Victor",6);

  printInternalNode(root);
}
