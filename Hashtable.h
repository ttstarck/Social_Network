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
  // Constructor for Hashtable, initializes tableSize to 211.
  Hashtable();

  // Destructor for Hashtable.
  ~Hashtable();

  // Inserts person into Hashtable. Returns -1 if the table is full or person is already in the Hashtable.
  int insert(std::string name, int profileDataPointer, FriendNode* friendHead);

  // Finds position of name in the Hashtable. Returns NULL if table is full or person is not found.
  HashNode* lookUp(std::string name);

  // Prints Hashtable from position 0, to position tableSize-1.
  void print();

  // Returns string concatenation of all friends of name.
  std::string getFriends(std::string name);

  // Adds friendship between name1 and name2 in the Hashtable.
  void addFriendship(std::string name1, std::string name2);

  // Removes friendship between name1 and name2 in the Hashtable.
  void removeFriendship(std::string name1, std::string name2);
  
 private:
  // Size of table.
  int tableSize;

  // Hashtable
  HashNode** table;

  // Function used to calculate the position of name.
  int hashFunction(std::string name, int seed);
  
};

#endif //HASHTABLE_H
