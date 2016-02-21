//
// FSeeker.h
// Social_Network
//

#ifndef FSEEKER_H
#define FSEEKER_H

#include "HashNode.h"
#include <string>

class FSeeker{
	public:

		FSeeker(std::string fileName);

		std::string insert(HashNode* addData);

		std::string getProfileData(int profileDataPointer);

		std::string getName(int profileDataPointer);

		std::string getOccupation(int profileDataPointer);

		std::string getAge(int profileDataPointer);

	private:
		std::string fileName;


};

#endif
