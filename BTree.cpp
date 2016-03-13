//
// BTree.cpp
// Social_Network
//

#include "BTree.h"
#include "FSeeker.h"

#include <iostream>
#include <cstring>

BTree::BTree(){
  root = NULL;
}

int BTree::insertRoot(std::string name, int profileDataPointer){
  //if the root is empty start a new tree
  if(root == NULL){
    root = new InternalNode(true);
  }
  //then add the information to the tree
  return insert(name, profileDataPointer, root);
}

int BTree::insert(std::string name, int profileDataPointer, InternalNode* currentNode){
  //look through all the names and find where the name belongs
  int i;
  for(i = 0; i < M; i++){
    if((currentNode->names[i] == "no name index")||(name < currentNode->names[i])||(name >= currentNode->names[i]&&i == M-1))
      break;
  }
  //if there is another layer of nodes, go to the next layer
  if(currentNode->leaves == NULL){
    insert(name, profileDataPointer, currentNode->nextNodes[i]);
  }
  else{
    addToLeaf(name, profileDataPointer, currentNode, i);
    // After inserting, if the number of items exceeds L, call splitLeaf.
    if(currentNode->leaves[i]->itemCount > L){ 
      splitLeaf(currentNode, i);
      // After splitLeaf, if the number of LeafNodes exceeds M, call splitInternalNode.
      if(currentNode->names[M-1] != "no name index"){ 
	splitInternalNode(currentNode);
      }
    }
    
  }
  return 1;
}
  

void BTree::addToLeaf(std::string name, int profileDataPointer, InternalNode* currentNode, int leafNodeIndex){
  // Creates new LeafNode there is no current LeafNode where the data is suppose to go.
  if(currentNode->leaves[leafNodeIndex] == NULL){
    currentNode->leaves[leafNodeIndex] = new LeafNode();
  }
  // stores number of items in the LeafNode that will be taking the ItemNode
  int numItems = currentNode->leaves[leafNodeIndex]->itemCount;
 
  // Adds ItemNode to end of array of items.
  currentNode->leaves[leafNodeIndex]->items[numItems]->name = name;
  currentNode->leaves[leafNodeIndex]->items[numItems]->profileDataPointer = profileDataPointer;
  currentNode->leaves[leafNodeIndex]->itemCount++;
  numItems++;

  // Sorts ItemNodes alphabetically.
  for(int i = numItems-1; i >= 1; i--){
    if(currentNode->leaves[leafNodeIndex]->items[i]->name < currentNode->leaves[leafNodeIndex]->items[i-1]->name){
      ItemNode* temp = new ItemNode();
      temp->name = currentNode->leaves[leafNodeIndex]->items[i]->name;
      temp->profileDataPointer = currentNode->leaves[leafNodeIndex]->items[i]->profileDataPointer;
      currentNode->leaves[leafNodeIndex]->items[i]->name = currentNode->leaves[leafNodeIndex]->items[i-1]->name;
      currentNode->leaves[leafNodeIndex]->items[i]->profileDataPointer = currentNode->leaves[leafNodeIndex]->items[i-1]->profileDataPointer;
      currentNode->leaves[leafNodeIndex]->items[i-1]->name = temp->name;
      currentNode->leaves[leafNodeIndex]->items[i-1]->profileDataPointer = temp->profileDataPointer;
      delete temp;
    }
  }
}

void BTree::splitLeaf(InternalNode* currentNode, int leafIndex){
  LeafNode* secondLeaf = new LeafNode();
  
  //find the middle of the array of items of the firstLeaf
  int middle = L/2+1;
  int j = 0;

  // Moves second half of full leaf into secondLeaf.
  for(int i = middle; i < L+1; i++){
    // Deletes empty items that were initialized by the LeafNode constructor.
    delete secondLeaf->items[j];
    secondLeaf->items[j] = currentNode->leaves[leafIndex]->items[i];
    currentNode->leaves[leafIndex]->items[i] = new ItemNode();
    secondLeaf->itemCount++;
    currentNode->leaves[leafIndex]->itemCount--;
    j++;
  }
  
  // Moves all leaves after the previously full leaf over one to make room for secondLeaf.
  for(int i=M-1; i>leafIndex; i--){
    currentNode->names[i] = currentNode->names[i-1];
    currentNode->leaves[i+1] = currentNode->leaves[i];
  }
  
  // Insert the secondLeaf after the previously full leaf.
  currentNode->names[leafIndex] = secondLeaf->items[0]->name;
  if(leafIndex-1>=0){
    currentNode->names[leafIndex-1] = currentNode->leaves[leafIndex]->items[0]->name;
  }
  currentNode->leaves[leafIndex+1] = secondLeaf;
}

