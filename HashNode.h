//
// HashNode.h
// Social_Network
//

#ifndef HASHNODE_H
#define HASHNODE_H

#include "FriendNode.h"

#include <string>

// class for the nodes of the hash table which contain the name of the person, their profileDataPointer, and a pointer to the linked list of FriendNodes
class HashNode{
	public:
		std::string name;
		int profileDataPointer;
		FriendNode* friendHead;
};

#endif
