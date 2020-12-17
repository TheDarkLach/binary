#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "node.h"

using namespace std;

struct Trunk {
  Trunk *prev;
  char* str;

  Trunk(Trunk *prev, char* str) {
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

   else if (method == 2) {//getting input from file, store in char array
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
    if (method == 1) {
      cout << "Please enter a num: ";
      cin >> value;
      cin.clear();
      cin.ignore(1000000, '\n');
      cout << endl;
      addNode(value, head);
    }
    else if (method == 2) {
      cout << "Please enter a num: ";
      cin >> value;
      cin.ignore(100000, '\n');
      cout << endl;
      Node* temp = search(value, head);
      if (temp != NULL) {
	cout << endl << value << " has been deleted from EXISTENCE." << endl << endl;
	remove(value, head);
      }
      else
	cout << endl << value << " is not in the tree." << endl << endl;
      temp = NULL;
      delete temp;
    }
    else if (method == 3) {
      cout << "Please enter a num: ";
      cin >> value;
      cin.ignore(1000000, '\n');
      cout << endl;
      Node* temp = search(value, head);
      if (temp != NULL)
	cout << endl << value << " is in the tree." << endl << endl;
      else
	cout << endl << value << " is not in the tree." << endl << endl;
      temp = NULL;
      delete temp;
    }
    else if (method == 4) {
      break;
    }
    else {
      cout << endl << "Invalid Input." << endl;
      break;
    }
    
    if (head != NULL)
      printTree(head, NULL, false);
  }
  
  return 0;
}
