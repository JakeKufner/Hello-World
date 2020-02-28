#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//person class 
class Person
{
    private:
        bool isOwner;
        bool isInside;
        bool hasAccess;
        string* name;
        string* persons_key;
    public:
        //constructor takes in a name of the person
        Person(string name_of_person)
        {
            isOwner = false;
            isInside = false;
            hasAccess = false;
            name = new string(name_of_person);
            persons_key = new string("");
        }
        ~Person ()
        {  
		   delete name;
		   delete persons_key;
		}

        string getKey()
        {
		   return *persons_key;
        }
        string getName()
        {
            return *name;
        }
        bool getIsOwner()
        {
            return isOwner;
        }
        bool getIsInside()
        {
            return isInside;
        }
        bool getHasAccess()
        {
            return hasAccess;
        }
        void setKey(string newkey)
        {
            *persons_key = newkey;
        }
        void setName(string newname)
        {
		    *name = newname;
        }
        void setIsOwner(bool personOwner)
        {
            isOwner = personOwner;
        }
        void setIsInside(bool personInside)
        {
            isInside = personInside;
        }
        void setHasAccess(bool access)
        {
            hasAccess = access;
        }

};
vector<Person*> allPeople;

class House
{
    private:
        vector<string> valid_keys;
        vector<Person*> peopleinside;
    
    public:
        House(vector<string> keys)
        {
            valid_keys = keys;
            valid_keys.push_back("FIREFIGHTER_SEC_KEY");
        }
        bool isValidKey(string key)
        {
            for(int i = 0; i < valid_keys.size(); i++)
            {
                if(key.compare(valid_keys[i].data()) == 0)
                {
                    return true;
                }
            }
            return false;
        }
        void printPeopleInside()
        {
            if(peopleinside.size() == 0)
            {
                cout << "NOBODY HOME";
            }
            else if(peopleinside.size() == 1)
            {
                cout << peopleinside[0]->getName();
            }
            else
            {
                for(int i = 0; i < peopleinside.size() - 1; i++)
                {
                    cout << peopleinside[i]->getName() << ", ";
                }
                cout << peopleinside[peopleinside.size() - 1]->getName();
            }
            cout << endl;
        }
        void setKeys(vector<string> newKeys)
        {
            valid_keys = newKeys;
            valid_keys.push_back("FIREFIGHTER_SEC_KEY");
        }
        void addPerson(Person* newPerson)
        {
            peopleinside.push_back(newPerson);
        }
        bool removePerson(string name)
        {
            bool removed = false;
            for(int i = 0; i < peopleinside.size(); i++)
            {
                if(peopleinside[i]->getName().compare(name) == 0)
                {
                    peopleinside[i]->setIsInside(false);
                    peopleinside[i]->setHasAccess(false);
					delete peopleinside[i];
                    peopleinside.erase(peopleinside.begin() + i);
                    removed = true;
                }
            }
            return removed;
        }
};

bool findPerson(string aname, vector<Person*> listofpeople, Person** newperson)
{
    for(int i = 0; i < listofpeople.size(); i++)
    {
        if(listofpeople[i]->getName().compare(aname) == 0)
        {
            *newperson = listofpeople[i];
            return true;
        }
    }
    return false;
}
void printPersons(vector<Person*> listofpeople)
{
    for(int i = 0; i < listofpeople.size(); i++)
    {
        cout << "Name: " << listofpeople[i]->getName() << endl;
        cout << "Key: " << listofpeople[i]->getKey() << endl;
    }
}


