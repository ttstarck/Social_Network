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

	std::string getFriends(std::string name);

	void addFriendship(std::string name1, std::string name2);

private:

	int tableSize;
	
	HashNode** table;

	int hashFunction(std::string name, int seed);

};

#endif //HASHTABLE_H
