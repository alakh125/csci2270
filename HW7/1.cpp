#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

MovieTree::~MovieTree()
{

}

TreeNode * printHlp(TreeNode * m)
{
    if(m == NULL)
    {
        return NULL;
    }
    else
    { 
        printHlp(m->leftChild);
        cout << "Movies starting with letter: " << m->titleChar << endl;
        while(m->head != NULL)
        {
            cout << " >> " << m->head->title << " " << m->head->rating << endl;
            m->head = m->head->next;
        }
        printHlp(m->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
        printHlp(root);
}

TreeNode * addHlp(TreeNode * currNode, TreeNode * parent, int ranking, string title, int year, float rating)
{
    if(currNode == NULL)
    {
    
      TreeNode * newNode = new TreeNode;
      newNode->titleChar = title[0];
      
      newNode->leftChild = NULL;
      newNode->rightChild = NULL;

      newNode->parent = parent;
      
      // Root LL
      LLMovieNode * newMovie = new LLMovieNode(ranking, title, year, rating);
      newNode->head = newMovie;
      newMovie->ranking = ranking;
      newMovie->title = title;
      newMovie->year = year;
      newMovie->year = year;
      return newNode;
    }
    else if(title[0] > currNode->titleChar)
    {
        currNode->rightChild = addHlp(currNode->rightChild, currNode, ranking, title, year, rating);
    }
    else if(title[0] < currNode->titleChar)
    {
        currNode->leftChild = addHlp(currNode->leftChild, currNode, ranking, title, year, rating);
    }
    return currNode;
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    // If the title char node DNE
    if(searchChar(title[0]) == NULL)
    {
        root = addHlp(root, root, ranking, title, year, rating);
    }
    // If the title char already exists
    else
    {
        LLMovieNode * newMovie = new LLMovieNode(ranking, title, year, rating);
        newMovie->ranking = ranking;
        newMovie->title = title;
        newMovie->year = year;
        newMovie->rating = rating;
        
        // Alphabetical order
        
        LLMovieNode * temp = new LLMovieNode;
        temp = (searchChar(title[0]))->head;
        
        // If it first alphabetically
        if(title.compare(temp->title) < 0)
        {
            LLMovieNode * temp2 = new LLMovieNode; // Stores head
            temp2 = (searchChar(title[0]))->head;
            (searchChar(title[0]))->head = newMovie;
            newMovie->next = temp2;
        }
        else
        {
            while(title.compare(temp->title) > 0 && temp->next != NULL)
            {
                temp = temp->next;
            }
            // If it is at the end
            if(temp->next == NULL)
                temp->next = newMovie;
            else
            {
                temp = (searchChar(title[0]))->head;
                while(title.compare(temp->title) > 0 && title.compare(temp->next->title) < 0)
                {
                    temp = temp->next;
                }
                newMovie->next = temp->next->next;
                temp->next->next = newMovie;
            }
        }
    }
}

void MovieTree::deleteMovie(std::string title)
{

}

void MovieTree::leftRotation(TreeNode* curr)
{

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