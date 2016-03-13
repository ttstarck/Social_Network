//
// main.cpp
// Social_Network
//
#include "FSeeker.h"
#include "FriendNode.h"
#include "Hashtable.h"
#include "HashNode.h"
#include "BTree.h"

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

    // fileName is the document we are adding to
    string fileName = "ProfileData.txt";
    FSeeker* f = new FSeeker(fileName);

    // input.txt are the people that we initially insert into the social network
    ifstream file("input.txt");
    string line;

    Hashtable* h = new Hashtable();
    BTree* b = new BTree();

    //parse through the input.txt line by line    
    while(getline(file,line)){
      string name = "";
      string occupation = "";
      string age = "";

      FriendNode* friendHead = new FriendNode;
      friendHead->name = "";
      friendHead->nextFriend = NULL;

      FriendNode* fNode = friendHead;
      bool anotherFriend = false;

      //position is to keep track of 
      int position = 0;
      int currentFriend = 0;

      //parse through each person's line in input.txt
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
      cout << "Inserting: " << name << endl;
      f->insert(name, age, occupation, numInserted);
      h->insert(name, numInserted, friendHead);
      b->insertRoot(name,numInserted);
      numInserted++;
    }
    
    while(true)
      {
	string str;
	cin >> str;
	if(cin.eof())
	  {
	    break;
	  }
	if(str.compare("exit") == 0)
	  {
	    break;
	  }
	else if(str.compare("insert") == 0)
	  {
	    string profile = "";
	    string name = "";
	    string age = "";
	    string occupation = "";
     
	    cin >> name >> age;
	    getline(cin, occupation);

	    f->insert(name,age,occupation,numInserted);
	    h->insert(name, numInserted, NULL);
	    b->insertRoot(name,numInserted);
	    numInserted++;
	  }
	else if(str.compare("rangeQuery") == 0){
	  string name1;
	  string name2;

	  cin >> name1 >> name2;

	  b->getRange(name1, name2, f);
	
	}
	else if(str.compare("addFriendship") == 0)
	  {
	    string name1;
	    string name2;
	    cin >> name1 >> name2;
	    h->addFriendship(name1, name2);
	  }
	else if(str.compare("removeFriendship") == 0)
	  {
	    string name1;
	    string name2;
	    cin >> name1 >> name2;
	    h->removeFriendship(name1, name2);
	  }
	else if(str.compare("getFriendsProfileData") == 0)
	  {
	    string name;
	    cin >> name;
	    getFriendsProfileData(name, h, f);
	  }
	else if(str.compare("printAll") == 0)
	  {
	    printSocialNetwork(h,f,numInserted);
	  }
	else if(str.compare("printBTree") == 0)
	  {
	    b->printBTree();

	  }
	else if(str.compare("insertFile") == 0)
          {
	    std::string fileName;
	    cin >> fileName;
	    ifstream file(fileName);

	    //parse through the input.txt line by line
	    while(getline(file,line)){
	      string name = "";
	      string occupation = "";
	      string age = "";

	      FriendNode* friendHead = new FriendNode;
	      friendHead->name = "";
	      friendHead->nextFriend = NULL;

	      FriendNode* fNode = friendHead;
	      bool anotherFriend = false;

	      //position is to keep track of
	      int position = 0;
	      int currentFriend = 0;

	      //parse through each person's line in input.txt
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
	      cout << "Inserting: " << name << endl;
	      f->insert(name, age, occupation, numInserted);
	      h->insert(name, numInserted, friendHead);
	      b->insertRoot(name,numInserted);
	      numInserted++;
	    }
	  }

	else
	  {
	    cin.clear();
	    cout << "Inputed string format was incorrect" << endl;
	  }	  
      }
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
      cout << f->getProfileData(i) << "," << h->getFriends(name) << endl;
    }
  }


















