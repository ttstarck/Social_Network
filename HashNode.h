//
// HashNode.h
// Social_Network
//

#ifndef HASHNODE_H
#define HASHNODE_H

#include "FriendNode.h"

#include <string>

class HashNode{
	public:
		int profileDataPointer;
		FriendNode* friendHead;
		std::string name;
};

#endif
