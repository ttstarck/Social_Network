//
// Hashtable.cpp
// Social_Network
//

#include "Hashtable.h"

#include <iostream>

Hashtable::Hashtable(){
  
  tableSize = 211;

  table = new HashNode*[tableSize];

  for(int i = 0; i < tableSize; i++){
        table[i] = NULL;
  }
}

Hashtable::~Hashtable(){
}

int Hashtable::insert(std::string name, int profileDataPointer, FriendNode* friendHead){
  // If name is already in the Hashtable, exit insert function.
  if(lookUp(name) != NULL)
    return -1;

  // Else, find where name should be placed in the Hashtable using linear probing.
  int seed = 0;
  int hash = hashFunction(name,seed);
  while(table[hash] != NULL && seed < tableSize){
    seed++;
    hash = hashFunction(name,seed);
  }
  // If table is full, exit.
  if(seed == tableSize)
    return -1;

  // Initializing new Hashnode to insert.
  HashNode* entry = new HashNode;
  entry->name = name;
  entry->profileDataPointer = profileDataPointer;
  entry->friendHead = friendHead;

  // Insert Hashnode into the hashtable.
  table[hash] = entry;
 
  return 0;
}

HashNode* Hashtable::lookUp(std::string name){
  // Find where name .
  int seed = 0;
  int hash = hashFunction(name,seed);

  // If not found at first hash position, use linear probing to find hash of name. 
  while(table[hash] != NULL && table[hash]->name != name && seed < tableSize){
    seed++;
    hash = hashFunction(name,seed);
  }
  
  // If name found, returns HashNode that stores name in Hashtable
  // If name not found, returns NULL
  if(seed == tableSize)
    return NULL;
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

  // Inserts all the friends of 'name' into friendsStr.
  std::string friendsStr = "";
  while(nodeFriend != NULL){
    friendsStr += nodeFriend->name;
    nodeFriend = nodeFriend->nextFriend;
    if(nodeFriend != NULL)
      friendsStr += ",";
  }
  
  return friendsStr;
}

void Hashtable::addFriendship(std::string name1, std::string name2){
  HashNode* person1 = lookUp(name1);
  HashNode* person2 = lookUp(name2);

  // If one of the two people aren't in the Hashtable, return.
  if(person1 == NULL || person2 == NULL)
    return;
  
  FriendNode* friendsList1 = person1->friendHead;
  FriendNode* friendsList2 = person2->friendHead;

  // Searches to make sure the two people aren't already friends.
  while(friendsList1 != NULL){
    if(friendsList1->name == name2){
      return;
    }
    friendsList1 = friendsList1->nextFriend;
  }

  // Adds name1 to the friendslist of name2
  FriendNode* friend1 = new FriendNode;
  friend1->name = name1;
  friend1->nextFriend = person2->friendHead;
  person2->friendHead = friend1;

  // Adds name2 to the friendslist of name1
  FriendNode* friend2 = new FriendNode;
  friend2->name = name2;
  friend2->nextFriend = person1->friendHead;
  person1->friendHead = friend2;
}

void Hashtable::removeFriendship(std::string name1, std::string name2){
  HashNode* person1 = lookUp(name1);
  HashNode* person2 = lookUp(name2);

  // If one of the two people aren't in the Hashtable, return.
  if(person1 == NULL || person2 == NULL)
    return;
  
  FriendNode* friendsList1 = person1->friendHead;
  FriendNode* friendsList2 = person2->friendHead;

  // If name2 is name1's first friend, remove friendship.
  if(friendsList1 != NULL && friendsList1->name == name2){
    FriendNode* tempFriend = friendsList1;
    person1->friendHead = tempFriend->nextFriend;
    delete tempFriend;
  }
  else{ // Else, see if name2 is in the rest of name1's friends. If name2 is in the list, remove name2.
    while(friendsList1 != NULL && friendsList1->nextFriend != NULL){
      if(friendsList1->nextFriend->name == name2){
	FriendNode* tempFriend = friendsList1->nextFriend;
	friendsList1->nextFriend = tempFriend->nextFriend;
	delete tempFriend;
	break;
      }
      friendsList1 = friendsList1->nextFriend;
    }
  }
   // If name1 is name2's first friend, remove friendship.
  if(friendsList2 != NULL && friendsList2->name == name1){
    FriendNode* tempFriend = friendsList2;
    person2->friendHead = tempFriend->nextFriend;
    delete tempFriend;
  }
  else{ // Else, see if name1 is in the rest of name2's friends. If name1 is in the list, remove name1.
    while(friendsList2 != NULL && friendsList2->nextFriend != NULL){
      if(friendsList2->nextFriend->name == name1){
	FriendNode* tempFriend = friendsList2->nextFriend;
	friendsList2->nextFriend = tempFriend->nextFriend;
	delete tempFriend;
	break;
      }
      friendsList2 = friendsList2->nextFriend;
    }
  }
}

int Hashtable::hashFunction(std::string name, int seed){
  long hash = 0;
  for(int i = 0;i < int(name.length());i++){
    hash = hash * 101 + int(name[i]);
  }
  return (hash + seed) % 201;
}


