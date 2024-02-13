#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "student.h"
#include "node.h"

using namespace std;

/*
 * Name | Sophia You
 * Date | 02/08/2024
 * Description | Hash Table. Students are either randomly generated or added
 * manually and stored in a hash table. The user has the option to print,
 * delete, etc. as well.
 * 
 * Sources
 * https://www.softwaretestinghelp.com/random-number-generator-cpp/ 
 */

// function prototypes
int hashFunction(int ID, int tableSize);
void insert(Node** &table, Student* student, int tableSize);
void remove(int id, Node* prevNode, Node* currentNode, Node* &startNode);
void printByIndex(Node** table, int tableSize);
void printByNode(Node* nextNode, Node* startNode);
void rehash(Node** table, int tableSize);
void generateStudents(int &ID, vector<Student*> randomStudents, int numStudents);

int main()
{
   // create a dynamic array of linked lists
   int tableSize = 101;
   Node** table = new Node*[tableSize]; // an array of node pointers

   
   // walk through the node table, set all the values to null
   for (int i = 0; i < tableSize - 1; i++)
     {
       table[i] = NULL;
     }
  
   bool editing = true; // while editing is true, the program runs

   // see random student generator function - this makes sure generated students don't repeat IDs
   int idCheck = 1;
   
   while (editing)
     {
       int max = 20;
       char input[max];
       
       // prompts user for command type
       cout << "LOWER CASE LETTERS ONLY!!!" << endl;
       cout << "Type 'add' to add a student." << endl;
       cout << "Type 'delete' to delete a student." << endl;
       cout << "Type 'print' to print the student roster." << endl;
       cout << "Type 'quit' to exit editing mode." << endl;
       cin.getline(input, max);
       int length = strlen(input);
       input[length + 1] = '\0';

       // ADD A STUDENT
       if (strcmp(input, "add") == 0)
 	{
 	  cout << "To enter a student manually, type 'manual.' To generate a random student, type 'random.'" << endl;
 	  cin.getline(input, max);
 	  if (strcmp(input, "manual") == 0)
 	    {
 	      int max = 50;
 	      char input[max];
 	      char* first = new char[25];
 	      char* last = new char[50];
 	      int id = 0;
 	      float gpa = 0.0;

 	      // prompt for student information
 	      cout << "Enter student information: " << endl;
 	      cout << "First name: " << endl;
 	      cin.getline(input, max);
 	      strcpy(first, input);
 	      cout << "Last name: " << endl;
	      cin.getline(input, max);
 	      strcpy(last, input);

	      cout << "Student ID: " << endl;
	      cin >> id;
	      cin.ignore(max, '\n');

	      // we have to make sure the ID is unique
	      while (id < idCheck)
		{
		  cout << "ID already exits! Try again. " << endl;
		  cin >> id;
		  cin.ignore(max, '\n');
		}

 	      cout << "Student GPA:" << endl;
 	      cin >> gpa;
 	      cin.ignore(max, '\n');

 	      // new student
 	      Student* student = new Student(first, last, id, gpa);

 	      // insert the student into the hash table
	      insert(table, student, tableSize);
	      
 	    }
 	  else if (strcmp(input, "random") == 0)
 	    {
 	      int numStudents = 0;
	      
 	      // use random student generator
 	      cout << "How many students would you like to generate?" << endl;
 	      cin >> numStudents; // store this number
 	      cin.ignore(80, '\n');

 	      // local array stores students
 	      vector<Student*> randomStudents;
	      
 	      // walk through each array slot, create a new student
 	      // call on the random student generator
 	      for (int i = 0; i < numStudents; i++)
 		{
 		  Student* student = new Student();
 		  randomStudents.push_back(student);
 		}

	      cout << numStudents << " students added. Enter 'print' to view updated roster." << endl;
	      cout << "" << endl;

	      // create and store the students
 	      generateStudents(idCheck, randomStudents, numStudents);
	      for (vector<Student*>:: iterator it = randomStudents.begin(); it != randomStudents.end(); it++)
		{
		  insert(table, (*it), tableSize);
		}
 	    }
 	  else
 	    {
 	      cout << "command not found" << endl;
 	    }
 	}

       // REMOVE A STUDENT
       else if (strcmp(input, "delete") == 0)
 	{
 	  int id = 0;
 	  cout << "enter the ID of the student you want to delete." << endl;
 	  cin >> id;
 	  cin.ignore(25, '\n');
	  int searchKey = hashFunction(id, tableSize);
	  for (int i = 0; i < tableSize; i++)
	    {
	      if (i == searchKey)
		{
		  remove(id, table[i], table[i], table[i]);
		}
	    }
	  // remove function
 	  cout << "Student removed. " << endl;
 	  cout << "" << endl;
 	}

       // PRINT STUDENT ROSTER
       else if (strcmp(input, "print") == 0)
 	{
	  cout << "" << endl;
	  
 	  // prints student roster
	  printByIndex(table, tableSize);

 	}

       // EXIT PROGRAM
       else if (strcmp(input, "quit") == 0)
 	{
 	  editing = false;
 	}
       else
 	{
 	  cout << "Command not recognized." << endl;
 	  cout << "Check your spelling and capitalization and try again." << endl;
 	}
     }
 }

 /*
  * This function takes in the student ID, determines the location where 
  * the item should be inserted 
  */
 int hashFunction(int ID, int tableSize)
 {
   // use modulo arithmetic to get the index
   return ID % tableSize; // return the index/key
 }

 /*
  * This function inserts a student into the table according to its key.
  */
