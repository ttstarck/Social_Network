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

std::string FSeeker::insert(std::string name, std::string age, std::string occupation, int numInserted){
  
  // Convert name, age, and occupation to const char* so they are the correct type to insert into the file.
  const char * addName = name.c_str();
  const char * addAge = age.c_str();
  const char * addOccupation = occupation.c_str();

  // Go to the end of the file to insert the next person. Each person inserted is allotted 53 char's.
  fseek(pFile, 53*numInserted, SEEK_SET);
  
  // Insert name into the file. Then move the position by the difference of 20 and the length of name.
  fputs ( addName , pFile );
  fseek ( pFile , 20-strlen(addName), SEEK_CUR );
  
  // Insert age into the file. Then move the position by the difference of 3 and the length of age.
  fputs ( addAge , pFile );
  fseek ( pFile , 3-strlen(addAge) , SEEK_CUR);

  // Insert occupation into the file. Then move the position by the difference of 30 and the length of occupation.
  fputs ( addOccupation, pFile);
  fseek ( pFile , 30-strlen(addOccupation) , SEEK_CUR );

  return "inserted";
}

std::string FSeeker::getProfileData(int profileDataPointer){

  std::string profileData = "";
  
  // Adds the values recieved from called getName, getAge, and getOccupation into the string profileData.
  profileData += getName(profileDataPointer);
  profileData += "," + getAge(profileDataPointer);
  profileData += "," + getOccupation(profileDataPointer);

  return profileData;
}

std::string FSeeker::getName(int profileDataPointer){
  // Calculates the correct position of where the name starts in the file.
  int nameStart = profileDataPointer*53;

  // Name in the file is max 20 chars long.
  char* nameData = new char[20];

  // Opens fileName file with read argument.
  FILE * rFile;
  rFile = fopen ( fileName , "r" );

  // Go to the position nameStart in the file.
  fseek(rFile, nameStart, SEEK_SET);

  // Get name from the file, which is a max of 20 chars long.
  nameData = fgets(nameData, 21, rFile);

  fclose(rFile);

  std::string nameDataStr = nameData;

  delete[] nameData;

  return nameDataStr;
}

std::string FSeeker::getOccupation(int profileDataPointer){
  // Calculates the correct position of where the occupation starts in the file.
  int occupationStart = profileDataPointer*53+23;

  // Occupation is max 30 chars long.
  char* occupationData = new char[30];

  // Opens fileName file with read argument.
  FILE * rFile;
  rFile = fopen ( fileName , "r" );

  // Go to the position occupationStart in the file.
  fseek(rFile, occupationStart, SEEK_SET);

  // Get occupation from the file, which is a max of 30 chars long.
  occupationData = fgets(occupationData, 31, rFile);

  fclose(rFile);

  std::string occupationDataStr = occupationData;

  delete[] occupationData;

  return occupationDataStr;
}

std::string FSeeker::getAge(int profileDataPointer){
  // Calculates the correct position of where the occupation starts in the file.
  int ageStart = profileDataPointer*53+20;
  
  // Age is max of 3 chars long.
  char* ageData = new char[3];

  // Opens fileName file with read argument.
  FILE * rFile;
  rFile = fopen ( fileName , "r" );

  // Go to the position ageStart in the file.
  fseek(rFile, ageStart, SEEK_SET);

  // Get age form the file, which is a max of 3 chars long.
  ageData = fgets(ageData, 4, rFile);

  fclose(rFile);

  std::string ageDataStr = ageData;

  delete[] ageData;

  return ageDataStr;
}
