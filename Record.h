// Record.h
// Ben Howe
// COSC 2030
// Project 2

// The data structure for the data we're storing.

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Record
{
public:
  Record();
  ~Record();
  int setRawEvent(string s); //returns 0 for successful, 1 for unsuccessful
  void setParentID(string s);
  string getParent();
  string getID();
  string getRawEvent();
  string getLHASH();
  string getRHASH();
  void setLHASH(string s);
  void setRHASH(string s);
  void print(int nodeid);
  string hash(const string s);

private:
  string ID;
  string ParentID;
  string RawEvent;
  string RHash;
  string LHash;
  vector<string> RHist;
  vector<string> LHist;
  
};

# endif