//
// Hashtable.h
// Social_Network
//
#ifndef HASHTABLE_H
#define HASHTABLE_H

class Hashtable{
public:
	
	Hashtable();

	~Hashtable();

	int insert();

	int lookUp();

private:

	struct FriendNode{

	};

	struct Node{

	};

	Node** table;

	int hashFunction();

};

#endif //HASHTABLE_H