#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char** argv) {
	std::vector<std::string> authorizedKeys;
	std::vector<std::string> userActions;
	std::vector<std::string> peopleInside;
	//std::vector<std::string>::iterator iter;
	std::string secretKey, owner, userInput, parsedInput, instruction, keyHolder, keyUsed;
	int offset;
	bool acceptableKey, keyTurned, personInside;

	secretKey = "POLICE_SECRET_KEY";						// initialize secret key literal string
	keyHolder = "\0";								// initialize current key user
	keyUsed = "\0";									// initialize current key being used
	acceptableKey = false;								// initialize system logic checks
	keyTurned = false;
	personInside = false;

	if (argc < 3)									// checks for proper formatting
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	owner = argv[1];								// get owner from user input
	
	for(int i = 2; i < argc; i++)							// set authorized keys as per user input
	{
		authorizedKeys.push_back(argv[i]);
	}
	
	while(1)
	{
		userActions.clear();							// reset user inputted instructions
		std::getline(std::cin, userInput, '\n');				// read user input
		std::stringstream stream(userInput);	

		while(std::getline(stream, parsedInput, ' '))
		{
			userActions.push_back(parsedInput);				// parse user input and push to userActions vector
		}
		
		if(std::cin.eof())							// checks that the file hasn't ended
		{
			break;
		}

		instruction = userActions[0] + " " + userActions[1];			// get instructions from parsed input

		if(instruction.compare((std::string)"PUT KEY") == 0)			// if the user inserts a key
		{
			if(userActions.size() != 4)					// check for proper formatting
			{
				std::cout << "ERROR" << std::endl;
			}
			else
			{
				keyHolder = userActions[2];				// assign current user
				keyUsed = userActions[3];				// assign inserted key

				for(int i = 0; i < authorizedKeys.size(); i++)				// checks all authorized keys
				{
					if(keyUsed == authorizedKeys[i] || keyUsed == secretKey)	// checks if the used key is an authorized key
					{
						acceptableKey = true;
						break;
					}
				}

				std::cout << "KEY " << keyUsed << " INSERTED BY " << keyHolder << std::endl;
			}
		}
		else if(instruction.compare((std::string)"ROTATE THE") == 0)		// if the user turns the key
		{
			if(userActions.size() != 3)					// checks for proper formatting
			{
				std::cout << "ERROR" << std::endl;
			}
			else
			{
				if(userActions[2] == keyHolder && acceptableKey)						// checks that the key is authorized and still the same user
				{
					keyTurned = true;
					std::cout << "SUCCESS " << userActions[2] << " TURNS KEY " << keyUsed << std::endl;
				}
				else
				{
					std::cout << "FAILURE " << userActions[2] << " UNABLE TO TURN KEY " << keyUsed << std::endl; 
				}
			}
		}
		else if(instruction.compare((std::string)"ENTER INSIDE") == 0)				// if the user tries to enter
		{
			if(userActions.size() != 3)							// checks for proper formatting
			{
				std::cout << "ERROR" << std::endl;
			}
			else
			{
				if(userActions[2] == keyHolder && keyTurned)				// checks that the key has turned and still the same user
				{
					peopleInside.push_back(keyHolder);				// user now inside
					
					std::cout << "ACCESS ALLOWED" << std::endl;
					keyHolder = "\0";                                                       // reset lock system
	                                keyUsed = "\0";
        	                        acceptableKey = false;
                	                keyTurned = false;

				}
				else
				{
					std::cout << "ACCESS DENIED" << std::endl;
				}
			/*	
				keyHolder = "\0";							// reset lock system
				keyUsed = "\0";
				acceptableKey = false;
				keyTurned = false;*/
			}
		}
		else if(instruction.compare((std::string)"WHO'S THERE") == 0)				// if the user wants to know who's inside the house currently
		{
			if(userActions.size() != 2)							// checks for proper formatting
			{
				std::cout << "ERROR" << std::endl;
			}
			else
			{
				if(peopleInside.size() == 0)						// checks if anyone is inside
				{
					std::cout << "NOBODY HOME" << std::endl;
				}
				else
				{
					for(int i = 0; i < peopleInside.size(); i++)			// print out list of all people inside
					{
						std::cout << peopleInside[i];
						
						if(i + 1 < peopleInside.size())
						{
							std::cout << ", ";
						}
					}

					std::cout << std::endl;
				}
			}
		}
		else if(instruction.compare((std::string)"CHANGE THEM") == 0)				// if the user wants to change the locks
		{
			if(userActions.size() < 4)							// checks for proper formatting
			{
				std::cout << "ERROR" << std::endl;
			}
			else
			{
				for(int i = 0; i < peopleInside.size(); i++)				// checks if owner is inside
				{
					if(owner == peopleInside[i])
					{
						personInside = true;
						break;
					}
				}

				if(userActions[2] == owner && personInside)				// if the owner is inside and is the same person as the user
				{
					authorizedKeys.clear();						// reset authorized keys

					for(int i = 3; i < peopleInside.size(); i++)			// set new authorized keys
					{
						authorizedKeys.push_back(userActions[i]);
					}

					std::cout << "OK" << std::endl;
				}
				else
				{
					std::cout << "ACCESS DENIED" << std::endl;
				}
				
				personInside = false;
			}	
		}
		else if(instruction.compare((std::string)"LEAVE IT") == 0)				// if the user wants to leave the house
		{
			if(userActions.size() != 3)							// check for proper formatting
			{
				std:: cout << "ERROR" << std::endl;
			}
			else
			{
				for(int i = 0; i < peopleInside.size(); i++)	// checks if the user is inside the house
				{
					if(userActions[2] == peopleInside[i])
					{
						personInside = true;
						offset = i;
						break;
					}
				}

				if(personInside)								// if the user is inside, have them leave
				{
					peopleInside.erase(peopleInside.begin() + offset);
					std::cout << "OK" << std::endl;
				}
				else
				{
					std::cout << userActions[2] << " NOT HERE" << std::endl;
				}

				personInside = false;
			}
		}
		else
		{
			std::cout << "ERROR" << std::endl;							// if instructions aren't any of the above, show error message
		}
	}

	return 0;
}
