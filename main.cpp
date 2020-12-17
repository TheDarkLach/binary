//Binary search tree by Faizan Karim
//You know, last time i told myself i'd do my work on time but
//that didn't really happen
//changed the way i print out so this time the left/right children wont die
//reading numbers in again isn't working and don't think its my data


#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#include "node.h"

using namespace std;

struct Trunk
{
  Trunk *prev;
  char* str;

  Trunk(Trunk *prev, char* str)
  {
    this -> prev = prev;
    this -> str = str;
  }
};

void parseInput(char input[]);
void addNode(int value, Node* current);
void printTree(Node* root, Trunk *prev, bool isLeft);
void showTrunks(Trunk *p);
Node* search(int value, Node* current);
void remove(int value, Node* current);
void shiftUp(Node* current, bool LR);
Node* findLeast(Node* current, bool LR);

//i know this is illegal, but desperate times call for desperate measures
Node* head = NULL;

int main()
{
  int method;
  char fileName[20];
  char input[1000];
  int* parsed;
  int value;
  cout << endl << "How would you like to input your numbers? (1 for console, 2 for file)" << endl;
  cin >> method;
  cin.clear();
  cin.ignore(1000000, '\n');
  
  if (method == 1)
  {
    //getting input from console, store in char array
    cout << endl << "Input numbers with spaces in between them" << endl;
    cin.get(input, 1000);
    cin.clear();
    cin.ignore(1000000, '\n');
    //cout << input << endl;
  }

   else if (method == 2) 
   {
    //getting input from file, store in char array
    cout << endl << "What is the name of the file?" << endl;
    cin.get(fileName, 20);
    cin.clear();
    cin.ignore(1000000, '\n');
    streampos size;
    ifstream file(fileName, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
      //same file reading method from shunting yard
      size = file.tellg();
      file.seekg(0, ios::beg);
      file.read(input, size);
      file.close();
    }
  }
  else
  {
    cout << "Invalid Input.";
    return 0;
  }
  parseInput(input);
  cout << endl;

  printTree(head, NULL, false);
  while (true)
  {
    method = NULL;
    value = NULL;
    cout << endl << "What would you like to do?";
    cout << endl << "(1 for add, 2 for delete, 3 to search, 4 to quit)" << endl;
    cin >> method;
    cin.clear();
    cin.ignore(1000000, '\n');
    if (method == 1) 
    {
      cout << "Please enter a num: ";
      cin >> value;
      cin.clear();
      cin.ignore(1000000, '\n');
      cout << endl;
      addNode(value, head);
    }
    else if (method == 2) 
    {
      cout << "Please enter a num: ";
      cin >> value;
      cin.ignore(100000, '\n');
      cout << endl;
      Node* temp = search(value, head);
      if (temp != NULL) 
      {
	cout << endl << value << " has been deleted from EXISTENCE." << endl << endl;
	remove(value, head);
      }
      else
      {
	cout << endl << value << " is not in the tree." << endl << endl;
      }
      temp = NULL;
      delete temp;
    }
    else if (method == 3) 
    {
      cout << "Please enter a num: ";
      cin >> value;
      cin.ignore(1000000, '\n');
      cout << endl;
      Node* temp = search(value, head);
      if (temp != NULL)
      {
	cout << endl << value << " is in the tree." << endl << endl;
      }
      else
      {
	cout << endl << value << " is not in the tree." << endl << endl;
      }
      temp = NULL;
      delete temp;
    }
    else if (method == 4) 
    {
      break;
    }
    else 
    {
      cout << endl << "Invalid Input." << endl;
      break;
    }
    
    if (head != NULL)
    {
      printTree(head, NULL, false);
    }
  }
  
  return 0;
}

//had something similar on shunting
void parseInput(char input[]) 
{
  //remove spaces between the chars, make int pointer (array) 
  int counter;
  int* parsed;
  int pointers[2];
  int value;
  int* temp;
  counter = 1;
  pointers[0] = -1;
  for (int i = 0; i < strlen(input); i++) 
  {
    if (input[i] == ' ') 
    {
      pointers[1] = i;
      int j = 0;
      char* newArray = new char[pointers[1] - pointers[0]];
      for (int i = pointers[0] + 1; i < pointers[1]; i++) 
      {
	newArray[j] = input[i];
	//cout << newArray[i] << endl;
	j = j + 1;
      }
      newArray[j] = '\0';
      temp = parsed;
      parsed = new int[counter];
      if (counter > 1) 
      {
	for (int i = 0; i < counter - 1; i++) 
	{
	  parsed[i] = temp[i];
	  //cout << parsed[i] << endl;
	}
      }
      parsed[counter - 1] = atoi(newArray);
      counter = counter + 1;
      pointers[0] = pointers[1];
    }
  }
  char* newArray = new char[strlen(input) - pointers[0]];
  int j = 0;
  for (int i = pointers[0] + 1; i < strlen(input); i++) 
  {
    newArray[j] = input[i];
    //cout << newArray[j];
    j = j + 1;
  }
  newArray[j] = '\0';
  temp = parsed;
  parsed = new int[counter];
  if (counter > 1) {
    for (int i = 0; i < counter - 1; i++) 
    {
      parsed[i] = temp[i];
      //cout << parsed[i] << endl;
    }
  }
  parsed[counter - 1] = atoi(newArray);
  /*for (int i = 0; i < counter; i++)
    {
       cout << endl << parsed[i] << endl;
    }*/
  for (int i = 0; i < counter; i++) 
  {
    //add all input to the tree
    //cout << ":)" << endl;
    addNode(parsed[i], head);
  }
}

