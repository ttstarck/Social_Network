//
// FSeeker.h
// Social_Network
//

#ifndef FSEEKER_H
#define FSEEKER_H

#include "FriendNode.h"
#include <string>

class FSeeker{
	public:

		FSeeker(char* fileName);

		std::string insert(std::string name, int age, std::string occupation);

		std::string getProfileData(int profileDataPointer);

		std::string getName(int profileDataPointer);

		std::string getOccupation(int profileDataPointer);

		std::string getAge(int profileDataPointer);

	private:
		char* fileName;


};

#endif
