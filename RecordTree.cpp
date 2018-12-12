// RecordTree.cpp
// Ben Howe
// COSC 2030
// Project 2
// 12/11/2018

// Minimal overhead vector representation of binary tree to store records.

#include "RecordTree.h"
#include "Record.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::string;

RecordTree::RecordTree()
{
  //Creating a recordtree
  //cout << "CONSTRUCTOR: creating record tree..." << endl;
  empty_slot = 0;
}
RecordTree::~RecordTree()
{
  //cout << "DESTRUCTOR: destroying record tree..." << endl;
  //system("pause");
}

int RecordTree::size()
{
  return rec.size();
}

void RecordTree::grow()
{
  int tmp = rec.size();
  Record tempRecord;
  for (int i = 0; i < (tmp + 1); i++)
  {
    rec.push_back(tempRecord);
	if(rec.size()==1)
	{
		//This is the first node in the tree, so set its parent to a random hash.
		rec.at(rec.size() - 1).setParentID("rndmhash");
	}
	else
	{
	//what is the parent id?  
	/*
	This is the parent id of the current element that has just been created
	replace "ABC" with rec.at(parent(rec.size()-1)).getID()
	*/
    string tmp = rec.at(parent(rec.size() - 1)).getID();
	rec.at(rec.size() - 1).setParentID(tmp);
	}
    //cout << rec.size() - 1 << endl;
  }
}
void RecordTree::addRecord(int slot, string & s)
{
// Set the raw event (this also generates a Hash for the ID)
  if (rec.at(slot).setRawEvent(s)==0)
  {
    //0=successful, 1= unsuccessful
    //We only want to do anything if adding the record was successful
    empty_slot++;
    updateParent(slot);
    // calculate bighash = (id+parentid+rawevent+lhash+rhash)
    // Need to distinguish if current node is left or right child of parent
    // if left, send bighash to parent node to set LHASH and append LHIST
    // if right, send bighash to parent node to set RHASH and append RHIST

    //hash(rec.at(slot).getParent,rec.at(slot).getRawEvent());

 //  now that the empty slot has been filled, move the reference to the next empty slot.



    cout << "Value recorded." << endl;

  }
  else
  {
    cout << "No Value was recorded." << endl;
  }
  

}
int RecordTree::findRecordID(string HashID)  //Returns -1 if no node is found.
{
  string tmp = "";
  int id = -1;
  bool found = false;
    while (tmp != HashID)
    {
      id++;
      if (id >= rec.size())
      {
        break;
      }
      tmp = rec.at(id).getID();
      if (tmp == HashID)
      {
        found = true;
      }

    }
  //returns the vector ID given the 8 digit hash ID
    if (found == true)
    {
      return id;
    }
    else
    {
      return -1;
    }
}
void RecordTree::print()
{
  for (int i = 0; i < size(); i++)
  {
      rec.at(i).print(i);
  }
}

int RecordTree::parent(int child) // Returns the vector id of a node's parent.
{
  if (child == 0)
  {
    return -1; //Root node
  }

  return (child - 1) / 2;
}

bool RecordTree::isleft(int child) //True -> left node, False -> right node
{
  if (child % 2 == 0)
  {
    //even is right
    return false;
  }
  else
  {
    //odd is left
    return true;
  }
}
int RecordTree::right(int ID) // returns right child vector id
{
  int tmp = (ID * 2) + 2;
  if (tmp >= empty_slot)
  {// right child not populated
    return -1;
  }
  else
  {
    return tmp;
  }
}
int RecordTree::left(int ID) // returns left child vector id
{
  int tmp = (ID * 2) + 1;
  if (tmp >= empty_slot)
  {// left child not populated
    return -1;
  }
  else
  {
    return tmp;
  }
}

void RecordTree::updateParent(int childID)
{
  if (childID != 0) // a childID of zero is the root node and has no parent to update
  {
    //Correct Hash
    string bighash = rec.at(childID).hash(rec.at(childID).getID() + rec.at(childID).getParent() + rec.at(childID).getRawEvent() + rec.at(childID).getLHASH() + rec.at(childID).getRHASH());
    //Debug Hash
    //string bighash = std::to_string(childID);

    if (isleft(childID) == true)
    {//left node, update parent's left info
      //the parent to update: parent(childID)
      rec.at(parent(childID)).setLHASH(bighash);
    }
    else
    {//right node, update parent's right info
      //the parent to update : parent(childID)
      rec.at(parent(childID)).setRHASH(bighash);
    }
    
    // recursive call to parent node so it can update its parent.
    // percolate!
    updateParent(parent(childID));
  }
}


// Display the tree.
/*
I really didn't like the display offered by the Lab 8 code. I felt like it was
backwards, so I modified the code to be more intuitive.

The tree is laid on its side. (Rotated 90 degrees counterclock-wise)
Left is down, and right is up.

For example, the tree
      A
    /   \
  B       C

would display as
      C
    /
  A
    \
      B
*/

// Node values are indented by the depth of the node to display
//   the shape of the tree.
void RecordTree::display(std::ostream& outfile, int startid)
{
  std::string prefix;
  //if (tree_ == NULL)
  if(rec.size()==0)
  {
    outfile << "-" << std::endl;
  }
  else
  {
    displayRight(outfile, right(startid), "           ");
    outfile << "---" << rec.at(startid).getID() << std::endl;
    displayLeft(outfile, left(startid), "           ");

  }
}

// Display the nodes connected to subtree.
// This is a left subtree.

void RecordTree::displayLeft(std::ostream & outfile, int startid, std::string prefix)
{
  if (startid == -1)
  {
    outfile << prefix + "\\" << std::endl;
  }
  else
  {
    displayRight(outfile, right(startid), prefix + "|           ");
    outfile << prefix + "\\---" << rec.at(startid).getID() << std::endl;
    displayLeft(outfile, left(startid), prefix + "            ");
  }
}


// Display the nodes connected to subtree.
// This is a right subtree.

void RecordTree::displayRight(std::ostream & outfile, int startid, std::string prefix)
{
  if (startid == -1)
  {
    outfile << prefix + "/" << std::endl;
  }
  else
  {
    displayRight(outfile, right(startid), prefix + "            ");
    outfile << prefix + "/---" << rec.at(startid).getID() << std::endl;
    displayLeft(outfile, left(startid), prefix + "|           ");
  }
}
