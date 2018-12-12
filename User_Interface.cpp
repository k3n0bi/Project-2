// User_Interface.cpp
// Ben Howe
// COSC 2030
// 12/11/2018

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
  std::string s; // String input by user.
  while (exitProgram == false)
  {
    if (myTree.size() == myTree.empty_slot) { myTree.grow(); }
    

    cout << "Enter an option, or enter an 8 digit ID to view. (Enter ? for options)" << endl;
    // I had a strange case where the prompt would display twice after the "ID not found" message.
    // Apparently I had some extra stuff in the input stream, so after searching for why getline
    // ran twice in a while loop, I ran across this: https://stackoverflow.com/questions/7884930/why-this-while-loop-executes-twice-before-asking-for-name
       std::cin >> std::ws;   // <--- drop whitespaces
   // It's probably not the best method of clearing out the input stream, but it cleared up my problem. 
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
        //cout << "Add a record..." << endl;
        {
          cout << "Enter record value up to 1024 characters. Empty values will be ignored. (Press enter to commit the value):" << endl;
          string in;
          getline(cin, in);
          myTree.addRecord(myTree.empty_slot,in);
        }
      }
      /* Editing records not necessary
      if (s == "E" || s == "e")
      {
        // edit
        cout << "Edit a record..." << endl;
      }
      */

      if (s == "I" || s == "i")
      {
        // View
        cout << "Enter the 8 character record id: ";
        
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


      }

      if (s == "R" || s == "r")
      {
        myTree.print();
      }


      if (s == "S" || s == "s")
      {
        // subtree print
        cout << "Enter the 8 character record id: ";

        {
          string tempid;
          cin >> tempid;
          forcecase(tempid); //force to lowercase
          {
            int i;
            i = myTree.findRecordID(tempid);
            if (i != -1)
            {
              cout << "____________________________________________________" << endl;
              cout << "== SUBTREE DISPLAY ==" << endl;
              myTree.display(cout, i);
              cout << "____________________________________________________" << endl;

            }
            else
            {
              cout << "ID not found." << endl;
            }
          }
        }


      }


      if (s == "T" || s == "t")
      {
        cout << "____________________________________________________" << endl;
        myTree.display(cout,0);
        cout << "____________________________________________________" << endl;

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
  cout << "========================================================" << endl;
  cout << "                  COSC 2030 Project 2" << endl;
  printHelp();


}


void printHelp()
{
  // Omitted the ? option since it's shown with every prompt to enter data.
  cout << "========================================================" << endl;
  cout << "                  OPTIONS" << endl;
  cout << "========================================================" << endl;

  cout << "A - add a record" << endl;
  //cout << "E - edit a record" << endl;
  cout << "I - view an individual record" << endl;
  cout << "R - view all records (empty records hidden)" << endl;
  cout << "S - view a subtree (treat given node as the root)." << endl;
  cout << "    This is useful if the whole tree is too large to view." << endl;
  cout << "T - view the entire tree" << endl;
  cout << "? - view these options again" << endl;
  cout << "Q - quit" << endl;
  cout << "========================================================" << endl;

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