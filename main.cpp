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
    cout << endl << "Input numbers with spaces in between them: " << endl <<;
    cin.get(input, 1000);
    cin.clear();
    cin.ignore(1000000, '\n');
    //cout << input << endl;
  }
}
