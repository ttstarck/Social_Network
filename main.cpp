//
// main.cpp
// Social_Network
//
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

int main(){
	try{
		ifstream file("input.txt");
		string line;
		string name = "";
		string occupation = ""; 
		string age = "";
		/*
			This only allows for one possible friend. Option for multiple friends is to create 
			the linked list of friends here, or create a node class to create the linked list with.
		*/
		string friend1 = "";
		while(getline(file,line)){
			int position = 0;
			for(int i = 0; i < line.length(); i++){
				if(line[i] == '\n')
					break;
				if(line[i] == ',')
					position++;
				else if(position == 0)
					name += line[i];
				else if(position == 1){
					occupation += line[i];
				}
				else if(position == 2){
					age += line[i];
				}
				else{
					friend1 += line[i];
				}

			}
		}
		cout << name << endl << occupation << endl << age << endl << friend1 << endl;
	}
	catch(exception& ex){
		cerr << ex.what() << endl;
	}
}