void addNode(int value, Node* current) 
{
  //method for adding nodes
  if (head == NULL) 
  {
    //if the tree doesn't exist
    head = new Node();
    head-> setValue(value);
  }
  else 
  {//if it does exist
    if (value > current -> getValue()) 
    {
      if (current -> getRight() == NULL) 
      {
	current -> setRight(new Node());
	current -> getRight() -> setParent(current);
	current -> getRight() -> setValue(value);
      }
      else
      {
	//if not null, recursively call next right
	addNode(value, current -> getRight());
      }
    }
      
    else if (value < current -> getValue())
    {
      //if the value is less than the current node
      if (current -> getLeft() == NULL)
      {
	//if the node doesn't have a left child
	current -> setLeft(new Node());
	current-> getLeft() -> setParent(current);
	current -> getLeft() -> setValue(value);
      }
      else
      {
	//if not null, recursively call next left
	addNode(value, current -> getLeft());
      }

    }
    else
    {
      //if the value is a duplicate
      cout << "You cannot have duplicate values." << endl;
    }
  }
}

//https://www.techiedelight.com/c-program-print-binary-tree/
//i think i couldve put this with the prototypes but idk if it matters
void showTrunks(Trunk *p)
{
  //helper method for printing
  if (p == NULL)
  {
    return;
  }
  showTrunks(p -> prev);

  cout << p -> str;
}

void printTree(Node* root, Trunk *prev, bool isLeft) 
{
  /* start out with the leftmost node and then print until the right most
   * Visual tree printing from //www.techiedelight.com/c-program-print-binary-tree/
   */
  if (root == NULL) //don't print if the tree is nonexistant
    return;

  char* prev_str = (char*)("    ");
  Trunk *trunk = new Trunk(prev, prev_str);
  printTree(root -> getLeft(), trunk, true);
  if (!prev)
    trunk -> str = (char*)("---");
  else if (isLeft) {
    trunk -> str = (char*)(".---");
    prev_str = (char*)("   |");
  }
  else {
    trunk -> str = (char*)("`---");
    prev -> str = prev_str;
  }
  showTrunks(trunk);
  cout << root -> getValue() << endl;

  if (prev)
    prev -> str = prev_str;
  trunk -> str = (char*)("   |");
  printTree(root -> getRight(), trunk, false);
}

void remove(int value, Node* current) 
{
  //if the tree only has a head
  if (current -> getParent() == NULL && current -> getLeft() == NULL && current -> getRight() == NULL) 
  {
    head = NULL;
    return;
  }
  
  Node* temp = search(value, current);  
  
  if (temp -> getLeft() == NULL && temp -> getRight() == NULL) {//if there are no childtren
    if (temp -> getParent() -> getLeft() == temp) {
      temp -> getParent() -> setLeft(NULL);
      temp -> ~Node();
      return;
    }
    else if (temp -> getParent() -> getRight() == temp) {
      temp -> getParent() -> setRight(NULL);
      temp -> ~Node();
      return;
    }
  }
  else {
    if (temp -> getLeft() == NULL) {//if there is only a right child
      if (temp -> getParent() -> getLeft() == temp) {
	temp -> getParent() -> setLeft(temp -> getRight());
	temp -> ~Node();
	return;
      }
      else if (temp -> getParent() -> getRight() == temp) {
	temp -> getParent() -> setRight(temp -> getRight());
	temp -> ~Node();
	return;
      }
    }
    else if (temp -> getRight() == NULL) {//if there is only aleft child
      if (temp -> getParent() -> getLeft() == temp) {
	temp -> getParent() -> setLeft(temp -> getLeft());
	temp -> ~Node();
	return;
      }
      else if (temp -> getParent() -> getRight() == temp) {
	temp -> getParent() -> setRight(temp -> getLeft());
	temp -> ~Node();
	return;
      }
    }
    else {//if there are two children
      //need to still move the rest of the subtree (finished)
      //cout << "two children" << endl << endl;
      if (temp -> getRight() -> getLeft() != NULL) {//min in right subtree
	Node* temp2 = findLeast(temp -> getRight(), true);
	temp -> setValue(temp2 -> getValue());
	shiftUp(temp2, true);
	//temp2 -> getParent() -> setLeft(NULL);
	temp2 -> ~Node();
      }
      else if (temp -> getLeft() -> getRight() != NULL) {//max in left subtree
	Node* temp2 = findLeast(temp -> getLeft(), false);
	temp -> setValue(temp2 -> getValue());
	shiftUp(temp2, false);
	//temp2 -> getParent() -> setLeft(NULL);
	temp2 -> ~Node();
      }
      else {//if none of the subtrees have children
	temp -> setValue(temp -> getRight() -> getValue());
	temp -> getRight() -> ~Node();
	temp -> setRight(NULL);
      }
      return;
    }
  }
}

void shiftUp(Node* current, bool LR) {//true is shift left, false is shift right 
  if (LR) {
    current -> getParent() -> setLeft(current -> getRight());
  }
  else {
    current -> getParent() -> setRight(current -> getLeft());
  }
  return;
}

 Node* findLeast(Node* current, bool LR) {//true for left min, false for right max
   if (LR) {
     while (current -> getLeft() != NULL)
       current = current -> getLeft();
   }
   else {
     while (current -> getRight() != NULL)
       current = current -> getRight();
   }
   return current;
 }

Node* search(int value, Node* current) {//searching for a node with a certain value
  if (value == current -> getValue())
    return current;

  else if (value > current -> getValue()) {
    if (current -> getRight() == NULL)
      return NULL;
    else
      search(value, current -> getRight());
  }
  
  else if (value < current -> getValue()) {
    if (current -> getLeft() == NULL)
      return NULL;
    else
      search(value, current -> getLeft());
  }

  else {
    return NULL;
  }
}
