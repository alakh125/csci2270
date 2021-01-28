/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
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
/* finished. do not touch. */
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        //case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    }else{
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    if(head == NULL){
        cout << "List is empty;" << endl;
    }
    else if(head->name.compare(countryName) == 0){
        Country* temp = head ->next;
        delete head;
        head = temp;
    }
    else{
        bool found = false;
        Country *prev = head;
        Country *curr = head->next;
        while (curr != NULL & found == false){
            if (curr->name.compare(countryName) == 0){
                prev->next = curr->next;
                delete curr;
                found = true;
            }
            if(!found){
                prev = curr;
                curr = curr->next;
            }
        }
        if(!found){
            cout << "Country does not exist." << endl;
        }
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for(int i = 0; i < num_countries; i++)
    {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
// Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
* Purpose: Creates a loop from last node to the country specified.
* @param countryName name of the country to loop back
* returns pointer to last node before loop creation (to break the loop)
*/
Country* CountryNetwork::createLoop(string countryName)
{
    Country * curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = searchNetwork(countryName);
    return curr;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
    while(head != NULL){
        cout << "deleting: " << head->name << endl;
        deleteCountry(head->name);
    }
    cout << "Deleted network" << endl;
}

/*
*Purpose: to detect loop in the linkedlist
* @param
* returns true if loop is detected. Otherwise return false.
*/
bool CountryNetwork::detectLoop() {
    if(head == NULL){
        return false;
    }
    Country* fast = head->next;
    Country* slow = head;
    while(fast != NULL && fast->next != NULL){
        if(fast == slow){
            return true;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    return false;
}

/*
* Purpose: Take the chunk of nodes from start index to end index
*          Move that chunk at the end of the List
*@param: start index
*@param: end index
* return none
*/
void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    if(start_index > end_index){
        cout << "Invalid indices" << endl;
    }
    else if(head == NULL){
        cout << "Linked List is Empty" << endl;
    }
    else{
        int i = 0;
        Country* curr = head;
        Country* start;
        Country* end;
        Country* before;
        Country* after;
        Country* tail;
        for(i = 0; i < start_index-1; i++){
            curr = curr->next;
        }
        before = curr;
        curr = curr->next;
        start = curr;
        bool run = true;
        for(i = i; i < end_index-1; i++){
            curr = curr->next;
            if(curr->next == NULL){
                cout<<"Invalid end index" << endl;
                i = end_index;
                run = false;
            }
        }
        if(run){
            end = curr;
            curr = curr->next;
            after = curr;
            while(curr->next != NULL){
                curr = curr-> next;
            }
            tail = curr;
            if(start_index == 0){
                start = head;
                head = after;
            }
            else{
                before->next = after;
            }
            tail->next = start;
            end->next = NULL;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