void BTree::splitInternalNode(InternalNode* firstInternalNode){
  // Creates a new InternalNode that will either point to leaves or more InternalNodes
  // depending if firstInternalNode does or not.
  InternalNode* secondInternalNode;
  if(firstInternalNode->leaves == NULL){
    secondInternalNode = new InternalNode(false);
  }
  else{
    secondInternalNode = new InternalNode(true);
  }

  // Move the second half of the firstInternalNode to the first half of the secondinternalNode
  int secondIndex = 0;
  for(int i = M/2+1 ;i < M+1; i++){
    if(i < M){
      secondInternalNode->names[secondIndex] = firstInternalNode->names[i];
      firstInternalNode->names[i] = "no name index";
    }
    if(firstInternalNode->leaves != NULL){
      secondInternalNode->leaves[secondIndex] = firstInternalNode->leaves[i];
      firstInternalNode->leaves[i] = NULL;
    }
    else{
      secondInternalNode->nextNodes[secondIndex] = firstInternalNode->nextNodes[i];
      firstInternalNode->nextNodes[i] = NULL;
      secondInternalNode->nextNodes[secondIndex]->parent = secondInternalNode;
    }
    secondIndex++;
  }
  
  firstInternalNode->names[M/2] = "no name index";
  
  // If the node is the root then make a new root
  if(firstInternalNode == root){
    InternalNode* newRoot = new InternalNode(false);
    newRoot->names[0] = getNameIndex(secondInternalNode);
    newRoot->nextNodes[0] = firstInternalNode;
    firstInternalNode->parent = newRoot;
    newRoot->nextNodes[1] = secondInternalNode;
    secondInternalNode->parent = newRoot;
    root = newRoot;
  }
  // Else add it to the end of the firstInternalNode's parent
  else{
    int i = M-1;
    while(firstInternalNode->parent->nextNodes[i] != firstInternalNode){
      firstInternalNode->parent->nextNodes[i+1] = firstInternalNode->parent->nextNodes[i];
      firstInternalNode->parent->names[i] = firstInternalNode->parent->names[i-1];
      i--;
    }
    firstInternalNode->parent->nextNodes[i+1] = secondInternalNode;
    secondInternalNode->parent = firstInternalNode->parent;
    firstInternalNode->parent->names[i] = getNameIndex(secondInternalNode);
    
  }
    
  //if the parent doesn't pass the M invariant then call splitInternalNode again
  if(firstInternalNode->parent->names[M-1] != "no name index")
    splitInternalNode(firstInternalNode->parent);
}


std::string BTree::getNameIndex(InternalNode* nameNode){
  // If not  at leaves level, get traversing down BTree.
  while(nameNode->leaves == NULL){
    nameNode = nameNode->nextNodes[0];
  }
  return nameNode->leaves[0]->items[0]->name;
}


void BTree::printItem(ItemNode* item){
  std::cout<< item->profileDataPointer<< " "<< item->name;
}

void BTree::printLeafNode(LeafNode* leaf){
  for(int i = 0; i < L+1; i++){
    if(leaf->items[i] != NULL){
      printItem(leaf->items[i]);
      std::cout << std::endl;
    }
  }
  std::cout<<std::endl;
}
void BTree::printInternalNode(InternalNode* internalNode){
  std::string nameString="";
  for(int i = 0; i < M-1; i++){
    nameString += internalNode->names[i] + "[" + std::to_string(i) + "]" + " ";
  }
  std::cout << nameString << std::endl;
  for(int i = 0; i < M+1; i++){
    if(internalNode->leaves != NULL){
      if(internalNode->leaves[i] != NULL)
	printLeafNode(internalNode->leaves[i]);
    }
    else
      if(internalNode->nextNodes[i] != NULL)
	printInternalNode(internalNode->nextNodes[i]);
  }
}

