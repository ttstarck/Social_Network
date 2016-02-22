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

FSeeker::FSeeker(char* fileName){
  this->fileName=fileName;
}

//I am starting by inserting to the end of the file
std::string FSeeker::insert(std::string name, int age, std::string occupation){
  FILE * pFile;
  pFile = fopen ( fileName , "w" );
  const char * addName = name.c_str();
  std::stringstream ss;
  ss << age;
  std::string addAgeString = ss.str();
  char* addAge =(char*) addAgeString.c_str();
  const char * addOccupation = occupation.c_str();

  fseek(pFile, 0, SEEK_END);
  fputs ( addName , pFile );
  // seek 20 bytes from the beginning of the file.
  fseek ( pFile , 20 , SEEK_SET );
  fputs ( addAge , pFile );
  fseek ( pFile , 3- strlen("27") , SEEK_CUR );
  fputs ( addOccupation, pFile);
  fseek ( pFile , 53 , SEEK_SET );
  fclose ( pFile );


  return "inserted";
}

std::string FSeeker::getProfileData(int profileDataPointer){
  std::string profileData="";
  profileData+=getName(profileDataPointer);
  profileData+=getAge(profileDataPointer);
  profileData+=getOccupation(profileDataPointer);
  //how do we want to return it?

  return profileData;
}

std::string FSeeker::getName(int profileDataPointer){
  int nameStart = profileDataPointer*53;
  char* nameData = new char[20];
  FILE * pFile;
  pFile = fopen ( "ProfileData.txt" , "r" );
  fseek(pFile, nameStart, SEEK_SET);
  nameData = fgets(nameData, 20, pFile);

  return nameData;
}

std::string FSeeker::getAge(int profileDataPointer){
  int occupationStart = profileDataPointer*53+20;
  char* occupationData = new char[3];
  FILE * pFile;
  pFile = fopen ( "ProfileData.txt" , "r" );
  fseek(pFile, occupationStart, SEEK_SET);
  occupationData = fgets(occupationData, 3, pFile);

  return occupationData;
}

std::string FSeeker::getOccupation(int profileDataPointer){
  int ageStart = profileDataPointer*53+23;
  char* ageData = new char[30];
  FILE * pFile;
  pFile = fopen ( "ProfileData.txt" , "r" );
  fseek(pFile, ageStart, SEEK_SET);
  ageData = fgets(ageData, 30, pFile);

  return ageData;
}