//functions for different commands
void InsertKeyCommand(string person_name, string key)
{
    Person* newPerson;
    //if a person has this name, don' create a new person
    //if the person is found, newPerson variable will hold a pointer to the person after the findPerson function
    if(!findPerson(person_name, allPeople, &newPerson))
    {
        newPerson = new Person(person_name);
        allPeople.push_back(newPerson);
        newPerson->setKey(key);
        //printPersons(allPeople);
    }
    else
    {
        newPerson->setKey(key);
        //printf("Person was found");
    }
    //printPersons(allPeople);
    cout << "KEY " << key << " IS INSERTED BY " << newPerson->getName() <<endl;
}
void TurnKeyCommand(string name, House* home)
{
    Person* tempPerson;
    if(findPerson(name, allPeople, &tempPerson))
    {
        if(home->isValidKey(tempPerson->getKey()))
        {
            tempPerson->setHasAccess(true);
            cout << "SUCCESS BY " << tempPerson->getName() << " TURNS KEY " << tempPerson->getKey() << endl;
        }
        else
        {
            cout << "FAILURE BY " << tempPerson->getName() << " UNABLE TO TURN KEY " << tempPerson->getKey() << endl;
        }
    }
}
void EnterHouseCommand(string name, House* home)
{
    Person* tempPerson;
    if(findPerson(name, allPeople, &tempPerson))
    {
        if(tempPerson->getHasAccess())
        {
            tempPerson->setIsInside(true);
            home->addPerson(tempPerson);
            cout << "ACCESS IS ALLOWED" << endl;
        }
        else
        {
            cout << "ACCESS IS DENIED" << endl;
        }
        
    }
}

void ChangeLocksCommand(House* home, vector<string> keys)
{
    home->setKeys(keys);
}
void LeaveHouseCommand(string name, House* home)
{
    if(home->removePerson(name))
    {
        cout << "OK BY ME" << endl;
    }
    else
    {
        cout << name << " IS NOT HERE" << endl; 
    }
    
}
void printKeys(vector<string> keys)
{
    for(int i = 0; i < keys.size(); i++)
    {
        printf("Key %i: %s\n", (i+1), keys[i].data());
    }
}

//main
int main( int argc, const char* argv[] )
{
    //only continue if at least 2 arguments along with the program name
    if(argc < 3)
    {
        printf("Not enough arguments to start program\n");
        exit(1);
    }

    //Create a person for the owner of the house
    Person* owner = new Person(argv[1]);
    owner->setIsOwner(true);
    allPeople.push_back(owner);
    
    //Store all valid keys given through the command line into vector of keys
    vector<string> keys;
    for(int i = 2; i < argc; i++)
    {
        keys.push_back(argv[i]);
    }

    //create a house object with valid keys given
    House* home = new House(keys);

    //prompt for a command and read the entire line
    string command;
   

    string token;
    string tempname;
    string tempkey;
    while(getline(cin,command))
    {
        //cout << command << endl;
        //create a istringstream for the string
        istringstream iss(command);

        //Stores first word of command in token
        
        iss >> token;

        //Insert Key
        if(token.compare("INSERT") == 0)
        {
            
            //consume the word KEY
            iss >> token;

            //token becomes the name of person
            iss >> tempname;

            //token becomes key
            iss >> tempkey;
            InsertKeyCommand(tempname, tempkey);
        }

        //Turn Key
        else if(token.compare("ROTATE") == 0)
        {
            //consume the word KEY
            iss >> token;

            //token becomes the name of person
            iss >> tempname;

            TurnKeyCommand(tempname, home);
        }

        //Enter House
        else if(token.compare("ENTER") == 0)
        {
            //consume the word HOUSE
            iss >> token;

            //token becomes the name of person
            iss >> tempname;

            EnterHouseCommand(tempname, home);
        }

        //Who's Inside
        else if(token.compare("WHO'S") == 0)
        {
            //consume the word INSIDE?
            iss >> token;
            home->printPeopleInside();
        }

        //Change Locks
        else if(token.compare("CHANGE") == 0)
        {
            //consume the word LOCKS
            iss >> token;

            //token becomes the name of person
            iss >> tempname;

            //if person is owner, proceed
            if(tempname.compare(owner->getName()) == 0 && owner->getIsInside())
            {
                keys.clear();
                iss >> tempkey;
                keys.push_back(tempkey);
                while(!iss.eof())
                {
                    iss >> tempkey;
                    keys.push_back(tempkey);
                }
                ChangeLocksCommand(home, keys);
                cout << "IS OK" << endl;
            }
            else
            {
                cout << "ACCESS IS DENIED" << endl;
            }
            
            
        }

        //Leave House
        else if(token.compare("LEAVE") == 0)
        {
            //consume the word HOUSE
            iss >> token;
            if(!token.compare("HOUSE") == 0)
            {
                cout << "IS ERROR" << endl;
            }
            //token becomes the name of person
            iss >> tempname;
            LeaveHouseCommand(tempname, home);
        }
        else
        {
            printf("IS ERROR\n");
        }
         
    }
    
    
    
    return 0;
}
