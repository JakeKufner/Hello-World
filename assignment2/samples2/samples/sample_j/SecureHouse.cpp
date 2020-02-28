#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

static const std::string FIREFIGHTER = "FIREFIGHTER_SECRET_KEY";

bool isCommand(std::string command, bool checkWholeCommand){
    static const std::string acceptedCommands[] = {"INSERT KEY", "TURN KEY", "WHO'S INSIDE?", "CHANGE LOCKS", "ENTER HOUSE", "LEAVE HOUSE"};
    int arrSize = sizeof(acceptedCommands)/sizeof(acceptedCommands[0]);
    for(int i = 0; i < arrSize; i++){
        if(checkWholeCommand){
            if(acceptedCommands[i] == command)
                return true;
        }else{
            if(acceptedCommands[i].find(command) != std::string::npos)
                return true;
        }

    }
    return false;
}

int countWords(std::string input, int counter = 0){
    std::string temp;
	char buf[10000];
	char buf2[13000];
	char result[14000];		
	std::size_t found = input.find(' ');

	if (found == std::string::npos)
	{
	   return counter + 1;
	}
	else
	{
	   return countWords(input.substr(found+1), counter + 1);
	}
}

void secure_house(int argc, char *argv[]){

    std::string input;
    std::string owner;
    std::string currentUsername;
    std::string currentKey;
    bool userCanEnter;
    std::vector<std::string> insideHouse;
    std::vector<std::string> currentCommand;
    std::vector<std::string> keys;

    if(argc != 1){

    owner = argv[1];

    for(int i = 2; i < argc; i++)
        keys.push_back(argv[i]);
    }

    while(std::getline(std::cin, input)){

        std::stringstream ss(input);
        std::string temp;

        std::string command;
        int commandCounter = 0;
        currentCommand.clear();

        while(std::getline(ss, temp, ' ')){

            if(commandCounter < 2){
                currentCommand.push_back(temp);

                if(commandCounter == 0){
                    int wordCount = countWords(input);
                    if(wordCount == 1){
                        std::cout << "\tERROR" << std::endl;
                        continue;
                    }
                }

                if(commandCounter == 1){

                    command = "";

                    std::vector<std::string>::iterator counter = currentCommand.begin();
                    while(counter != currentCommand.end()){
                        if(counter == currentCommand.begin()){
                            command += *counter;
                            command += ' ';
                        }else
                            command += *counter;
                        counter++;
                    }

                    currentCommand.clear();

                    if(isCommand(command, true)){
                        int wordCount = countWords(input);
                        if(wordCount < 4 && command == "INSERT KEY"){
                            std::cout << "\tERROR" << std::endl;
                            continue;
                        }else if(wordCount < 3 && (command == "TURN KEY" || command == "ENTER HOUSE" || command == "LEAVE HOUSE" || command == "CHANGE LOCKS")){
                            std::cout << "\tERROR" << std::endl;
                            continue;
                        }
                        if(command == "WHO'S INSIDE?"){
                            if(insideHouse.size() == 0)
                                std::cout << "\tNOBODY HOME" << std::endl;
                            else{
                                std::vector<std::string>::iterator counter = insideHouse.begin();
								std::cout << "\t";
                                while(counter != insideHouse.end()){
                                    if(*counter == insideHouse.rbegin()[0])
                                        std::cout << *counter << std::endl;
                                    else
                                        std::cout << *counter << ", ";
                                    counter++;
                                }
                            }
                        }
                    }else{
                        std::cout << "\tERROR" << std::endl;
                        break;
                    }
    
                }

                commandCounter++;

            }else{

                std::vector<std::string>::iterator first = keys.begin();
                std::vector<std::string>::iterator last = keys.end();
                
                if(command == "INSERT KEY"){

                    currentCommand.push_back(temp);

                    if(commandCounter == 3){
                        currentKey = currentCommand.rbegin()[0];
                        currentUsername = *currentCommand.begin();
                        std::cout << "\tKEY " << currentKey << " INSERTED BY " << currentUsername << std::endl;
                        break;
                    }

                }else if(command == "TURN KEY"){

                    currentCommand.push_back(temp);

                    if(commandCounter == 2){
                        if((std::find(first, last, currentKey) != last || currentKey == FIREFIGHTER) && currentUsername == *currentCommand.begin()){
                            userCanEnter = true;
                            std::cout << "\tSUCCESS " << currentUsername << " TURNS KEY " << currentKey << std::endl;
                            break;
                        }else{
                            std::cout << "\tFAILURE " << *currentCommand.begin() << " UNABLE TO TURN KEY " << currentKey << std::endl;
                            break;
                        }
                    }
                }else if(command == "ENTER HOUSE"){

                    currentCommand.push_back(temp);

                    if(commandCounter == 2){
                        
                        if(currentUsername != *currentCommand.begin()){
                            currentUsername = *currentCommand.begin();
                            userCanEnter = false;
                        }

                        if(userCanEnter){
                            insideHouse.push_back(currentUsername);
                            userCanEnter = false;
                            std::cout << "\tACCESS ALLOWED" << std::endl;
                            break;
                        }else{
                            std::cout << "\tACCESS DENIED" << std::endl;
                            break;
                        }
                    }
                }else if(command == "LEAVE HOUSE"){

                    currentCommand.push_back(temp);

                    if(commandCounter == 2){
                        std::vector<std::string>::iterator remove = std::find(insideHouse.begin(), insideHouse.end(), *currentCommand.begin());
                        if(remove != insideHouse.end()){
                            insideHouse.erase(remove);
                            std::cout << "\tOK" << std::endl;
                            break;
                        }else{
                            std::cout << *currentCommand.begin() << " \tNOT HERE" << std::endl;
                            break;
                        }
                    }
                }else if(command == "CHANGE LOCKS"){

                    currentCommand.push_back(temp);

                    std::vector<std::string>::iterator checkForOwner = std::find(insideHouse.begin(), insideHouse.end(), owner);

                    if(owner == *currentCommand.begin() && checkForOwner != insideHouse.end()){

                        if(commandCounter > 2)
                            keys.push_back(temp);
                        else{
                            std::cout << "\tOK" << std::endl;
                            keys.clear();
                        }

                    }else{
                        if(commandCounter == 2) 
                            std::cout << "\tACCESS DENIED" << std::endl;
                        break;
                    }

                }

                commandCounter++;

            }

        }

    }
}

int main(int argc, char *argv[]){

    secure_house(argc, argv);

    return 0;

}
