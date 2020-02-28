#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char *argv[]) {
    string* owner = NULL;
    string* userKey = NULL;
    string* secretKey = new string("FIREFIGHTER_KEY");
    vector<string> keys;
    vector<string> authorized;
    vector<string> occupants;
    string a = "KEY INSERT";
    string b = "KEY TURN";
    string c = "HOUSE ENTER";
    string d = "WHO'S INSIDE?";
    string e = "LOCKS CHANGE";
    string f = "HOUSE LEAVE";

    // assign owner
    owner = new string(argv[1]);

    // assign authorized keys
    for (int i = 2; i < argc; ++i)
        keys.emplace_back(argv[i]);
    // keys.emplace_back("foobar");

    string input = "";
    while(getline(cin, input)) {

        if(input.find(a) != string::npos) { // KEY INSERT <user_name> <key>
            size_t pos = input.find(a);
            string temp = input.substr(pos+11);
            pos = temp.find(" ");
            *userKey = temp.substr(pos+1);
            char str[temp.length()];
            for (int i = 0; i < sizeof(str); i++) {
                str[i] = temp[i];
            }
            char* user = strtok(str, " ");

            // KEY <key> INSERTED BY <username>
            cout << "KEY " << *userKey << " INSERTED BY ";
            printf("%s", user);
            cout << "\n";

        } else if(input.find(b) != string::npos) { // KEY TURN <user_name>
            size_t pos = input.find(b);
            string user = input.substr(pos+9);
            if (find(keys.begin(), keys.end(), *userKey) != keys.end() || *userKey == *secretKey) {
                cout << "SUCCESS " << user << " TURNS KEY " << *userKey << endl;
                authorized.emplace_back(user);
            } else {
                cout << "FAILURE " << user << " UNABLE TO TURN KEY " << *userKey << endl;
            }
        } else if(input.find(c) != string::npos) { // HOUSE ENTER <user_name>
            size_t pos = input.find(b);
            string user = input.substr(pos+13);
            if (find(authorized.begin(), authorized.end(), user) != authorized.end()) {
                cout << "ACCESS ALLOWED" << endl;
                occupants.emplace_back(user);
            } else {
                cout << "ACCESS DENIED" << endl;
            }
        } else if(input.find(d) != string::npos) { // WHO'S INSIDE?
            if(occupants.empty()) {
                cout << "NOBODY HOME" << endl;
            } else {
                ostringstream ss;
                copy(occupants.begin(), occupants.end() - 1, ostream_iterator<string>(ss, ", "));
                ss << occupants.back();

                cout << ss.str() << "\n";
            }
        } else if(input.find(e) != string::npos) { // LOCKS CHANGE <user_name> <key_1> <key_2> ... <key_n>
            size_t pos = input.find(b);
            string temp = input.substr(pos+13);
            char str[temp.length()];
            for (int i = 0; i < sizeof(str); i++) {
                str[i] = temp[i]; // <user_name> <key_1> <key_n>
            }
            char* user = strtok(str, " ");
            string username = user;

            // check if username is owner and if owner is inside home
            if (find(occupants.begin(), occupants.end(), *owner) != occupants.end() && username.compare(*owner) == 0) {
                keys.clear();
                pos = temp.find(" ");
                string temp2 = temp.substr(pos+1);
                stringstream ss(temp2);
                string token;

                while(getline(ss, token, ' ')) {
                    keys.emplace_back(token);
                }
                cout << "OK" << endl;
            } else {
                cout << "ACCESS DENIED" << endl;
            }
        } else if(input.find(f) != string::npos) { // HOUSE LEAVE <user_name>
            size_t pos = input.find(a);
            string user = input.substr(pos+13);
            if (find(occupants.begin(), occupants.end(), user) != occupants.end()) {
                occupants.erase(std::remove(occupants.begin(), occupants.end(), user), occupants.end());
                cout << "OK" << endl;
            } else {
                cout << user << " NOT HERE" << endl;
            }
        } else {
            cout << "ERROR" << endl;
        }
    }
    return 0;
}