void insert(Node** &table, Student* student, int tableSize)
 {
   // hash the student ID to get a key
   int searchKey = hashFunction(student->getID(), tableSize);
   
   // run through the array of linked lists
   for (int i = 0; i < tableSize; i++)
     {
       // if the index of the array matches the search key
       if (searchKey == i)
	 {
	   // no collision detected
	   if (table[i] == NULL)
	     {
	       //cout << "empty slot" << endl;
	       Node* head = new Node(student);
	       table[i] = head;
	     }
	   // collision detected
	   else if (table[i] != NULL)
	     {
	       //cout << "collision detected" << endl;
	       
	       // run through the linked list until you find a null node
	       Node* current = table[i];
	       
	       // counts the number of nodes in the list
	       // since a collision has been detected, there must be at least 2
	       int numCollisions = 2;
	       
	       while (current->getNext() != NULL)
		 {
		   current = current->getNext();
		   numCollisions++;
		 }

	       cout << "collisions: " << numCollisions << endl;

	       Node* node = new Node(student);
	       current->setNext(node);

	       // you have to rehash
	       if (numCollisions >= 4)
		 {
		   cout << "rehash required" << endl;
		   //Node** newtable = new Node*[tableSize * 2 + 1];
		   // the new table should be more than 2x the number of slots
		   rehash(table, tableSize);
		 }
	     }
	 }
     }
 }

 /*
  * This function removes a node in the table according to its key.
  */
void remove(int id, Node* prevNode, Node* currentNode, Node* &startNode)
 {
     // the student has been found
  if (currentNode != NULL && currentNode->getStudent()->getID() == id)
    {
      if (currentNode == startNode) // if the id is the first in the list
	{
	  startNode = currentNode->getNext(); // set the head to the next node
	}
      else if (currentNode->getNext() != NULL) // the node is in the middle
	{
	  // previous node now connects to the node after currentNode
	  prevNode->setNext(currentNode->getNext());
	}
      else if (currentNode->getNext() == NULL) // end of list
	{
	  prevNode->setNext(NULL);
	}
      
      delete currentNode;
    }
  else
    {
      if (currentNode->getNext() != NULL)
	{
	  remove(id, currentNode, currentNode->getNext(), startNode);
	}
      else // id not found
	{
	  cout << "ID not found." << endl;
	  cout << "" << endl;
	}
    }
 }

 /*
  * This function walks through the table and calls on printByNode for each
  * index
  */
