//
// SN_Tests.cpp
// Social_Network
//

#include "Hashtable.h"

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
	if(h->lookUp("stub") == NULL){
		numTestsPassed++;
		cout << pass << endl;
	}
	else{
		cout << "	Expected result: " << "NULL" << " Actual result: " << h->lookUp("stub") << endl;
		numTestsFailed++;
		cout << fail << endl;
	}
	cout << "Results for HashTable tests:" << endl;
	cout << "Tests passed:" << numTestsPassed << endl;
	cout << "Tests failed:" << numTestsFailed << endl;
}


int main(){
	
	hashTableTest();

	return 0;
}
