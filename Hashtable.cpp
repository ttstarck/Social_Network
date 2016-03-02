//
// Hashtable.cpp
// Social_Network
//

#include "Hashtable.h"

#include <iostream>

Hashtable::Hashtable(){
  
  tableSize = 201;

  table = new HashNode*[tableSize];

  for(int i = 0; i < tableSize; i++){
        table[i] = NULL;
  }
}

Hashtable::~Hashtable(){
  // STUB!!!
}

int Hashtable::insert(std::string name, int profileDataPointer, FriendNode* friendHead){
  if(lookUp(name) != NULL)
    return -1;
  int seed = 0;
  int hash = hashFunction(name,seed);
  while(table[hash] != NULL && seed < tableSize){
    seed++;
    hash = hashFunction(name,seed);
  }
  if(seed == tableSize)
    return -42;
  HashNode* entry = new HashNode;
  entry->name = name;
  entry->profileDataPointer = profileDataPointer;
  entry->friendHead = friendHead;
  table[hash] = entry;
  // STUB!!!
  //  name="stub"; profileDataPointer=-42; friendHead = NULL; //I am doing this so we don't get unused parameter errors when compiling
  return 0;
}

HashNode* Hashtable::lookUp(std::string name){
  // STUB!!!
  //name="stub"; //I am doing this so we don't get unused parameter errors when compiling
  int seed = 0;
  int hash = hashFunction(name,seed);
  while(table[hash] != NULL && table[hash]->name != name && seed < tableSize){
    seed++;
    hash = hashFunction(name,seed);
    //std::cout << "Searching table in lookUp: " << seed <<  " " << hash << std::endl;
  }
  //std::cout << "Hash: " << hash << std::endl;
  return table[hash];
}

void Hashtable::print(){
  for(int i = 0; i < tableSize; i++){
      if(table[i] != NULL){
        std::cout <<"( Position: " << i << " Name: " << table[i]->name << " ProfileDataPointer: " << table[i]->profileDataPointer << ", Friends: ";
        for(FriendNode* j = table[i]->friendHead; j != NULL; j = j->nextFriend){
          std::cout << j->name << ", ";
        }
        std::cout<<")"<< std::endl;
      }
  }
}

std::string Hashtable::getFriends(std::string name){
  HashNode* node = lookUp(name);
  FriendNode* nodeFriend;
  if(node != NULL)
    nodeFriend = node->friendHead;
  else
    return "";
  std::string friendsStr = "";
  while(nodeFriend != NULL){
    friendsStr += nodeFriend->name;
    nodeFriend = nodeFriend->nextFriend;
    if(nodeFriend != NULL && nodeFriend->nextFriend != NULL)
      friendsStr += ",";
  }
  return friendsStr;

}

void Hashtable::addFriendship(std::string name1, std::string name2){
  HashNode* person1 = lookUp(name1);
  HashNode* person2 = lookUp(name2);
  
  if(person1 == NULL || person2 == NULL)
    return;
  
  FriendNode* friendsList1 = person1->friendHead;
  FriendNode* friendsList2 = person2->friendHead;
  
  while(friendsList1 != NULL){
    if(friendsList1->name == name2){
      return;
    }
    friendsList1 = friendsList1->nextFriend;
  }

  FriendNode* friend1 = new FriendNode;
  friend1->name = name1;
  friend1->nextFriend = person2->friendHead;
  person2->friendHead = friend1;

  FriendNode* friend2 = new FriendNode;
  friend2->name = name2;
  friend2->nextFriend = person1->friendHead;
  person1->friendHead = friend2;

}

int Hashtable::hashFunction(std::string name, int seed){
  long hash = 0;
  for(int i = 0;i < int(name.length());i++){
    hash = hash * 101 + int(name[i]);
  }
  //std::cout << "Hashtable for loop" << hash <<std::endl;
  return (hash + seed) % 201;
  // STUB!!!
  //name="stub"; seed=-42; //I am doing this so we don't get unused parameter errors when compiling
  //return -42;
}