void printByIndex(Node** table, int tableSize)
 {
   // walk through the entire table by index
   for (int i = 0; i < tableSize; i++)
     {
       // print the linked list in each slot thru recursion
       printByNode(table[i], table[i]);
     }

 }

 /*
  * This function prints out the linked list inside one slot of the table
  */
 void printByNode(Node* nextNode, Node* startNode)
 {
   // prints out the linked list recursively
   // credit from my own linked lists project

  if (nextNode != NULL)
    {
      Student* student = nextNode->getStudent();
      cout.precision(3);
      cout.setf(ios::showpoint);
      
      // print out the student info held inside the current node
      cout << student->getFirst() << " " << student->getLast() << ", ID " << student->getID() << ", GPA " << student->getGPA() << endl;
      cout << "" << endl;
      
      // call the printNode function (recursively) on the next node in the list
      printByNode(nextNode->getNext(), startNode);
    }

 }

 /*
  * This function doubles the number of slots in the table and puts all the data
  * in this new, larger table to avoid collisions
  */

 void rehash(Node** table, int tableSize)
 {
   cout << "entered rehash function. table size " << tableSize << endl;

   // create a new table with at least double the slots
   Node** newtable = new Node*[tableSize * 2 + 1];
   
   // walk through the entire old table
   for (int i = 0; i < tableSize - 1; i++)
     {
       Node* current = table[i];
       while (current != NULL)
	 {
	   // create a new search key
	   int searchKey = hashFunction(current->getStudent()->getID(), (tableSize * 2 + 1));
	   insert(newtable, current->getStudent(), (tableSize *2 + 1));
	   //current->reset(); // set student = new student, next = null
	   delete current;
	   
	   current = current->getNext();
	 }
     }
   // create keys by hashing all the ids from the old table
   // set values inside the old table to equal NULL
   // delete everything in the old table
   // set old table equal to the new table
 }

 /*
  * generates random student names, IDs, and GPAs
  */
void generateStudents(int &ID, vector<Student*> randomStudents, int numStudents)
 {
   srand((unsigned) time(NULL));
   float randomGPA = 0.0;
   int randomNames = 0;
   //int ID = 1;

   // FIRST NAMES
      // create a vector of first names
      vector<char*> firstNames;
      char* first = new char[25];

      // CREDIT TO MR. GALBRAITH
      ifstream inFile;
      inFile.open("first_names.txt");
      char* input = new char[20];
      while (inFile >> input)
	{
	  char* temp = new char[20];
	  strcpy(temp, input);
	  firstNames.push_back(temp);
	}

      int numFirstNames = 0; // keeps track of the number of first names in the file
      for (vector<char*>:: iterator it = firstNames.begin(); it != firstNames.end(); it++)
	{
	  numFirstNames++;
	}
      
      inFile.close();

      // LAST NAMES
      vector<char*> lastNames;
      char* last = new char[50];
      int numLastNames = 0;
      
      inFile.open("last_names.txt");
      char* input2 = new char[50];
      while (inFile >> input2)
	{
	  char* temp = new char[50];
	  strcpy(temp, input2);
	  lastNames.push_back(temp);
	}

      for (vector<char*>:: iterator it = lastNames.begin(); it != lastNames.end(); it++)
	{
	  numLastNames++;
	}

      inFile.close();
   
   for (vector<Student*>:: iterator it = randomStudents.begin(); it != randomStudents.end(); it++)
     {
       // student first name
       randomNames = (rand() % numFirstNames);
       (*it)->setFirst(firstNames[randomNames]);

       // last names
       randomNames = (rand() % numLastNames);
       (*it)->setLast(lastNames[randomNames]);
       
       // generate random GPA
      randomGPA = 1.0 + (float(rand() % 400)/100);
      cout.precision(3);
      cout.setf(ios::showpoint);
      (*it)->setGPA(randomGPA);

      // assign ID number - must be unique
      (*it)->setID(ID);
      ID++;

     }   
}
