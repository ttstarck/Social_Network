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

  FSeeker(std::string fileName);
  
  std::string insert(std::string name, std::string age, std::string occupation, int numInserted);
		
  std::string getProfileData(int profileDataPointer);

  std::string getName(int profileDataPointer);

  std::string getOccupation(int profileDataPointer);

  std::string getAge(int profileDataPointer);

 private:
  const char* fileName;

  FILE * pFile;

};

#endif
