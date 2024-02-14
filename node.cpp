#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

// default constructor
Node::Node()
{
  stu = new Student();
  next = NULL;
}

// regular constructor
Node::Node(Student* currentStudent){
    stu = currentStudent;
    next = NULL;

}

// destructor
Node::~Node(){
    delete stu;
    next = NULL;

}


// returns the student held in the current node.
Student* Node::getStudent(){
    return stu;
}

// sets the next node
void Node::setNext(Node* nextNode){
    next = nextNode;

}

// returns the next node in the chain.
Node* Node::getNext(){
    return next;
}

// sets the value of the student in the node.
void Node::setStudent(Student* newstudent)
{
  stu = newstudent;
}
