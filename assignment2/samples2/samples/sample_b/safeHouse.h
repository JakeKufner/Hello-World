#include <iostream>
#include <vector> 

using namespace std;

class House {

private:
    // states: 1=locked, 2= key insert, 3= key turned, 4= unlocked
    int lock_state;
    string owner;
    vector<string> keys;
    vector<string> owner_n_key;
    vector<string> waiting_outside;

public:
    vector<string> people_inside;
    
    House(string o)
    {
        lock_state = 1;
        owner = o;
        keys.push_back("POLICE_SECRET_KEY");
        owner_n_key.push_back("NULL");
    }
    string return_owner()
    {
        return owner;
    }
    void reKey(vector<string> vs)
    {
        keys.clear();
        keys = vs;
    }
    void remove_person(string p)
    {
        int pos = -1;
        for(int x = 0; x < people_inside.size(); x++)
        {
            if (p == people_inside.at(x))
            {
			   people_inside.erase( people_inside.begin() + pos);
			   break;
            }
        }
    }
    bool is_inside(string s)
    {
        bool yes = false;
        for(int i = 0; i < people_inside.size(); i++)
        {
            if (s == people_inside.at(i))
                yes = true;
        }

        return yes;
    }
    void add_key(string keyx)
    {
        keys.push_back(keyx);
    }
    void print_keys()
    {
        vector<string>::iterator it;
        for( it = keys.begin(); it != keys.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    void owner_and_key(string o, string k)
    {
        // new key in lock. replaced the old one
        owner_n_key.clear();
        owner_n_key.push_back(o);
        owner_n_key.push_back(k);

        // state of lock changed
        lock_state = 2; 
    }
    vector<string> return_OAK()
    {
        return owner_n_key; 
    }
    bool validate(string k)
    {
        bool isKey = false;
        vector<string>::iterator it;
        for( it = keys.begin(); it != keys.end(); it++)
        {
            if (k == *it)
                isKey = true;
        }
        
        return isKey;
    }
    void waitingOutside(string wo)
    {
        waiting_outside.push_back(wo);
    }
    bool had_valid_key(string check)
    {
        bool letInside = false;
        int it; 
        
        for( it = 0; it != waiting_outside.size(); it++)
        {
            if (check == waiting_outside.at(it) )
                letInside = true;
        }
        
        return letInside;
    }
};
void program(House *SH);

enum all_commands {
    INSERT, TURN, ENTER,
     WHOS, CHANGE, LEAVE, ERROR
};

all_commands toEnum(string e)
{
    if (e == "INSERT"){ return INSERT; }
    if (e == "TRN"){ return TURN; }
    if (e == "ENTER"){ return ENTER; }
    if (e == "WHO'S"){ return WHOS; }
    if (e == "CHNG"){ return CHANGE; }
    if (e == "LEAVE"){ return LEAVE; }

    return ERROR;
}
