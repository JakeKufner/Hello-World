#include <vector>
#include <string>

using namespace std;
struct Key {
	string keyName;
	bool used;
};

struct User {
	string userName;
	Key userKey;
};

class House {
public:
	Key cKey;
	User user1;
	bool turned;
	bool validKey;
	string currentKey;
	string currentUser;
	string ownerName;
	vector <Key> allowedKeys;
	vector <User> insideUsers;

	
	bool changeLocks();
	string enterHouse(string enteringUser);
	string insertKey(string comingUser, string comingKey);
	string leaveHouse(string u);
	string turnKey(string comingUser);
	void addUser(User u);
	void createKeys(vector <string> newKeys);
	void listInside();
	
	bool searchUser(string name);
	bool usedKey(string kname);
	int searchKey(string keyName);
	int userIndex(string name);
	void changeKeyUsed(string kname);
	void printKeyList();
};

