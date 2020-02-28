#include <iostream>
#include <iomanip> //to format the output
#include <string>

using namespace std;

//struct Person represents certain person information
struct Person
{
	string name;
	string key;
	bool canEnter;
	bool inHouse;
	struct Person* next;
};

//class LinkedList will contains a linked list of Persons
class LinkedList
{
private:
	struct Person* head;

public:
	LinkedList();
	~LinkedList();
	bool isFound(string personName);
	bool addPerson(string personName, string key);
	bool removePerson(string personName);
	string insertKey(string personName);
	void printPersonList();
	void enterHouse(string personName);
	void canEnter(string personName);
	bool getCanEnter(string personName);
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList() //Destrutor to save space
{
	int personCount = 0;
	Person* current = head;

	while (current != NULL)
	{
		Person* next = current->next;		//Don't unlink the linkage!!
		delete(current);
		current = next;
		personCount++;
	}
	head = NULL;
	cout << "The number of deleted persons is: " << personCount << "\n";
}

bool LinkedList::isFound(string personName) //see if name exists in linked list
{
	struct Person* start = head;
	bool found = false;
	while (start != NULL)
	{
		if (start->name == personName)
		{
			found = true;
			break;
		}
		else
			start = start->next;
	}
	return found;
}

bool LinkedList::addPerson(string personName, string keyName) //person is added to linked list along with the key they were using
{
	if (isFound(personName))
	{
		return false;
	}
	else
	{
		Person* temp = new Person();			//contains newest node
		Person* previous = head;				//node previous to current
		Person* current = head;				//traversing node
		temp->name = personName;
		temp->key = keyName;
		temp->canEnter = false;
		temp->inHouse = false;
		if (head == NULL)						//if head is null
		{
			head = temp;
			return true;
		}
		while (current != NULL)
		{												
			previous = current;
			current = current->next;
		}
		previous->next = temp;									//if inserting node at the end of list
	}
	return true;
}
string LinkedList::insertKey(string personName)	//get name of key related to person
{
	Person* current = head;
	while (current != NULL)
	{
		if (current->name == personName)
		{
			return current->key;
		}
		current = current->next;
	}
}

//Return true if it is successfully removed, false otherwise.
bool LinkedList::removePerson(string personName) //remove targeted person
{
	if (isFound(personName))
	{
		Person* current = head;
		Person* temp;
		Person* previous = head;
		if (head->name == personName)				//if removing head, must replace head
		{
			temp = head;
			head = head->next;
			delete(temp);
			return true;
		}
		else
		{
			while (current->name != personName)	//removing node from elsewhere
			{
				previous = current;
				current = current->next;
			}
			previous->next = current->next;
			delete(current);							
			return true;
		}
	}
	else
	{
		return false;
	}
}
void LinkedList::canEnter(string personName) //set if person can enter or not
{
	Person* current = head;
	while (current != NULL)
	{
		if (current->name == personName)
		{
			current->canEnter = true;
		}
		current = current->next;
	}
}
bool LinkedList::getCanEnter(string personName) //retrieve boolean if person can enter
{
	Person* current = head;
	while (current != NULL)
	{
		if (current->name == personName)
		{
			if (current->canEnter == true)
			{
				return true;
			}
		}
		current = current->next;
	}
	return false;
}

void LinkedList::enterHouse(string personName) //change inHouse to be true
{
	Person* current = head;
	while (current != NULL)
	{
		if (current->name == personName)
		{
			current->inHouse = true;
		}
		current = current->next;
	}
}

//Prints all the elements in the linked list starting from the head node.
void LinkedList::printPersonList()
{
	int headCount = 0;
	Person* current = head;
	while (current != NULL)
	{
		if (current->inHouse == true)
		{
			if (current->next == NULL)
			{
				cout << current->name << "\n";
				current = current->next;
				headCount++;
			}
			else
			{
				cout << current->name << "--";	
				current = current->next;
				headCount++;
			}
		}
		else
		{
			current = current->next;
		}
	}
	if (headCount == 0)
	{
		cout << "NOBODY'S HOME\n";
	}
}
