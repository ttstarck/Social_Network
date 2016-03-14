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

    // Add data to ProfileData.txt
    string fileName = "ProfileData.txt";
    FSeeker* f = new FSeeker(fileName);

    // Use entries in input.txt to add to the Social Network
    ifstream file("input.txt");
    string line;

    Hashtable* h = new Hashtable();
    BTree* b = new BTree();

    // Parse through the input.txt line by line    
    while(getline(file,line)){
      string name = "";
      string occupation = "";
      string age = "";

      FriendNode* friendHead = new FriendNode;
      friendHead->name = "";
      friendHead->nextFriend = NULL;

      FriendNode* fNode = friendHead;
      bool anotherFriend = false;

      // Keep track of position so we know when we are reading in friends. 
      int position = 0;
      int currentFriend = 0;

      // Read in the data of each person in input.txt
      for(size_t i = 0; i < line.length(); i++){
        if(line[i] == '\n')
          break;
        if(line[i] == ','){
          position++;

	  // After the third element, prepare to add a non-root member of FriendNode by setting anotherFriend to true.
          if(position > 3)
            anotherFriend = true;
        }

	// Add the first element as the name.
        else if(position == 0)
          name += line[i];

	// Add the second element as the age.
        else if(position == 1){
          age += line[i];
        }

	// Add the third element as the occupation.
        else if(position == 2){
          occupation += line[i];
        }
        else{
	  // If line[i] is a non-root friend, make it into a FriendNode and add it to the linked list.
          if(anotherFriend){
            FriendNode* node = new FriendNode;
            node->name = line[i];
            node->nextFriend = NULL;
            fNode->nextFriend = node;
            fNode = fNode->nextFriend;
            anotherFriend = false;
          }
	  // If line[i] is the root of the linked list of FriendNodes, add it as the head.
          else{
            fNode->name += line[i];
          }
        }
      }

      // Insert each person's data into:
      cout << "Inserting: " << name << endl;
      // the ProfileData.txt file,
      f->insert(name, age, occupation, numInserted);
      // the hash table,
      h->insert(name, numInserted, friendHead);
      // and the B-Tree.
      b->insertRoot(name,numInserted);
      numInserted++;
    }
    
    while(true)
      {
	// Read in each line of input to str.
	string str = "";
	getline(cin, str);

	if(cin.eof())
	  {
	    break;
	  }

	// Type exit to end the program.
	if(str.compare("exit") == 0)
	  {
	    break;
	  }

	// Type insert and a person and their information to insert them into the Social Network.
	else if(str.compare("insert") == 0)
	  {
	    string profile = "";
	    string name = "";
	    string age = "";
	    string occupation = "";

	    // Print who is being inserted. And assign each piece of information to variables.
	    cout << "Name: ";
	    getline(cin,name);
	    cout << "Age: ";
	    getline(cin,age);
	    cout << "Occupation: ";
	    getline(cin, occupation);

	    // Insert int the ProfileData.txt, hash table, and the B-Tree.
	    f->insert(name,age,occupation,numInserted);
	    h->insert(name, numInserted, NULL);
	    b->insertRoot(name,numInserted);
	    numInserted++;
	  }

	// Type rangeQuery and two names to print the name, age, and 
	// occupation of the people with names that fall alphabetically between the two names.
	else if(str.compare("rangeQuery") == 0){
	  string name1 = "";
	  string name2 = "";

	  // Print the name of the bounds of the range query and take assign these names to variables.
	  cout << "First person's name: ";
	  getline(cin, name1);
	  cout << "Second person's name: ";
	  getline(cin, name2);
	  
	  // Use B-Tree to do query.
	  b->getRange(name1, name2, f);
	
	}

	// Type addFriendship to add a friendship between two people.
	else if(str.compare("addFriendship") == 0)
	  {
	    string name1 = "";
	    string name2 = "";

	    // Print the names of the people who are becoming friends and assign these names to variables.
	    cout << "First person's name: ";
	    getline(cin, name1);
	    cout << "Second person's name: ";
	    getline(cin, name2);

	    // Add the friendship in the hash table.
	    h->addFriendship(name1, name2);
	  }
	else if(str.compare("removeFriendship") == 0)
	  {
	    string name1 = "";
	    string name2 = "";

	    // Print the names of the people who are removing each other as friends and assign these names to variables.
	    cout << "First person's name: ";
	    getline(cin, name1);
	    cout << "Second person's name: ";
	    getline(cin, name2);

	    // Remove the friendship from the hash table.
	    h->removeFriendship(name1, name2);
	  }

	// Type getFriendsProfileData to get the names, ages, and occupations of a person's friends.
	else if(str.compare("getFriendsProfileData") == 0)
	  {
	    string name = "";
	    
	    // Print the name of the person whose friends we want information about.
	    cout << "Name: ";
	    getline(cin, name);

	    // Call the function to get the profileData of a person's friends.
	    getFriendsProfileData(name, h, f);
	  }

	// Type printAll to print all the elements in ProfileData.txt.
	else if(str.compare("printAll") == 0)
	  {

	    //Call a function to print the elements in ProfileData.txt.
	    cout << "Printing Social Network" << endl;
	    printSocialNetwork(h,f,numInserted);
	  }

	// Type printBTree to do a rough print of the B-Tree.
	else if(str.compare("printBTree") == 0)
	  {

	    // Call a function of the B-Tree to print the tree.
	    cout << "Printing BTree" << endl;
	    b->printBTree();

	  }

	// Type insertFile to insert the people in a file into the social network.
	else if(str.compare("insertFile") == 0)
          {
	    std::string fileName = "";

	    // Print the name of the file that is going to be inserted and use the ifstream to parse the file.
	    cout << "File Name: ";
	    getline(cin, fileName);
	    ifstream file(fileName);

	    // Parse through the input.txt line by line    
	    while(getline(file,line)){
	      string name = "";
	      string occupation = "";
	      string age = "";

	      FriendNode* friendHead = new FriendNode;
	      friendHead->name = "";
	      friendHead->nextFriend = NULL;

	      FriendNode* fNode = friendHead;
	      bool anotherFriend = false;

	      // Keep track of position so we know when we are reading in friends. 
	      int position = 0;
	      int currentFriend = 0;

	      // Read in the data of each person in input.txt
	      for(size_t i = 0; i < line.length(); i++){
		if(line[i] == '\n')
		  break;
		if(line[i] == ','){
		  position++;

		  // After the third element, prepare to add a non-root member of FriendNode by setting anotherFriend to true.
		  if(position > 3)
		    anotherFriend = true;
		}

		// Add the first element as the name.
		else if(position == 0)
		  name += line[i];

		// Add the second element as the age.
		else if(position == 1){
		  age += line[i];
		}

		// Add the third element as the occupation.
		else if(position == 2){
		  occupation += line[i];
		}
		else{

		  // If line[i] is a non-root friend, make it into a FriendNode and add it to the linked list.
		  if(anotherFriend){
		    FriendNode* node = new FriendNode;
		    node->name = line[i];
		    node->nextFriend = NULL;
		    fNode->nextFriend = node;
		    fNode = fNode->nextFriend;
		    anotherFriend = false;
		  }

		  // If line[i] is the root of the linked list of FriendNodes, add it as the head.
		  else{
		    fNode->name += line[i];
		  }
		}
	      }

	      // Insert each person's data into the ProfileData.txt file, hash table, and B-Tree.
	      cout << "Inserting: " << name << endl;
	      f->insert(name, age, occupation, numInserted);
	      h->insert(name, numInserted, friendHead);
	      b->insertRoot(name,numInserted);
	      numInserted++;
	    }
	  }
	// If what we typed doesn't match any of the above strings, print that the format of the input was incorrect.
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

// Function to print a person's friend's names, ages, and occupations.
void getFriendsProfileData(string name,Hashtable* h, FSeeker* f){

  // Use the hash table's lookup function to look up the HashNode of the person.
  HashNode* person = h->lookUp(name);

  // If the function returns NULL, the person isn't in the social network, so return from the function.
  if(person == NULL)
    return;

  // Make friendHead equal to the head of the linked list of the person's friends.
  FriendNode* friendHead = person->friendHead;
  cout << "Profile data on the friends of " << name << endl;

  // Parse through the linked list of friends. 
  while(friendHead != NULL){
    string friendName = friendHead->name;
    // Look up each friend.
    HashNode* friendHashN = h->lookUp(friendName);
    if(friendHashN != NULL){
      // Get the name, age, and occupation of each friend.
      cout << f->getProfileData(friendHashN->profileDataPointer) << endl;
    }
    friendHead = friendHead->nextFriend;
  }

  // Once we reach the end of the linked list, return.
  if(friendHead == NULL)
    return;
}

// Print all the names, ages, occupations, and friends of each person in the social network.
void printSocialNetwork(Hashtable* h, FSeeker* f, int totalUsers){
  for(int i = 0; i < totalUsers; i++){
    // For each name, get the profile data using the Fseeker and get the friends using the hash table.
    string name = f->getName(i);
    cout << f->getProfileData(i) << "," << h->getFriends(name) << endl;
  }
}


















