#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <istream>
#include <iterator>

using namespace std;

struct Person {
	string name;
	bool isOwner;
	bool isInHouse;
	bool usingFireKey;
};

struct Key {
	string name;
	bool isInserted;
	bool isTurned;
	bool isValid;
	Person* beingUsedBy;
};

struct House {
	vector<Key*> houseKeys;
	vector<Person*> personsInHouse;
	Person* owner;
	Key* inserted;
};

Person* findPerson(string);
Key* findKey(string);
void turnKey(Person*, House*);
void insertKey(Person*, House*, Key*);
void whosInside(House*);
void walkIntoHouse(House*, Person*);
void enterHouse(Person*, House*);
void leaveHouse(Person*, House*);
void changeLocks(Person*, vector<string>, House*);

vector<string> commandArguments;
vector<Key*> validKeys;
vector<Person*> listOfPeople;
string owner;
Key* inserted;
Key* fireKey;




int main(int argc, char* argv[]) {
	House* thisHouse = new House;
	thisHouse->inserted = new Key;
	thisHouse->owner = NULL;
	for (int i = 1; i < argc; i++) {
		commandArguments.push_back(argv[i]);
	}
	if (commandArguments.size() > 1) {
		Person* owner = new Person;
		owner->name = commandArguments[0];
		owner->isOwner = true;
		owner->isInHouse = false;
		owner->usingFireKey = false;
		listOfPeople.push_back(owner);
		thisHouse->owner = owner;
	}
	fireKey = new Key;
	fireKey->isInserted = false;
	fireKey->isTurned = false;
	fireKey->isValid = true;
	fireKey->name = "FF_SECRET_KEY";
	validKeys.push_back(fireKey);
	for (int i = 1; i < commandArguments.size(); i++) {
		Key* newKey = new Key;
		newKey->isInserted = false;
		newKey->isTurned = false;
		newKey->isValid = true;
		newKey->name = commandArguments[i];
		validKeys.push_back(newKey);
	}

	thisHouse->houseKeys = validKeys;
	
	string inputString = "";
	
	while (getline(cin, inputString)) {
		//Slightly changed code posted on StackOverflow for splitting the string into a vector
		//Link : stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
		vector<string> inputStrings;
		string tmp;
		for (char x : inputString) {
			if (x == ' ' || x == EOF) {
				if (tmp.length() != 0) {
					inputStrings.push_back(tmp);
				}
				tmp = "";
			}
			else
			{
				tmp = tmp + x;
			}
		}
if (tmp.length() != 0) {
	inputStrings.push_back(tmp);
}
//End of borrowed code

if (inputStrings.size() == 0) {
	break;
}

if (inputStrings.size() > 1) {

	if (inputStrings[0] == "INSERT" && inputStrings[1] == "THEKEY" && inputStrings.size() == 4) {
		Person* attemptingPerson = findPerson(inputStrings[2]);
		Key* attemptingKey = findKey(inputStrings[3]);
		insertKey(attemptingPerson, thisHouse, attemptingKey);
	}
	else if (inputStrings[0] == "TURN" && inputStrings[1] == "THEKEY" && inputStrings.size() == 3) {
		Person* attemptingPerson = findPerson(inputStrings[2]);
		turnKey(attemptingPerson, thisHouse);
	}
	else if (inputStrings[0] == "ENTER" && inputStrings[1] == "THEHOUSE" && inputStrings.size() == 3) {
		Person* attemptingPerson = findPerson(inputStrings[2]);
		enterHouse(attemptingPerson, thisHouse);
	}
	else if (inputStrings[0] == "WHO'S" && inputStrings[1] == "INSIDE?" && inputStrings.size() == 2) {
		whosInside(thisHouse);
	}
	else if (inputStrings[0] == "CHANGE" && inputStrings[1] == "THELOCKS" && inputStrings.size() >= 4) {
		vector<string> newKeyList;
		Person* attemptingPerson = findPerson(inputStrings[2]);
		for (int i = 3; i < inputStrings.size(); i++) {
			newKeyList.push_back(inputStrings[i]);
		}
		changeLocks(attemptingPerson, newKeyList, thisHouse);
	}
	else if (inputStrings[0] == "LEAVE" && inputStrings[1] == "THEHOUSE" && inputStrings.size() == 3) {
		Person* attemptingPerson = findPerson(inputStrings[2]);
		leaveHouse(attemptingPerson, thisHouse);
	}
	else {
		cout << "ERROR\n";
	}
}
	}

	return 0;
}

