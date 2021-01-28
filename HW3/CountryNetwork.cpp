/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = NULL;
}


/*
 * Purpose: Add a new Country to the network
 * between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    Country* newCountry = new Country;
    newCountry->name = countryName;    
    if(previous == NULL){
        newCountry->next = head;
        head = newCountry;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else{
        newCountry->next = previous->next;
        previous->next = newCountry;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    insertCountry(NULL, "United States");
    Country* US = searchNetwork("United States");
    insertCountry(US, "Canada");
    Country* Canada = searchNetwork("Canada");
    insertCountry(Canada, "Brazil");
    Country* Brazil = searchNetwork("Brazil");
    insertCountry(Brazil, "India");
    Country* India = searchNetwork("India");
    insertCountry(India, "China");
    Country* China = searchNetwork("China");
    insertCountry(China, "Australia");
    Country* Aus = searchNetwork("Australia");
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country* temp = head;
    while(temp != NULL){
        if(temp->name.compare(countryName) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    bool transmit = false;
    Country* temp = searchNetwork(receiver);
    if(temp == NULL){
        if(head==NULL){
            cout << "Empty List" << endl;
        }
        else{
            cout << "Country not found" << endl;
            transmit = true; 
        }
    }
    else if(temp != NULL){
        temp = head;
        while(!transmit){
            if(temp->name.compare(receiver) == 0){
                transmit = true;
            }
            temp->message = message;
            temp->numberMessages++;
            cout << temp->name << " [# messages received: " 
                << temp->numberMessages << "] received: " << temp->message << endl;
            temp = temp->next;
           
        }  
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    Country* temp = head;
    cout << "== CURRENT PATH ==" << endl;
    if(temp != NULL){
        while(temp != NULL){
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    else{
        cout << "nothing in path" << endl;
    }
    cout << "===" << endl;
}
