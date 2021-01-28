#include "LinkedList.h"

using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = new Node;
    head->key = newKey;
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }

  else{

      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
  }


// TODO: SILVER PROBLEM
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n)
{
  bool isDeleted = false;

  if(head == NULL){
    cout<< "List is already empty"<<endl;
    return isDeleted;
  }

  // Special case to delete the head
    if (n == 0) {
        Node *temp = head->next;
        delete head;
        head = temp;
        isDeleted = true;
        return isDeleted;
    }
  Node *pres = head;
	Node *prev = NULL;
  int i = 0;
  for(int i = 0; i < n-1; i++){
    prev = pres;
    pres = prev->next;
  }

  prev->next = pres->next;
  delete pres;
  pres = prev->next;
  isDeleted = true;

	return isDeleted;
}

// TODO: GOLD PROBLEM
// Swap the first and last nodes (don't just swap the values)
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;

    if(head == NULL) {
        cout << "List is empty. Cannot swap" << endl;
        return false;
    }

    Node *tail = head->next;
    if(tail == NULL){
      cout<<"Failed"<<endl;
      return false;
    }
    if(tail->next == NULL){
      Node *temp = head;
      head = tail;
      head->next = temp;
      tail = temp;
      tail->next = NULL;
      return true;
    }
    Node *temp = tail;
    while(tail->next != NULL){
      temp = tail;
      tail = tail->next;
    }

    Node *hTemp = head;
    Node *tTemp = tail;
    temp->next = hTemp;
    tTemp->next = head->next;
    hTemp->next = NULL;

    tail = hTemp;
    head = tTemp;
    cout << tail->key << " " << head->key << endl;
    cout << tail->next << " " << head->next << endl;

    // TODO (take care of the edge case when your linkedlist has just 2 nodes)
    isSwapped = true;
    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;
  int i = 0;

  while(temp->next != NULL ){
    cout<< temp->key <<" -> ";
    temp = temp->next;
    i++;

   // cout<< i<<endl;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}
