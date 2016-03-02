//
// main.cpp
// Social_Network
//
#include "FSeeker.h"
#include "FriendNode.h"
#include "Hashtable.h"
#include "HashNode.h"
//#include "BTree.h"

#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

void getFriendsProfileData(string name, Hashtable* h, FSeeker* f);

void printSocialNetwork(Hashtable* h, FSeeker* f, int totalUsers);

int main(){
  try{
    int numInserted = 0;

    string fileName = "ProfileData.txt";
    FSeeker* f = new FSeeker(fileName);

    ifstream file("input.txt");
    string line;
    Hashtable* h = new Hashtable();
    
    while(getline(file,line)){

      string name = "";
      string occupation = "";
      string age = "";

      FriendNode* friendHead = new FriendNode;
      friendHead->name = "";
      friendHead->nextFriend = NULL;

      FriendNode* fNode = friendHead;
      bool anotherFriend = false;

      int position = 0;
      int currentFriend = 0;
      for(size_t i = 0; i < line.length(); i++){
        if(line[i] == '\n')
          break;
        if(line[i] == ','){
          position++;
          if(position > 3)
            anotherFriend = true;
        }
        else if(position == 0)
          name += line[i];
        else if(position == 1){
          age += line[i];
        }
        else if(position == 2){
          occupation += line[i];
        }
        else{
          if(anotherFriend){
            FriendNode* node = new FriendNode;
            node->name = line[i];
            node->nextFriend = NULL;
            fNode->nextFriend = node;
            fNode = fNode->nextFriend;
            anotherFriend = false;
          }
          else{
            fNode->name += line[i];
          }
        }
      }
      cout << "Profile data for " << name << endl << "Occupation: " << occupation << endl << "Age: " <<  age << endl << "Friends: ";
      FriendNode* node = friendHead;
      while(node != NULL && node->nextFriend != NULL){
        cout << node->name << ",";
        node = node->nextFriend;
      }
      cout << node->name << endl;
      f->insert(name, age, occupation, numInserted);
      h->insert(name, numInserted, friendHead);
      numInserted++;
      // Insert into Hashtable, BTree, and ProfileData
    }
    h->print();

    printSocialNetwork(h, f, numInserted);
    /*
    
    DONE: getFriendsProfileData and addFriendship both works here

    getFriendsProfileData("Wyatt", h, f);
    getFriendsProfileData("Dominic", h, f);
    h->addFriendship("Wyatt", "Dominic");
    getFriendsProfileData("Wyatt", h, f);
    getFriendsProfileData("Dominic", h, f);
    
    */

  }
  catch(exception& ex){
    cerr << ex.what() << endl;
  }
}

void getFriendsProfileData(string name,Hashtable* h, FSeeker* f){
  HashNode* person = h->lookUp(name);
  if(person == NULL)
    return;
  FriendNode* friendHead = person->friendHead;
  
  cout << "Profile data on the friends of " << name << endl;

  while(friendHead != NULL){
    string friendName = friendHead->name;
    HashNode* friendHashN = h->lookUp(friendName);
    if(friendHashN != NULL){
      cout << f->getProfileData(friendHashN->profileDataPointer) << endl;
    }
    friendHead = friendHead->nextFriend;
  }

  if(friendHead == NULL)
    return;
}

void printSocialNetwork(Hashtable* h, FSeeker* f, int totalUsers){
  for(int i = 0; i < totalUsers; i++){
    string name = f->getName(i);
    //cout << name << endl;
    cout << f->getProfileData(i) << "," << h->getFriends(name) << endl;
  }
}


















