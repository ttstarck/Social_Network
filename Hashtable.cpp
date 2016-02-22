//
// Hashtable.cpp
// Social_Network
//

#include "Hashtable.h"

#include <iostream>

Hashtable::Hashtable(){
  table = NULL;
  // STUB!!!
}

Hashtable::~Hashtable(){
  // STUB!!!
}

int Hashtable::insert(std::string name, int profileDataPointer, FriendNode* friendHead){
  // STUB!!!
  //  name="stub"; profileDataPointer=-42; friendHead = NULL; //I am doing this so we don't get unused parameter errors when compiling
  return -42;
}

HashNode* Hashtable::lookUp(std::string name){
  // STUB!!!
  //name="stub"; //I am doing this so we don't get unused parameter errors when compiling
  return NULL;
}

int Hashtable::hashFunction(std::string name, int seed){
  // STUB!!!
  //name="stub"; seed=-42; //I am doing this so we don't get unused parameter errors when compiling
  return -42;
}

std::string Hashtable::getFriends(int profileDataPointer){
  //STUB!!!
  return "stub";

}
