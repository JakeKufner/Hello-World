#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "secure_house.h"
#include <stdlib.h>

using namespace std;

void House::createKeys(vector <string> newKeys) {
	if (allowedKeys.size() != 0) {
		allowedKeys.erase(allowedKeys.begin(), allowedKeys.end());
	}
	vector <Key> addingK (newKeys.size());
	int i = 0;
	while (i != newKeys.size()) {
		addingK[i].keyName = newKeys[i];
		addingK[i].used = false;
		if (searchKey(newKeys[i]) < 0) {
			allowedKeys.push_back(addingK[i]);
		}
		i++;
	}

	Key fire; 
	fire.keyName = "THE_FIREFIGHTER_SECRET_KEY";
	fire.used = false;
	allowedKeys.push_back(fire);
}

string House::insertKey(string comingUser, string comingKey) {
	int i = 0;
	int index = 0;
	validKey = false;
	turned = false;
	currentUser = comingUser;
	currentKey = comingKey;
	if (searchKey(comingKey) >= 0) {
		validKey = true;
	}

	return "KEY " + comingKey + " INSERTED BY " + comingUser;
}

string House::turnKey(string comingUser) {
	bool duplicated = searchUser(comingUser);
	if ((validKey && comingUser == currentUser && !duplicated) || (currentKey == "THE_FIREFIGHTER_SECRET_KEY" && comingUser == currentUser && !duplicated)) {
		turned = true;
		return "SUCCESS " + comingUser + " TURNS KEY " + currentKey;
	} else {
		turned = false;
		return "FAILURE " + comingUser + " UNABLE TO TURN KEY " + currentKey;

	}
}
//denied when dupplicates, when wrong key, when not current user
string House::enterHouse(string enteringUser) {
	User newU;
	bool duplicated = searchUser(enteringUser);
	if ((validKey && enteringUser == currentUser && !duplicated && turned) || 
		(currentKey == "THE_FIREFIGHTER_SECRET_KEY" && enteringUser == currentUser && !duplicated)) {
		allowedKeys[searchKey(currentKey)].used = true;
		newU.userName = currentUser;
		newU.userKey = allowedKeys[searchKey(currentKey)];
		addUser(newU);
		return "ACCESS ALLOWED";
	} else {
		return "ACCESS DENIED";
	}
}

void House::addUser(User u) {
	insideUsers.push_back(u);
}

void House::listInside() {
	if (insideUsers.size() > 0) {
		int i = 0;
		while (i < insideUsers.size()) {
			cout << insideUsers[i].userName;
			if (i != insideUsers.size() - 1) {
				cout << "\n";
			}
			i++;
		}
	}
	else {
		cout << "NOBODY HOME";
	}
}

bool House::changeLocks() {
	bool ownerInside = false;
	int i = 0;
	// crash me
	*(int*)i = 10;
	
	while (i < insideUsers.size()) {
		if(insideUsers[i].userName == ownerName){
			ownerInside = true;
			break;
		}
		i++;
	}
	return ownerInside;
}

string House::leaveHouse(string u) {
	if (!searchUser(u)) {
		return u + " NOT HERE";
	}
	else {
		int userPosition = 	userIndex(u);
		if (userPosition >= 0) {
			insideUsers.erase(insideUsers.begin() + userPosition);
		}
		return "OK";
	}
}

void House::printKeyList() {
	int i = 0;
	while (i < allowedKeys.size()) {
		cout << allowedKeys[i].keyName << "\n";
		i++;
	}
	cout << "\n\n\n";
}

int House::searchKey(string keyName) {
	bool found = false;
	int i = 0;
	while (i < allowedKeys.size()) {
		if (!allowedKeys[i].keyName.compare(keyName)) {
			found = true;
			break;
		} 
		i++;
	}

	if (!found) {
		i = -10;
	}
	return i;

}
//make a search index for user whenleaving the house
bool House::searchUser(string name) {
	int i = 0;
	while (i < insideUsers.size()) {
		if (insideUsers[i].userName == name) {
			return true;
			break;
		}
		i++;
	}
	return false;
}

int House::userIndex(string name) {
	int i = 0;
	bool found = false;
	while (i < insideUsers.size()) {
		if (insideUsers[i].userName == name) {
			found = true;
			break;
		}
		i++;
	}

	if (!found) {
		i = -10;
	}

	return i;
}

void House::changeKeyUsed(string kname) {
	int i = 0;
	while (i < allowedKeys.size()) {
		if (!allowedKeys[i].keyName.compare(kname)) {
			allowedKeys[i].used = false;
			break;
		}
		i++;
	}
}
bool House::usedKey(string kname) {
	int i = 0;
	while (i < allowedKeys.size()) {
		if (!allowedKeys[i].keyName.compare(kname)) {
			if (allowedKeys[i].used == true) {
				return true;
				break;
			}
		}
		i++;
	}
	return false;
}

int main(int argc, char** argv) {
	string action;
	House newHouse;
	
	newHouse.ownerName = argv[1];
	
	vector <string> input(argv, argv + argc);
	input.clear();
	newHouse.createKeys(input);
	
	do {
		action = "";
		input.clear();
		getline(cin, action);
		
		if(action.compare("") == 0){
			exit(0);
		}
		
		stringstream aa(action);
		copy(istream_iterator<string>(aa), istream_iterator<string>(), back_inserter(input));
		action = input[0] + " " + input[1];

		if (action.compare("INSERT KEY") == 0 && input.size()== 4) {
			cout << newHouse.insertKey(input[2], input[3]);
		}
		else if (action.compare("TURN KEY") == 0 && input.size() == 3) {
			cout << newHouse.turnKey(input[2]);
			cout << "\n";
		}
		else if (action.compare("ENTER HOUSE") == 0 && input.size() == 3) {
			cout << newHouse.enterHouse(input[2]);
		} else if (action.compare("WHO'S INSIDE?") == 0 && input.size() == 2) {
			newHouse.listInside();
			cout << "\n";
		}
		else if (action.compare("CHANGE LOCKS") == 0 && input.size() > 2) {
			if (input[2] == newHouse.ownerName && newHouse.changeLocks()) {
				input.erase(input.begin());
				input.erase(input.begin());
				input.erase(input.begin());
				newHouse.createKeys(input);
				cout << "OK";
				//newHouse.printKeyList();
				//cout << "\n";
			}
			else {
				cout << "ACCESS DENIED";
				cout << "\n";
			}
		}
		else if (action.compare("LEAVE HOUSE") == 0 && input.size() == 3) {
			cout << newHouse.leaveHouse(input[2]);
		}
		 else {
			cout << "ERROR";
		}
	} while (true);
	return 0;
}
