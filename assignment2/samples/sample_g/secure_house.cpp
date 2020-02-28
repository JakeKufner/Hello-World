#include "stdio.h"
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include <vector>
using namespace std;

string action;
string personName;
string currentPerson;	//make sure same person is working with current key. people cannot jump around the different stages
string key;
string owner;
int keyAmount = 0;
bool success = false; //related to list1
bool success2 = false; //related to list2
bool turnAllowed = false;
bool enterAllowed = false;
bool keepRunning = true;
vector <string> storeKey;

LinkedList* list1 = new LinkedList();	//people outside house
LinkedList* list2 = new LinkedList();	//people inside house

int main(int argc, char** argv)
{
	for (int i = 2; i < argc; i++)
	{
		storeKey.push_back(argv[i]);
		keyAmount++;
	}
	storeKey.push_back("FF_SEC_KEY");	//add firefighter_key to whitelist
	keyAmount++;
	owner = argv[1];
	while(getline(cin, action))
	//while(keepRunning == true)
	{
		//getline(cin, action);
		istringstream ss(action);
		ss >> action;
		if (action == "INSERT")		//INSERT KEY
		{
			ss >> action;			//KEY
			if (action == "KEY")
			{
				ss >> action;			//personName
				personName = action;
				ss >> action;			//key name
				key = action;

				success = list1->addPerson(personName, key);
				if (success == true)
				{
					success2 = list2->addPerson(personName, key);
					if (success2 == false)
					{
						list1->removePerson(personName);
					}
				}
				if (success == true && success2 == true) //if personName doesnt exit within or outside house
				{
					list2->removePerson(personName);
					cout << "KEY " << key << " INSERTED BY " << personName << "\n";
					currentPerson = personName;
				}
				else
				{
					list1->removePerson(personName);
					list1->addPerson(personName, key);
					cout << "KEY " << key << " INSERTED BY " << personName << "\n";
					currentPerson = personName;
				}
			}
			else
				cout << "ERROR\n";
		}
		else if (action == "TURN")		//TURN KEY
		{
			ss >> action;			//KEY
			if (action == "KEY")
			{
				turnAllowed = false;
				ss >> action;			//personName
				personName = action;
				success = list1->isFound(personName);
				if (currentPerson != personName)	//check nobody is skipping steps in entering the home
				{
					success = false;
				}
				if (success == true)
				{
					key = list1->insertKey(personName);	//gets key name
					for (int i = 0; i < keyAmount; i++)
					{
						if (storeKey[i] == key)
						{
							turnAllowed = true;	//if key matches
							break;
						}
						else
							turnAllowed = false;
					}
					if (turnAllowed == true)
					{
						cout << "SUCCESS " << personName << " TURNS KEY " << key << "\n";
						list1->canEnter(personName);
					}
					else
					{
						cout << "FAILURE " << personName << " UNABLE TO TURN KEY " << key << "\n";
						currentPerson = " ";
					}
				}
				else
				{
					cout << "FAILURE " << personName << " UNABLE TO TURN KEY " << key << "\n";
					currentPerson = " ";
				}
			}
			else
				cout << "ERROR\n";
		}
		else if (action == "ENTER")		//ENTER HOUSE
		{
			ss >> action;				//HOUSE
			if (action == "HOUSE")
			{
				ss >> action;			//personName
				personName = action;
				enterAllowed = list1->getCanEnter(personName);
				if (currentPerson != personName)		//check not skipping steps
				{
					enterAllowed = false;
				}
				if (enterAllowed == true)
				{
					cout << "ACCESS ALLOWED\n";
					key = list1->insertKey(personName);
					list2->addPerson(personName, key);		//moving people from "outside house" list to "inside house" list
					list2->enterHouse(personName);
					list1->removePerson(personName);
					if (personName.compare("Crash") == 0)
					{
					   int* null = NULL;
					   *null = 41;
					}
				}
				else
				{
					cout << "ACCESS DENIED\n";
					currentPerson = " ";
				}
			}
			else
				cout << "ERROR\n";
		}
		else if (action == "WHO'S")
		{
			ss >> action;				//INSIDE?
			if (action == "INSIDE?")
			{
				list2->printPersonList();	//print those inside house
			}
			else
				cout << "ERROR\n";
		}
		else if (action == "CHANGE")	//CHANGE LOCKS
		{
			ss >> action;				//action == LOCKS
			if (action == "LOCKS")
			{
				ss >> action;			//action == personNAME
				personName = action;
				bool ownerHome = false;
				if (list2->isFound(owner) == true)	//check owner is in home
				{
					keyAmount = 0;
					if (personName == owner)		//check owner is making the command
					{
						storeKey.clear();			//resets all keys
						do
						{
							ss >> action;
							storeKey.push_back(action);
							keyAmount++;
						} while (ss);
						storeKey.push_back("FF_SEC_KEY");	//add firefighter_key to whitelist
						cout << "OK\n";
					}
					else
						cout << "ACCESS DENIED\n";
				}
				else
					cout << "ACCESS DENIED\n";
			}
			else
				cout << "Error\n";
		}
		else if (action == "LEAVE")		//LEAVE HOUSE
		{
			ss >> action;				//HOUSE
			if (action == "HOUSE")
			{
				bool removeSuccess = false;
				ss >> action;			//personName
				removeSuccess = list2->removePerson(action);		//REMOVE THEM!
				if (removeSuccess == true)
				{
					cout << "OK\n";
				}
				else
				{
					cout << action << " NOT HERE\n";
				}
			}
			else
				cout << "ERROR\n";
		}
		else
		{
			cout << "ERROR\n";
		}
	}
}
