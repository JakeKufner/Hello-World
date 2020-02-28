#include <iostream>
#include <string>
#include <vector>
#include <string.h>

std::string ownerName;
std::vector<std::string> keyList;
std::string insertedUser;
std::string insertedKey;
std::vector<std::string> turned;
std::vector<std::string> inside;

void insertKey(std::string, std::string);
void turnKey(std::string);
void enterHouse(std::string);
void whosInside();
void changeLocks(std::string, std::vector<std::string>);
void leaveHouse(std::string);

std::vector<std::string> splitString(const char*);

int main(int argc, char *argv[])
{
    keyList.push_back("FIREFIGHTER_AND_POLICE_SECRET_KEY");
    ownerName = argv[1];
    for (int i = 2; i < argc; i++)
    {
        keyList.push_back(argv[i]);
    }

    std::string inputString;

    while (getline(std::cin, inputString))
    {
	    std::vector<std::string> wordList = splitString(inputString.c_str());
        if (wordList.size() == 4 &&
            wordList.at(0).compare("INSERT") == 0 && wordList.at(1).compare("KEY") == 0)
        {
            insertKey(wordList.at(2), wordList.at(3));
        }
        else if (wordList.size() == 3 &&
                 wordList.at(0).compare("TURN") == 0 && wordList.at(1).compare("KEY") == 0)
        {
            turnKey(wordList.at(2));
        }
        else if (wordList.size() == 3 &&
                 wordList.at(0).compare("ENTER") == 0 && wordList.at(1).compare("HOUSE") == 0)
        {
            enterHouse(wordList.at(2));
        }
        else if (wordList.size() == 2 &&
                 wordList.at(0).compare("WHO'S") == 0 && wordList.at(1).compare("INSIDE?") == 0)
        {
            whosInside();
        }
        else if (wordList.size() > 3 &&
                 wordList.at(0).compare("CHANGE") == 0 && wordList.at(1).compare("LOCKS") == 0)
        {
            std::vector<std::string> newKeyList;
            for (unsigned int i = 3; i < wordList.size(); i++)
            {
                newKeyList.push_back(wordList.at(i));
            }
            changeLocks(wordList.at(2), newKeyList);
        }
        else if (wordList.size() == 3 &&
                 wordList.at(0).compare("LEAVE") == 0 && wordList.at(1).compare("HOUSE") == 0)
        {
            leaveHouse(wordList.at(2));
        }
        else
        {
            std::cout << "FAIL\n";
        }
    }

    return 0;
}

void insertKey(std::string user, std::string key)
{
    insertedUser = user;
    insertedKey = key;
    std::cout << key << " INSERTED BY " << user << "\n";
}

void turnKey(std::string user)
{
    if (insertedKey.empty())
    {
        std::cout << "ERROR\n";
        return;
    }
    if (user.compare(insertedUser) == 0)
    {
        for (unsigned int i = 0; i < keyList.size(); i++)
        {
            if (keyList.at(i).compare(insertedKey) == 0)
            {
                std::cout << "GREAT " << user << " TURNS KEY " << insertedKey << "\n";
                insertedUser.clear();
                insertedKey.clear();
                turned.push_back(user);
                return;
            }
        }
    }
    std::cout << "ERROR " << user << " UNABLE TO TURN KEY " << insertedKey << "\n";
}

void enterHouse(std::string user)
{
    bool userTurned = false;
    unsigned int position;
    for (unsigned int i = 0; i < turned.size(); i++)
    {
        if (user.compare(turned.at(i)) == 0)
        {
            userTurned = true;
            position = i;
        }
    }
    if (userTurned)
    {
        inside.push_back(user);
        turned.erase(turned.begin() + position);
        std::cout << "ALLOWED\n";
    }
    else
    {
        std::cout << "DENIED\n";
    }
}

void whosInside()
{
    if (inside.size() == 0)
    {
        std::cout << "NOBODY IS HERE\n";
    }
    else
    {
        for (unsigned int i = 0; i < inside.size() - 1; i++)
        {
            std::cout << inside.at(i) << ", ";
        }
        std::cout << inside.at(inside.size() - 1) << "\n";
    }
}

void leaveHouse(std::string user)
{
    bool userInside = false;
    unsigned int position;
    for (unsigned int i = 0; i < inside.size(); i++)
    {
        if (user.compare(inside.at(i)) == 0)
        {
            userInside = true;
            position = i;
        }
    }
    if (userInside)
    {
        inside.erase(inside.begin() + position);
        std::cout << "YOU OK\n";
    }
    else
    {
        std::cout << user << " NOT HERE\n";
    }
}

void changeLocks(std::string user, std::vector<std::string> newKeyList)
{
    bool userInside = false;
    for (unsigned int i = 0; i < inside.size(); i++)
    {
        if (user.compare(inside.at(i)) == 0)
        {
            userInside = true;
        }
    }
    if (user.compare(ownerName) == 0 && userInside)
    {

        keyList = newKeyList;
        keyList.push_back("FIREFIGHTER_AND_POLICE_SECRET_KEY");
        std::cout << "YOU OK\n";
    }
    else
    {
        std::cout << "DENIED\n";
    }
}

std::vector<std::string> splitString(const char* sent)
{
    std::vector<std::string> wordList;
	int i = 0;
	char* prev = NULL;
    while (*sent != '\0')
    {
	   for (i = 0; i < strlen(sent); i++)
	   {
		  if (sent[i] == ' ')
		  {
			 break;
		  }
		  else if (sent[i] == '&')
		  {
			 sent += *prev;
		  }
	   }
	   std::string new_string(sent, i);
	   wordList.push_back(new_string);
	   if (i + 1 == strlen(sent))
	   {
		  break;
	   }
	   sent = sent + i + 1;
    }
    return wordList;
}
