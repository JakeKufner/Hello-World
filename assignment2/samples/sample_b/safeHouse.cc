// Name of program mainreturn.cpp 
#include <iostream> 
#include <string>
#include <vector>
#include "safeHouse.h"
using namespace std;

vector<string> commands;

int main(int argc, char** argv) 
{ 
	
    string owner = argv[1];
    House *secure_house = new House(owner);

    if (argc > 2)
    {
        for (int i = 2; i < argc; ++i)
        { 
		    secure_house->add_key(argv[i]);
        }
    }

// reading inputs  
string line; 
int space_pos;

while(getline(cin, line)) 
{
    // separate the commands to individual words
    do
    {
        space_pos = line.find(" ");
        if (space_pos == -1)
        {
            commands.push_back(line);
        }
        else
        {
            commands.push_back(line.substr(0,space_pos));
            line = line.substr(space_pos+1);
        }
       
    } while(space_pos != -1);

program( &(*secure_house) );


commands.clear();
}

	return 0; 
} 







void program(House *SH)
{


switch( toEnum(commands.at(0)) )
{
case INSERT: 
        {
            string person = commands.at(2);
            string persons_key = commands.at(3);
            SH->owner_and_key(person, persons_key);

            // response 
            cout << "KEY " << persons_key << " "<< "INSERTED BY " << person << endl;  

        }
    break;

case TURN: 
        {
            string person = commands.at(2); 
            vector<string> PaK = SH->return_OAK();
            
            if (PaK.at(0) == "NULL") { cout << "ERROR" << endl; }
            
            if ( PaK.at(0) == person)
            {
                if ( SH->validate(PaK.at(1)) )
                {
                    cout << "SUCCESS " << PaK.at(0) << " TURNS KEY " << PaK.at(1) << endl;
                    SH->waitingOutside(PaK.at(0));
                }
                else
                {
                    cout << "FAILURE " << PaK.at(0) << " UNABLE TO TURN KEY " << PaK.at(1) << endl;
                }
            } 
            else 
            { 
                cout << "ERROR" << endl;
            }  

        }
    break;

case ENTER: 
        {
            string person = commands.at(2); 
            if (SH->had_valid_key(person))
            {
                SH->people_inside.push_back(person);
                cout << "ACCESS OK" << endl;
            }
            else
               { cout << "ACCESS REJECTED" << endl;}
        }
        break;

case WHOS:
        {
            if (SH->people_inside.size() == 0)
            {
                cout << "NOBODY HOME" << endl;
            }
            else if (SH->people_inside.size() == 1)
            {
                cout << SH->people_inside.at(0) << endl;
            }
            else
            {
                vector<string>::iterator it;
                for( it = SH->people_inside.begin(); it != SH->people_inside.end(); it++)
                    if (it != (SH->people_inside.end()-1))
                        cout << *it << ", ";
                    else
                        cout << *it ; 
                cout << endl;
            }
        }
    break;

case CHANGE:
        {
            string person = commands.at(2);
            vector<string> temp; 
            for (int x = 3; x < commands.size(); x++)
                temp.push_back(commands.at(x));
            
            if (person == SH->return_owner() && SH->is_inside(person))
            {
                SH->reKey(temp);
                cout << "OK" << endl;
            }
            else
            { cout << "ACCESS REJECTED" << endl; } 

        }
    break;
case LEAVE:
        {
            string person = commands.at(2);
            if ( SH->is_inside(person) )
            {
                SH->remove_person(person);
                cout << "OK" << endl;
            }
            else
            { cout << person << " NOT HERE" << endl; }
        }
    break;

default: 
    cout << "NOT OK" << endl;
    break;
}


}
