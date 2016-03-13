# Social_Network
Social network application, final project for CS130A

Project Title: Data Structures for Solving Analytical Queries on Social Networks
Project Number:	3 (Final)
Author: Tristan Starck
Author: Kelly Bielaski
Date Submitted: 3/13/16

Project Description:
	Builds a Social Network of people by either taking in a person's name, age, and occupation by commandline
	or through reading their information and friends using a text file. A Friendship Graph is built on memory
	using a Hashtable which stores a person's name, pointer to their profile data online, and a linked list of
	names of the person's friends (which should already be in the Hashtable). We implemented a BTree in order
	to be able to efficiently look at ranges of people by name in our Social Network. The BTree is stored in memory
	but the leaves contain pointers to a person's profile data which is stored on disc in a text file.

Project Files:
	main.cpp (Reads in files and handles commandline inputs)
	BTree.h (BTree class)
	BTree.cpp (BTree class)
	Hashtable.h (Hashtable class for Friendship Graph)
	Hashtable.cpp (Hashtable class for Friendship Graph)
	HashNode.h (Nodes that are stored in Hashtable)
	FSeeker.h (Class used to insert people onto the disc and read from the disc)
	FSeeker.cpp (Class used to insert people onto the disc and read from the disc)
	FriendNode.h (Linked list class, used to store friends names)
	SN_Tests.cpp (Tests used for FSeeker and Hashtable class)
	BT_Tests.cpp (Tests used for BTree class)
	input.txt (Text file used to initialize Social Network)
	makefile 

Commandline Inputs:
	Type:	insert (Inserts new person into Social Network)
	Type: 	rangeQuery (Prints information of all people ranging alphabetically from name1 to name2)
	Type:	addFriendship (Adds a friendship between two people)
	Type:	removeFriendship (Removes a friendship between two people)
	Type:	getFriendsProfileData (Prints profile data of the person's friends)
	Type:	printAll (prints entire Social Network: Name, Age, Occupation and list of Friends for each person in the Social Network)
	Type:	printBTree (prints all internalNodes, leaves, and items in the BTree)
	Type:	insertFile (read in another .txt file)
	Type:	exit (exits program)

To Run Program:
	Type:	make run_main

To Run Tests:
	Type:	make run_bt (BTree tests)
	Type:	make run_tests (Hashtable and FSeeker tests)

To remove *.o files:
	Type:	make clean

Other make targets:
	Type:	make main (compiles main)
	Type:	make tests (compiles tests)
	Type:	make btree (compiles btree tests)

TO DO:
	1. Comment/Clean Up main.cpp(K)
	2. Comment FSeeker.cpp(T) -completed
	3. Comment BTree.cpp and BTree.h(T) -completed
	4. Comment Nodes.(K) -completed
	5. Add info into README.md (T) -completed
	6. Change name commandline insert to handle spaces.(T) -completed
	7. Change rangeQuery to print profileData, not just occupation.(K) -completed
	8. read in input file at the commandline -completed
	9. read in names/occupations with spaces main -completed