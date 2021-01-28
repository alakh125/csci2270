#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void deleteLinkedList(TreeNode *tn)
{
    while(tn->head != NULL)
    {
        LLMovieNode *llHead = tn->head;
        tn->head = tn->head->next;
        delete llHead;
    }
}

void recursiveDestruct(TreeNode *tn)
{
    if(tn->leftChild == NULL && tn->rightChild == NULL)
    {
        deleteLinkedList(tn);
        delete tn;
        return;
    }
    else
    {
        if(tn->leftChild != NULL) recursiveDestruct(tn->leftChild);
        if(tn->rightChild != NULL) recursiveDestruct(tn->rightChild);
        deleteLinkedList(tn);
        delete tn;
    }

}
MovieTree::~MovieTree()
{
    if(root != NULL) recursiveDestruct(root);
}

void recursivePrintInventory(TreeNode* t)
{
    if(t == NULL)
    {
        return;
    }
    else
    {
        recursivePrintInventory(t->leftChild);
        cout << "Movies starting with letter: " << t->titleChar << endl;
        LLMovieNode* temp = t->head;
        while(temp != NULL)
        {
            cout << " >> " << temp->title << " " << temp->rating << endl;
            temp = temp->next;
        }
        recursivePrintInventory(t->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    recursivePrintInventory(root);
    return;
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    char tChar = title[0];
    if(root == NULL)
    {
        TreeNode* newNode = new TreeNode;
        newNode->titleChar = tChar;
        root = newNode;
    }
    if(searchChar(tChar) == NULL)
    {
        //recursiveAddTreeNode(root, tChar);
        TreeNode* temp = root;
        bool run = true;
        while((temp->leftChild != NULL || temp->rightChild != NULL) && run)
        {
            if(tChar < temp->titleChar && temp->leftChild != NULL) temp = temp->leftChild;
            else if(tChar > temp->titleChar && temp->rightChild != NULL) temp = temp->rightChild;
            else run = false;
        }
        if(tChar < temp->titleChar)
        {
            TreeNode* newNode = new TreeNode;
            temp->leftChild = newNode;
            newNode->titleChar = tChar;
            newNode->parent = temp;
        }
        if(tChar > temp->titleChar)
        {
            TreeNode* newNode = new TreeNode;
            temp->rightChild = newNode;
            newNode->titleChar = tChar;
            newNode->parent = temp;
        }
    }
    if(searchChar(tChar)->head == NULL)
    {
        LLMovieNode *newNode = new LLMovieNode(ranking, title, year, rating);
        searchChar(tChar)->head = newNode;
        return;
    }
    LLMovieNode *temp = searchChar(tChar)->head;
    if(title.compare(temp->title) < 0)
    {
        LLMovieNode *newNode = new LLMovieNode(ranking, title, year, rating);
        newNode->next = temp;
        searchChar(tChar)->head = newNode;
        return;
    }
    bool run2 = true;
    while(temp->next != NULL && run2) //find the node before inserted node
    {
        if(title.compare((temp->next)->title) > 0) temp = temp->next;
        else run2 = false;
    }
    LLMovieNode *newNode = new LLMovieNode(ranking, title, year, rating);
    newNode->next = temp->next;
    temp->next = newNode;
    return;
}

void MovieTree::deleteMovie(string title)
{
    //locate movie node in tree
    char fChar = title[0];
    bool found = false;
    TreeNode * t = searchChar(fChar);

    //movie first char not found
    if(root == NULL){
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }
    else if(t==NULL){
        LLMovieNode *tLL = t->head;
        delete tLL;
        return;
    }
    LLMovieNode * Curr = t->head;
    LLMovieNode * Prev = t->head;
    //sort LL for node
    found = false;
    int count = 0;
    while(!found && Curr != NULL){
        count++;
        if(title.compare(Curr->title) == 0){
            found = true;
        }
        else{
            Curr = Curr->next;
            if(count > 1){
                Prev = Prev->next;
            }
        }
    }
    if(count > 1){
        //delete from LL if multiple nodes in LL
        Prev->next = Curr->next;
        delete Curr;
        return;
    }
    else if(t->head->next != NULL){
        LLMovieNode * temp = t->head->next;
        t->head = temp;
        return;
    }
    if(t->head->title != ""){
        LLMovieNode *tLL = t->head;
        delete tLL;
    }
    else{
        root = NULL;
        t = NULL;
        return;
    }
    if(t->leftChild == NULL && t->rightChild == NULL){
        if(t!=root){
            if(t->parent->titleChar > t->titleChar){
                t->parent->leftChild = NULL;
            }
            else{
                t->parent->rightChild = NULL;
            }
        }
        else{
            root = NULL;
        }
    }    
    else if(t->leftChild == NULL){
        TreeNode * temp = t->rightChild;
        if(t == root){
            root->rightChild = temp->rightChild;
            root->head = temp->head;
            //root->leftChild = t->leftChild;
            root->titleChar = temp->titleChar;
        }
        else{
            TreeNode * parent = t->parent;
            if(parent->titleChar > t->titleChar){
                parent->leftChild->head = temp->head;
                //parent->leftChild->leftChild = temp->leftChild;
                parent->leftChild->rightChild = temp->rightChild;
                parent->leftChild->titleChar = temp->titleChar;
            }
            else{
                parent->rightChild->head = temp->head;
                //parent->rightChild->leftChild = temp->leftChild;
                parent->rightChild->rightChild = temp->rightChild;
                parent->rightChild->titleChar = temp->titleChar;
            }
        }
    }
    else if(t->rightChild == NULL){
        TreeNode * temp = t->leftChild;
        if(t == root){
            //root->rightChild = temp->rightChild;
            root->head = temp->head;
            root->leftChild = temp->leftChild;
            root->titleChar = temp->titleChar;
        }
        else{
            TreeNode * parent = t->parent;
            if(parent->titleChar > t->titleChar){
                parent->leftChild->head = temp->head;
                parent->leftChild->leftChild = temp->leftChild;
                //parent->leftChild->rightChild = temp->rightChild;
                parent->leftChild->titleChar = temp->titleChar;
            }
            else{
                parent->rightChild->head = temp->head;
                parent->rightChild->leftChild = temp->leftChild;
                //parent->rightChild->rightChild = temp->rightChild;
                parent->rightChild->titleChar = temp->titleChar;
            }
        }
    }
    else{
        //find least in right subtree
       TreeNode * temp = t->rightChild;
        while(temp->leftChild != NULL){
            temp = temp->leftChild;
        }
        if(t == root){
            root->rightChild = t->rightChild;
            root->head = temp->head;
            root->leftChild = t->leftChild;
            root->titleChar = temp->titleChar;
        }
        else{
            TreeNode * parent = t->parent;
            if(parent->titleChar > t->titleChar){
                parent->leftChild->head = temp->head;
                parent->leftChild->leftChild = temp->leftChild;
                parent->leftChild->rightChild = temp->rightChild;
                parent->leftChild->titleChar = temp->titleChar;
            }
            else{
                parent->rightChild->head = temp->head;
                parent->rightChild->leftChild = temp->leftChild;
                parent->rightChild->rightChild = temp->rightChild;
                parent->rightChild->titleChar = temp->titleChar;
            }
        }
        temp->parent->leftChild = temp->rightChild;
        delete temp;
    }
    delete t;
}

void MovieTree::leftRotation(TreeNode* curr)
{
    // Parent of x becomes the parent of y
    //TreeNode * temp = curr;
    //TreeNode * rChild = curr->rightChild;
    //TreeNode * lChild = curr->leftChild;
    TreeNode * currParent = curr->parent;

    // If curr is the root
    if(root == curr)
    {

        TreeNode * temp2 = curr->rightChild;
        //delete [] curr->rightChild;


        curr->rightChild = temp2->leftChild;


        root = temp2;

        temp2->leftChild = curr;

        curr->parent = temp2;
        root->parent = NULL;

    }
    // If curr was originally right
    else if(currParent->rightChild == curr)
    {
        TreeNode * temp2 = curr->rightChild;
        //delete [] curr->rightChild;

        curr->rightChild = temp2->leftChild;

        curr->parent->rightChild = temp2;

        temp2->leftChild = curr;
        temp2->parent = curr->parent;
        curr->parent = temp2;

    }
}
//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}
