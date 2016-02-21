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
  fileName=fileName;
}

//I am starting by inserting to the end of the file
std::string FSeeker::insert(std::string name, int age, std::string occupation){
  FILE * pFile;
  pFile = fopen ( "ProfileData.txt" , "w" );
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
  fputs ( "\n" , pFile );
  fclose ( pFile );


  return "inserted";
}

std::string FSeeker::getProfileData(int profileDataPointer){
  //STUB!!!
  return "stub";
}

std::string FSeeker::getName(int profileDataPointer){
  //STUB!!!
  return "stub";
}

std::string FSeeker::getOccupation(int profileDataPointer){
  //STUB!!!
  return "stub";
}

std::string FSeeker::getAge(int profileDataPointer){
  //STUB!!!
  return "stub";
}
