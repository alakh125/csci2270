/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
using namespace std;
void displayMenu();  // declaration for main's helper-function

int main(int argc, char* argv[])
{
    CountryNetwork CountryNet;
    bool quit = false;
    while(!quit){
        displayMenu();
        string i;
        getline(cin,i);
        string country;
        string message;
        string enter;
        int in = stoi(i);
        switch (in)
        {
            case 1:
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;
            case 2:
                CountryNet.printPath();
                break;
            case 3:
                cout << "Enter name of the country to receive the message:" << endl;
                getline(cin,country);
                cout << "Enter the message to send:" << endl;
                getline(cin,message);
                cout << endl;
                CountryNet.transmitMsg(country,message);
                break;
            case 4:
                cout << "Enter a new country name:" << endl;
                getline(cin,country);
                //getchar();
                cout << "Enter the previous country name (or First):" << endl;
                getline(cin,message); //message is name of previous country
                //getchar();
                if(message.compare("First") == 0){
                    CountryNet.insertCountry(NULL,country);
                }
                else{
                    Country* prev = CountryNet.searchNetwork(message);
                    while(prev == NULL){
                        cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                        getline(cin,message);
                        prev = CountryNet.searchNetwork(message);
                    }
                    CountryNet.insertCountry(prev,country);
                }
                CountryNet.printPath();
                break;                
            case 5:
                cout << "Quitting..." << endl;
                quit = true;
                break;
            default:
                cout << "Quitting..." << endl;
                quit = true;
                break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

/*bool append(string* &str_arr, string s, int &numEntries, int &arraySize)
{
    bool doubled = false;
    if(numEntries == arraySize){
        arraySize = arraySize *2;
        string* newArr = new string[arraySize];
        for(int i = 0; i < numEntries; i++){
            newArr[i] = str_arr[i];
        }
        delete [] str_arr;
        str_arr = newArr;
        doubled = true;
    }

    str_arr[numEntries] = s;
    numEntries++;
    return doubled;
}*/
