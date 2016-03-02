//
// SN_Tests.cpp
// Social_Network
//

#include "Hashtable.h"
#include "FSeeker.h"
#include "FriendNode.h"

#include <iostream>
#include <string>

using namespace std;
void hashTableTest(){
  string fail = "Test failed.";
  string pass = "Test passed.";
	
  Hashtable* h = new Hashtable();
  int numTestsPassed = 0;
  int numTestsFailed = 0;

  cout << "Running tests on Hashtable:" << endl;
  cout << "insert function1: ";
  
  int insertValue1 = h->insert("stub",-42,NULL);
  if(insertValue1 == 0){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << "	Expected result: " << 0 << " Actual result: " << insertValue1 << endl;
    cout << fail << endl;
  }
  
  cout << "insert function2: ";
  FriendNode* fNode = new FriendNode;
  fNode->name = "Bob";
  FriendNode* fNode1 = new FriendNode;
  fNode1->name = "Bill";
  fNode1->nextFriend = NULL;
  fNode->nextFriend = fNode1;
  int insertValue2 = h->insert("Chris",2,fNode);
  if(insertValue2 == 0){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << " Expected result: " << 0 << " Actual result: " << insertValue2 << endl;
    cout << fail << endl;
  }
  
  cout << "lookUp function1: ";
  if((h->lookUp("stub")->name) == "stub"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "	Expected result: " << "stub" << " Actual result: ";
    if(h->lookUp("stub") != NULL)
      cout << (h->lookUp("stub")->name) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "lookUp function2: ";
  if( h->lookUp("Chris")!= NULL && (h->lookUp("Chris")->name) == "Chris"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << " Expected result: " << "Chris" << " Actual result: ";
    if(h->lookUp("Chris")!= NULL)
      cout << (h->lookUp("Chris")->name) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "getFriends function1: ";
  if( h->getFriends("stub") == ""){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << " Expected result: " << "" << " Actual result: " << (h->getFriends("stub")) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "getFriends function2: ";
  if( h->getFriends("Chris") == "Bob Bill"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << " Expected result: " << "Bob Bill" << " Actual result: " << (h->getFriends("Chris")) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }

  cout << "Printing HashTable h:" << endl;
  h->print();

  cout << "\nResults for HashTable tests:" << endl;
  cout << "Tests passed:" << numTestsPassed << endl;
  cout << "Tests failed:" << numTestsFailed << endl;

}



void FSeekerTest(){
  string fail = "Test failed.";
  string pass = "Test passed.";
  std::string fileNameC = "ProfileData.txt";
  const char* fileName = fileNameC.c_str();
  FSeeker* f = new FSeeker(fileName);

  int numTestsPassed = 0;
  int numTestsFailed = 0;

  cout << "Running tests on FSeeker:" << endl;
  cout << "insert function1: ";
  std::string insertStr1 = f->insert("Kanye", "38", "musician",0);
  if(insertStr1=="inserted"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << fail << "   Expected result: " << "inserted" << " Actual result: " << insertStr1 << endl;
  }
 cout << "insert function2: ";
 std::string insertStr2 = f->insert("Jennifer", "47", "actress",1);
  if(insertStr2=="inserted"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << fail << "   Expected result: " << "inserted" << " Actual result: " << insertStr2 << endl;
  }
  
  cout << "getProfileData function: ";
  if(f->getProfileData(0)=="Kanye,38,musician"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout <<  fail << "   Expected result: " << "Kanye,38,musician" << " Actual result: " << (f->getProfileData(0)) << endl;
    numTestsFailed++;
  }
  cout << "getName function: "; 
 if(f->getName(0)=="Kanye"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << fail << "   Expected result: " << "Kanye" << " Actual result: " << (f->getName(0)) << endl;
    numTestsFailed++;
  }
 cout << "getOccupation function: ";
   if(f->getOccupation(0)=="musician"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << fail << "   Expected result: " << "musician" << " Actual result: " << (f->getOccupation(0)) << endl;
    numTestsFailed++;
  }
   cout << "getAge function: ";
   if(f->getAge(0)=="38"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << fail << "   Expected result: " << "38" << " Actual result: " << (f->getAge(0)) << endl;
    numTestsFailed++;
  }
  cout << "\nResults for FSeeker tests:" << endl;
  cout << "Tests passed:" << numTestsPassed << endl;
  cout << "Tests failed:" << numTestsFailed << endl << endl;


}


int main(){
	
  hashTableTest();
  cout<<"\n";
  FSeekerTest();

  return 0;
}
