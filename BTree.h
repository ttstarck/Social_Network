//
// BTree.h
// Social_Network
//

#ifndef BTREE_H
#define BTREE_H

#include <string>

class BTree{

public:

	BTree();

	int insert(std::string name, int profileDataPointer);

private:

	struct ItemNode{
		int profileDataPointer;
		std::string name;
	};

	struct LeafNode{
		ItemNode** items;
	};

	struct InternalNode{
		std::string* names;
		InternalNode** nextNodes;
		bool isLeaf;
		LeafNode** leaves;
	};

	InternalNode* root;

	int M;

	int L;

	int numItemsInTree;

	void splitInternalNode(InternalNode* node);

};

#endif //BTREE_H
