// Record.cpp
// Ben Howe
// COSC 2030
// Project 2

// The data structure for the data we're storing.

#include "Record.h"
#include <iostream>
using std::cout;
using std::endl;

Record::Record() :ID(""), ParentID(""), RawEvent(""), RHash(""), LHash("")
{
  //cout << "CONSTRUCTOR: creating new record..." << endl;
}
Record::~Record()
{
  //cout << "DESTRUCTOR: destroying record..." << endl;
}
int Record::setRawEvent(string s)
{
  if (s.length() != 0) //Only record an event if there's something there!
  {
    if (s.length() <= 1024)
    {
      RawEvent = s;
    }
    else
    {//limit the event to 1024 characters
      string tmp = "";
      for (short i = 0; i < 1024; i++)
      {
        tmp.push_back(s.at(i));
      }
      RawEvent = tmp;
    }
  //set the ID
  ID = hash(ParentID + RawEvent);
  return 0;
  }
  else
  {
    return 1;
  }
}
void Record::setParentID(string s)
{
  ParentID = s;
}

string Record::getParent()
{
  return ParentID;
}

string Record::getID()
{
  return ID;
}

string Record::getRawEvent()
{
  return RawEvent;
}

string Record::getLHASH()
{
  return LHash;
}

string Record::getRHASH()
{
  return RHash;
}

void Record::setLHASH(string s)
{
  //update hash, and append to history
  LHash = s;
  LHist.push_back(s);
}

void Record::setRHASH(string s)
{
  //update hash, and append to history
  RHash = s;
  RHist.push_back(s);
}

void Record::print(int nodeid)
{
  if (RawEvent != "") //change string to something other than "" to print empty nodes for debug
  {
    cout << "====================" << endl;
    cout << "      NODE " << nodeid << endl;
    cout << "====================" << endl;
    cout << "      ID: " << ID << endl;
    cout << "ParentID: " << ParentID << endl;
    cout << "RawEvent: " << RawEvent << endl;
    cout << "   RHash: " << RHash << endl;
    cout << "   LHash: " << LHash << endl;
    cout << "   RHist: [";
    for (int i = 0; i < RHist.size(); i++)
    {
      if (i > 0) { cout << " ,"; }
      cout << RHist.at(i);
    }
    cout << "]" << endl;
    cout << "   LHist: [";
    for (int i = 0; i < LHist.size(); i++)
    {
      if (i > 0) { cout << " ,"; }
      cout << LHist.at(i);
    }
    cout << "]" << endl;
    cout << "--------------------" << endl;
  }
}

string Record::hash(const string s)
{
  {
    long sums = 0;
      
    for (int i = 0; i < s.length(); i++)
    {
      sums += s.at(i)+i; // value of character + position
    }
    //Cloudy with a Chance of Meatballs hash function
    long foo = 11111111 + (((sums * 103) + (199 * s.length())) / 17) * 409 + 2396743;
    string poo = std::to_string(foo);
    string temp = "";
    char c;
    for (int z = 0; z < poo.length(); z++)
    {
      switch (poo.at(z))
      {
        // dyslexic people won't like this obfuscation
      case '0':
        c = 'q';
        break;
      case '1':
        c = 'p';
        break;
      case '2':
        c = 'd';
        break;
      case '3':
        c = 'b';
        break;
      case '4':
        c = 'y';
        break;
      case '5':
        c = 'g';
        break;
      case '6':
        c = 'j';
        break;
      case '7':
        c = 'i';
      case '8':
        c = 'x';
        break;
      case '9':
        c = 'k';
        break;
      }
      if (temp.length() < 8)
      {
        temp.push_back(c);
      }

    }

    return temp;

  }
}
