
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void insertKey(stringstream&, string&, string&, bool&);
void turnKey(stringstream&, string&, string&, bool&, string*, int);
bool verifyKey(string&, string*, int);
void enterHouse(stringstream&, string&, bool&, vector<string>&);
void leaveHouse(stringstream&, vector<string>&, bool&);
void changeLocks(stringstream&, string&, string*&, vector<string>&, bool&, int&);
bool ownerInside(string&, vector<string>&);
void whosInside(stringstream&, vector<string>&);

int main(int argc, char* argv[]) 
{
   string owner = argv[1];
   
   int numKeys = argc - 1;
   string* keys = new string[numKeys];
   string insertedKey = "";
   string atDoor = "";
   
   bool lockOpen = false;
   vector<string> occupants;
   
   for (int i = 2; i < argc; i++)
   {
      keys[i-2] = argv[i];
   }
   
   keys[numKeys - 1] = "FIREFIGHTER_KEY_SECRET";
      
   string line;
   string str;
   string command;
   
   while (!cin.eof()) 
   { 
      getline(cin, line);  
      stringstream ss(line);
      command = "";
      
      ss >> str;
      command += str;
      ss >> str;
      command += " " + str;
      
      if (command.compare("INSERT KEY") == 0)
         insertKey(ss, insertedKey, atDoor, lockOpen);
      else if (command.compare("TURN KEY") == 0)
         turnKey(ss, insertedKey, atDoor, lockOpen, keys, numKeys);
      else if (command.compare("ENTER HOUSE") == 0)
         enterHouse(ss, atDoor, lockOpen, occupants);
      else if (command.compare("LEAVE HOUSE") == 0)
         leaveHouse(ss, occupants, lockOpen);
      else if (command.compare("WHO INSIDE?") == 0)
         whosInside(ss, occupants);
      else if (command.compare("CHANGE LOCKS") == 0)
         changeLocks(ss, owner, keys, occupants, lockOpen, numKeys);
      else if (!cin.eof())
         cout << "ERROR" << endl;
   }
   return 0;
}

void insertKey(stringstream& ss, string& insertedKey, string& atDoor, bool& lockOpen)
{
   string str;
   string username;
   string key;
   
   ss >> username;
   ss >> key;
   ss >> str;
   
   if (str.compare("") != 0 || username.compare("") == 0
       || key.compare("") == 0)
   {
      cout << "ERROR" << endl;
      return;
   }
   
   cout << "KEY " << key << " INSERTED BY " << username << endl;
   
   insertedKey = key;
   atDoor = username;
   lockOpen = false;
}

void turnKey(stringstream& ss, string& insertedKey, string& atDoor, 
             bool& lockOpen, string* keys, int numKeys)
{
   string str;
   string username; 
   
   ss >> username;
   ss >> str;
   
   if (str.compare("") != 0 || username.compare("") == 0)
   {
      cout << "ERROR" << endl;
      return;
   }
   
   if (verifyKey(insertedKey, keys, numKeys) && atDoor.compare(username) == 0)
   {
      cout << "SUCCESS " << username << " TURNS " << insertedKey << endl;
      lockOpen = true;
   }  
   else
   {
      cout << "FAILURE " << username << " UNABLE TO TURN " << insertedKey << endl;
      lockOpen = false;
   }

}

bool verifyKey(string& insertedKey, string* keys, int numKeys)
{
   for (int i = 0; i < numKeys; i++)
   {
      if (insertedKey.compare(keys[i]) == 0)
         return true;
   }
   
   return false;
}

void enterHouse(stringstream& ss, string& atDoor, bool& lockOpen, vector<string>& occupants)
{
   string str;
   string username; 
   
   ss >> username;
   ss >> str;
   
   if (str.compare("") != 0 || username.compare("") == 0)
   {
      cout << "ERROR" << endl;
      return;
   }
   
   if (username.compare(atDoor) == 0 && lockOpen)
   {
      cout << "ACCESS ALLOWED" << endl;
      occupants.push_back(atDoor);
      lockOpen = false;
   }
   else
      cout << "ACCESS DENIED" << endl;
      
}

void leaveHouse(stringstream& ss, vector<string>& occupants, bool& lockOpen)
{
   string str;
   string username; 
   
   ss >> username;
   ss >> str;
   
   if (str.compare("") != 0 || username.compare("") == 0)
   {
      cout << "ERROR" << endl;
      return;
   }
   
   for (vector<string>::iterator i = occupants.begin(); i != occupants.end(); i++)
   {
      if (username.compare(*i) == 0)
      {
         cout << "OK" << endl;
         occupants.erase(i);
         lockOpen = false;
         return;
      }
   }
   
   cout << username << " NOT HERE" << endl;
}

void changeLocks(stringstream& ss, string& owner, string*& oldKeys, 
                 vector<string>& occupants, bool& lockOpen, int& oldNumKeys)
{
   int numKeys = 0;
   string keys = "";
   string str;
   string username; 
   
   ss >> username;
   ss >> str;
   
   while (!ss.eof())
   { 
      keys += str + " ";
      numKeys++;
      ss >> str;
   }
   
   if (str.compare("") != 0)
   {
      keys += str + " ";
      numKeys++;
   }
  
   if (username.compare("") == 0 || numKeys == 0)
   {
      cout << "ERROR" << endl;
      return;
   }
   
   if (username.compare(owner) != 0 || !ownerInside(owner, occupants))
      cout << "ACCESS DENIED" << endl;
   else
   {
      cout << "OK" << endl;
      
      numKeys++; //Remember firefighter key
      string* newKeys = new string[numKeys];
      stringstream keystream(keys);
      
      for (int i = 0; i < numKeys - 1; i++)
      {
         keystream >> newKeys[i];
      }
      newKeys[numKeys - 1] = "FIREFIGHTER_SECRET_KEY";
      
      string* temp = oldKeys;
      oldKeys = newKeys;
      delete[] temp;
      oldNumKeys = numKeys;
      lockOpen = false;
   }
 
}

bool ownerInside(string& owner, vector<string>& occupants)
{
   for (vector<string>::iterator i = occupants.begin(); i != occupants.end(); i++)
   {
      if (owner.compare(*i) == 0)
      {
         return true;
      }
   }
   
   return false;
}

void whosInside(stringstream& ss, vector<string>& occupants)
{
   string str;
   
   ss >> str;
   
   if (str.compare("") != 0)
   {
      cout << "ERROR" << endl;
      return;
   }

   if (occupants.size() == 0)
      cout << "NOBODY HERE" << endl;
   else
   {
      vector<string>::iterator i = occupants.begin();
      cout << *i;
	  cout << " ";
	  whosInside(ss, occupants);
	  
      cout << endl; 
   }
   
}