Person* findPerson(string name) {
	for (int i = 0; i < listOfPeople.size(); i++) {
		if (listOfPeople[i]->name == name) {
			return listOfPeople[i];
		}
	}
	Person* newPerson = new Person;
	newPerson->isInHouse = false;
	newPerson->isOwner = false;
	newPerson->usingFireKey = false;
	newPerson->name = name;
	listOfPeople.push_back(newPerson);
	return newPerson;
}

Key* findKey(string name) {
	for (int i = 0; i < validKeys.size(); i++) {
		if (validKeys[i]->name == name) {
			return validKeys[i];
		}
	}
	Key* newInvalidKey = new Key;
	newInvalidKey->isInserted = false;
	newInvalidKey->isTurned = false;
	newInvalidKey->isValid = false;
	newInvalidKey->name = name;
	return newInvalidKey;
}


void insertKey(Person* somePerson, House* thisHouse, Key* key) {
	if (inserted != NULL) {
		inserted->isInserted = false;
		inserted->isTurned = false;
	}
	key->isInserted = true;
	key->beingUsedBy = somePerson;
	thisHouse->inserted = key;
	inserted = key;
	cout << "KEY " << key->name << " INSERTED BY " << somePerson->name << endl;
}

void turnKey(Person* somePerson, House* thisHouse) {
	if (thisHouse->inserted->beingUsedBy == somePerson) {
		if (inserted->beingUsedBy == somePerson) {
			if (thisHouse->inserted->isValid) {
				if (thisHouse->inserted->beingUsedBy == somePerson) {
					thisHouse->inserted->isTurned = true;
					cout << "SUCCESS " << somePerson->name << " TURNS KEY " << thisHouse->inserted->name << endl;
					return;
				}
			}
		}
	}
	cout << "FAILURE " << somePerson->name << " UNABLE TO TURN KEY " << thisHouse->inserted->name << endl;
}

void changeLocks(Person* somePerson, vector<string> newKeyList, House* thisHouse) {
	if (thisHouse->owner == somePerson) {
		if (somePerson->isOwner == true) {
			for (int i = 0; i < thisHouse->personsInHouse.size(); i++) {
				if (somePerson == thisHouse->personsInHouse[i]) {
					validKeys.clear();
					thisHouse->houseKeys.clear();
					vector<Key*> changedKeys;
					changedKeys.push_back(fireKey);
					for (int i = 0; i < newKeyList.size(); i++) {
						Key* newKey = new Key;
						newKey->name = newKeyList[i];
						newKey->isInserted = false;
						newKey->isTurned = false;
						newKey->isValid = true;
						changedKeys.push_back(newKey);
					}
					validKeys = changedKeys;
					thisHouse->houseKeys = validKeys;
					thisHouse->inserted = NULL;
					cout << "OK\n";
					return;
				}
			}
		}
	}
	cout << "ACCESS DENIED\n";
}

void walkIntoHouse(Person* somePerson, House* thisHouse) {
	for (int i = 0; i < thisHouse->personsInHouse.size(); i++) {
		if (thisHouse->personsInHouse[i] == somePerson) {
			return;
		}
	}
	thisHouse->personsInHouse.push_back(somePerson);
	somePerson->isInHouse = true;
}

void enterHouse(Person* somePerson, House* thisHouse) {
	if (thisHouse->inserted->isInserted == true) {
		if (thisHouse->inserted->isTurned == true) {
			if (thisHouse->inserted->beingUsedBy == somePerson) {
				walkIntoHouse(somePerson, thisHouse);
				cout << "ACCESS ALLOWED\n";
				thisHouse->inserted->isTurned == false;
				thisHouse->inserted->isInserted == false;
				thisHouse->inserted->beingUsedBy == NULL;
				return;
			}
		}
	}
	cout << "ACCESS DENIED\n";
}


void whosInside(House* thisHouse) {
	for (int i = 0; i < thisHouse->personsInHouse.size(); i++) {
		cout << thisHouse->personsInHouse[i]->name;
		if (i == thisHouse->personsInHouse.size() - 1) {
			cout << endl;
		}
		else {
			cout << ", ";
		}
	}
	if (thisHouse->personsInHouse.size() == 0) {
		cout << "NOBODY HOME\n";
	}
}

void leaveHouse(Person* somePerson, House* thisHouse) {
	if (somePerson->isInHouse == false) {
		cout << somePerson->name << " NOT HERE\n";
	}
	for (int i = 0; i < thisHouse->personsInHouse.size(); i++) {
		if (thisHouse->personsInHouse[i] == somePerson) {
			thisHouse->personsInHouse.erase(thisHouse->personsInHouse.begin() + i);
			somePerson->isInHouse = false;
			cout << "OK\n";
			return;
		}
	}
}
