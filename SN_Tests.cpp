//
// SN_Tests.cpp
// Social_Network
//

#include "Hashtable.h"
#include "FSeeker.h"

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
  cout << "insert function: ";
  if(h->insert("stub", -42, NULL) == -42){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << "	Expected result: " << -42 << " Actual result: " << h->insert("stub", -42, NULL) << endl;
    cout << fail << endl;
  }
  cout << "lookUp function: ";
  if((h->lookUp("stub")) == NULL){                                                           //I think we are going to want to eventually replace h->lookup("stub") with h->lookup("stub")->name
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "	Expected result: " << "NULL" << " Actual result: " << (h->lookUp("stub")) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "Results for HashTable tests:" << endl;
  cout << "Tests passed:" << numTestsPassed << endl;
  cout << "Tests failed:" << numTestsFailed << endl;
}



void FSeekerTest(){
  string fail = "Test failed.";
  string pass = "Test passed.";

  FSeeker* f = new FSeeker("input.txt");

  int numTestsPassed = 0;
  int numTestsFailed = 0;

  cout << "Running tests on Hashtable:" << endl;
  cout << "insert function: ";
  if(f->insert("Kanye", 38, "musician")=="inserted"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    numTestsFailed++;
    cout << "   Expected result: " << "inserted" << " Actual result: " << f->insert("Kanye", 38, "musician") << endl;
    cout << fail << endl;
  }
  cout << "getProfileData function: ";
  if(f->getProfileData(0)=="Kanye38musician"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "   Expected result: " << "Kanye38musician" << " Actual result: " << (f->getProfileData(0)) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "getName function: "; 
 if(f->getName(0)=="Kanye"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "   Expected result: " << "Kanye" << " Actual result: " << (f->getName(0)) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
 cout << "getOccupation function: ";
   if(f->getOccupation(0)=="musician"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "   Expected result: " << "musician" << " Actual result: " << (f->getOccupation(0)) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
   cout << "getAge function: ";
   if(f->getAge(0)=="38"){
    numTestsPassed++;
    cout << pass << endl;
  }
  else{
    cout << "   Expected result: " << "38" << " Actual result: " << (f->getAge(0)) << endl;
    numTestsFailed++;
    cout << fail << endl;
  }
  cout << "Results for FSeeker tests:" << endl;
  cout << "Tests passed:" << numTestsPassed << endl;
  cout << "Tests failed:" << numTestsFailed << endl;


}


int main(){
	
  hashTableTest();
  cout<<"\n";
  FSeekerTest();

  return 0;
}
