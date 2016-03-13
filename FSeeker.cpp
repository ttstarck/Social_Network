//
// FSeeker.cpp
// Social_Network
//
#include "FSeeker.h"
#include "BTree.h"
#include "Hashtable.h"
#include "FriendNode.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

FSeeker::FSeeker(std::string fileName){
  this->fileName=fileName.c_str();
  
  pFile = fopen ( this->fileName , "w+" );
}

//I am starting by inserting to the end of the file
std::string FSeeker::insert(std::string name, std::string age, std::string occupation, int numInserted){
  
  const char * addName = name.c_str();
  const char * addAge = age.c_str();
  const char * addOccupation = occupation.c_str();

  fseek(pFile, 53*numInserted, SEEK_SET);
  fputs ( addName , pFile );
  // seek 20 bytes from the beginning of the file.
  fseek ( pFile , 20-strlen(addName), SEEK_CUR );
  fputs ( addAge , pFile );
  fseek ( pFile , 3-strlen(addAge) , SEEK_CUR);
  fputs ( addOccupation, pFile);
  fseek ( pFile , 30-strlen(addOccupation) , SEEK_CUR );

  return "inserted";
}

std::string FSeeker::getProfileData(int profileDataPointer){
  std::string profileData = "";
  profileData += getName(profileDataPointer);
  profileData += "," + getAge(profileDataPointer);
  profileData += "," + getOccupation(profileDataPointer);

  return profileData;
}

std::string FSeeker::getName(int profileDataPointer){
  int nameStart = profileDataPointer*53;
  char* nameData = new char[20];
  FILE * rFile;
  rFile = fopen ( fileName , "r" );
  fseek(rFile, nameStart, SEEK_SET);
  nameData = fgets(nameData, 20, rFile);

  fclose(rFile);

  std::string nameDataStr = nameData;

  delete[] nameData;

  return nameDataStr;
}

std::string FSeeker::getOccupation(int profileDataPointer){
  int occupationStart = profileDataPointer*53+23;
  char* occupationData = new char[30];
  FILE * rFile;
  rFile = fopen ( fileName , "r" );
  fseek(rFile, occupationStart, SEEK_SET);
  occupationData = fgets(occupationData, 30, rFile);

  fclose(rFile);

  std::string occupationDataStr = occupationData;

  delete[] occupationData;

  return occupationDataStr;
}

std::string FSeeker::getAge(int profileDataPointer){
  int ageStart = profileDataPointer*53+20;
  char* ageData = new char[3];
  FILE * rFile;
  rFile = fopen ( fileName , "r" );
  fseek(rFile, ageStart, SEEK_SET);
  ageData = fgets(ageData, 3, rFile);

  fclose(rFile);

  std::string ageDataStr = ageData;

  delete[] ageData;

  return ageDataStr;
}
