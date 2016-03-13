//
// FriendNode.h
// Soical_Network
//

#ifndef FRIENDNODE_H
#define FRIENDNODE_H

#include <string>

// class for nodes in a linked list that each contains a friend's name
class FriendNode{
	public:
		FriendNode* nextFriend;
		std::string name;
};

#endif //FRIENDNODE_H