void BTree::printBTree(){
  printInternalNode(root);
}

void BTree::getRange(std::string name1, std::string name2, FSeeker* f){
  getRange(name1, name2, root, f);
}

void BTree::getRange(std::string name1, std::string name2, InternalNode* node, FSeeker* f){
  if(node != NULL){
    // If at leaves level, print out profileData of people in items who's names are inbetween name1 and name2.
    if(node->leaves != NULL){
      for(int i = 0; i < M; i++){
	if((i == 0 && name1 < node->names[i]) || (i > 0 && node->names[i] != "no name index" && name1 < node->names[i] && name2 >= node->names[i-1]) || (i > 0 && node->names[i] == "no name index" && name2 >= node->names[i-1])){
	  for(int j = 0; j < L; j++){
	    if((name1 <= node->leaves[i]->items[j]->name) && (name2 >=node->leaves[i]->items[j]->name)){
	      std::cout << node->leaves[i]->items[j]->name << " " << f->getAge(node->leaves[i]->items[j]->profileDataPointer) << " " << f->getOccupation(node->leaves[i]->items[j]->profileDataPointer)<< std::endl;
	    }
	  }
	}

        if(node->names[i] == "no name index") // Break if no more leaves contain items.
	  break;
      }
    }
    else{ // Else, recursively call getRange on all internalNodes that could contain items that are inbetween name1 and name2.
      for(int i = 0; i < M; i++){
	if((i == 0 && name1 < node->names[i]) || (i > 0 && node->names[i] != "no name index" && name1 < node->names[i] && name2 >= node->names[i-1]) || (i > 0 && node->names[i] == "no name index" && name2 >= node->names[i-1])){
	  getRange(name1, name2, node->nextNodes[i], f);
	  if(node->names[i] == "no name index") // Break if no more InternalNodes pointers.
	    break;
	}
      }
    }
  }
}

void BTree::tests(){
  insertRoot("Kelly", 1);
  insertRoot("Tristan",2);
  insertRoot("David", 3);
  insertRoot("Amr", 4);
  insertRoot("Omid", 5);
  insertRoot("Victor",6);
  insertRoot("Lauren",7);
  insertRoot("Danny", 8);
  insertRoot("Chris", 9);
  insertRoot("Nicole", 10);
  insertRoot("Thomas", 11);
  insertRoot("John", 12);
  insertRoot("Jane", 13);
  insertRoot("Kathy", 14);
  insertRoot("Katherine", 15);
  insertRoot("Tim", 16);
  insertRoot("Tyler", 17);
  insertRoot("Travis", 18);
  insertRoot("Robert", 19);
  insertRoot("Steven", 20);
  insertRoot("Sam", 21);
  insertRoot("Scott", 22);
  insertRoot("Patricia", 23);
  insertRoot("Pamela", 24);
  insertRoot("Phoebe", 25);
  insertRoot("Abby", 26);
  insertRoot("Bailey", 27);
  insertRoot("Cam", 28);
  insertRoot("Dakota", 29);
  insertRoot("Abigail", 30);
  insertRoot("Achilles", 31);
  insertRoot("Olivia", 32);
  insertRoot("Ezra", 33);
  insertRoot("Amelia", 34);
  insertRoot("Levi", 35);
  insertRoot("Milo", 36);
  insertRoot("Astrid", 37);
  insertRoot("Penelope", 38);
  insertRoot("Jack", 39);
  insertRoot("Ethan", 40);
  insertRoot("Jasper", 41);
  insertRoot("Isabella", 42);
  insertRoot("Elijah", 43);
  insertRoot("Emma", 44);
  insertRoot("Hazel", 45);

  printInternalNode(root);

}
