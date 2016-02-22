//
// Hashtable.h
// Social_Network
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <string>

class Hashtable{
public:
	
	Hashtable();

	~Hashtable();

	int insert(std::string name, int profileDataPointer, FriendNode* friendHead);

	HashNode* lookUp(std::string name);

	void print();

	std::string getFriends(int profileDataPointer);

private:

	int tableSize;
	
	HashNode** table;

	int hashFunction(std::string name, int seed);

};

#endif //HASHTABLE_H
