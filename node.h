#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

class Node {

 public:
 // constructors
  Node();
  Node(Student* currentStudent);
  ~Node();

  // functions
  Node* getNext();
  void setNext(Node* nextNode);
  Student* getStudent();
  void setStudent(Student* newstudent); // resets the student value

 private:
 // creating variables
  Node* next;
  Student* stu;

};
#endif
