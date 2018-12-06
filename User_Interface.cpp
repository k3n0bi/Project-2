// User_Interface.cpp
// Ben Howe
// COSC 2030
// 11/23/2018

// The main program for the vector based binary tree record project.
// Handles user interaction.


#include <iostream>
#include <string>
#include <vector>
#include "RecordTree.h"
#include "Record.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


void printSplash(); // displays fancy title.
void printHelp(); //display help/options menu
void forcecase(string & input); //used to force lowercase on user input IDs
int main()
{
  // Create a Record Tree
  RecordTree myTree;


  bool exitProgram = false;

  printSplash();

  while (exitProgram == false)
  {
    if (myTree.size() == myTree.empty_slot) { myTree.grow(); }
    std::string s; // String input by user.

    cout << "Enter an option, or enter an 8 digit ID to view. (Enter ? for options)" << endl;
    
    getline(cin, s);
    
    if (s.length() == 8)
    {
      //cout <<"is it an ID?" << endl;
      {
        forcecase(s); //force to lowercase
          int i;
          i = myTree.findRecordID(s);
          if (i != -1)
          {
            myTree.rec.at(i).print(i);
          }
          else
          {
            cout << "id not found." << endl;
          }
        
      }
    }
    else
    {


      if (s == "?" || s == "Help")
      {
        // Display help menu
        printHelp();
      }

      if (s == "A" || s == "a")
      {
        // add
        cout << "Add a record..." << endl;
        {
          cout << "Enter record value (press enter to commit the value):" << endl;
          string in;
          getline(cin, in);
          myTree.addRecord(myTree.empty_slot,in);
        }
      }

      if (s == "E" || s == "e")
      {
        // edit
        cout << "Edit a record..." << endl;
      }

      if (s == "V" || s == "v")
      {
        // View
        cout << "Enter the record id: ";
        
        {
          string tempid;
          cin >> tempid;
          forcecase(tempid); //force to lowercase
          {
            int i;
            i = myTree.findRecordID(tempid);
            if (i != -1)
            {
              myTree.rec.at(i).print(i);
            }
            else
            {
              cout << "ID not found." << endl;
            }
          }
        }

        //myTree.print();
        
      }
      
      if (s == "T" || s == "t")
      {
        // add
        cout << "View the tree..." << endl;
        //myTree.print();
        myTree.display(cout,0);
      }

      if (s == "Quit" || s == "Q" || s == "q")
      {
        // Quit
        exitProgram = true;
      }

    }
  }
  return 0;
}


void printSplash()
{
  // Fancy!
  cout << "============================" << endl;
  cout << "    COSC 2030 Project 2" << endl;
  printHelp();


}


void printHelp()
{
  // Omitted the ? option since it's shown with every prompt to enter data.
  cout << "============================" << endl;
  cout << "A to add a record" << endl;
  cout << "E to edit a record" << endl;
  cout << "V to view a record" << endl;
  cout << "T to view the tree" << endl;
  cout << "Q to quit" << endl;
  cout << "============================" << endl;

}


  
void forcecase(string & input) //used to force lowercase on user input IDs
{
  for (int i = 0; i < input.length(); i++)
  {
    //A is ASCII 65
    //Z is ASCII 90
    if (input.at(i) >= 65 && input.at(i) <= 90)
    {
      //Uppercase letter detected, shift to lowercase letter
      input.at(i) = input.at(i) + 32;
    }
  }
}