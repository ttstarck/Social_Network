//
// FSeeker.h
// Social_Network
//

#ifndef FSEEKER_H
#define FSEEKER_H

#include "FriendNode.h"
#include <string>
#include <stdlib.h>

class FSeeker{
 public:
  // Constructor for FSeeker, opens a FILE with the name fileName.
  FSeeker(std::string fileName);
  
  // Inserts person into pFile at numInserted position.
  std::string insert(std::string name, std::string age, std::string occupation, int numInserted);
		
  // Calls getName, getOccupation, getAge.			
  std::string getProfileData(int profileDataPointer);

  // Returns the name of the person at profileDataPointer
  std::string getName(int profileDataPointer);

  // Returns the occupation of the person at profileDataPointer
  std::string getOccupation(int profileDataPointer);

// Returns the age of the person at profileDataPointer
  std::string getAge(int profileDataPointer);

 private:
  const char* fileName;

  // FILE that is being accessed.
  FILE * pFile;

};
#endif // FSEEKER_H
