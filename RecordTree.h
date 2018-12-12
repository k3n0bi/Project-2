// RecordTree.h
// Ben Howe
// COSC 2030
// Project 2
// 12/11/2018


// Minimal overhead vector representation of binary tree to store records.

#ifndef RECORDTREE_H
#define RECORDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include "Record.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;

class RecordTree
{
public:
  // Constructors
  RecordTree();
  // Destructor
  ~RecordTree();
  vector<Record> rec;
  int size();
  int empty_slot;
  void grow();
  void addRecord(int slot, string & s);
  int findRecordID(string HashID);
  void print();
  int parent(int child);
  bool isleft(int child); //True -> left node, False -> right node
  int right(int ID); // returns right child vector id
  int left(int ID); // returns left child vector id
  void updateParent(int childID);// recursive function that sends hash info to parent

   // Display the tree.
   // The node values are listed using an inorder
   //   traversal.
   // Node values are indented by the depth of the node to
   //   display the shape of the tree.
   // The tree shape is displayed with the left subtree at
   //   the top of the screen.
  void display(std::ostream& outfile, int startID);

   // This subtree is a left subtree.
   // Display the nodes connected to subtree on outfile.
   // Use a line by line display, order nodes from left to
   //   right, draw connecting lines.
   // Preface each line of the display with prefix.
  void displayLeft(std::ostream & outfile, int startid, std::string prefix);

   // This subtree is a right subtree.
   // Display the nodes connected to subtree on outfile.
   // Use a line by line display, order nodes from left to
   //   right, draw connecting lines.
   // Preface each line of the display with prefix.
  void displayRight(std::ostream & outfile, int startid, std::string prefix);





private:
  // Inaccessible standard functions
};

#endif