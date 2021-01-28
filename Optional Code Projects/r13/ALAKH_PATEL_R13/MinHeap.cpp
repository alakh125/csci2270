#include "MinHeap.hpp"
#include <limits.h>
using namespace std;

/*
Swaps two integer values
*/
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
MinHeap::MinHeap(int cap)
{
  currentSize = 0;
  capacity = cap;
  heapArr = new int[capacity];
}

/*
Finds the parent of a node, given its index.
*/
int MinHeap::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int MinHeap::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int MinHeap::rightChild(int index)
{
  return ((2*index) + 2);
}

/*
Returns the smallest element from the heap.
*/
int MinHeap::getMin()
{
  return heapArr[0];
}

/*
When an element is removed/deleted. This method make sures the array
satisfies the heap property.
*/
// TODO Complete the heapify function
void MinHeap::heapify(int i)
{
  int l = leftChild(i);
  int r = rightChild(i);
  int smallest = i;
  if(l > capacity || r > capacity){
    return;
  }
  if(heapArr[l] < heapArr[i] || heapArr[r] < heapArr[i]){
    cout << "Warning: Heap property not satisfied for node (" << heapArr[i] << ")" << endl;
  }
  heapify(l);
  heapify(r);
}

/*
Inserts an element into the heap by maintaining the heap property.
*/
void MinHeap::insertElement(int value)
{
  if(currentSize == capacity)
  {
    cout<<"Maximum heap size reached. Cannot insert anymore"<<endl;
    return;
  }

  currentSize = currentSize + 1;
  int index = currentSize - 1;
  heapArr[index] = value;

  while (index != 0 && heapArr[parent(index)] > heapArr[index])
    {
       swap(&heapArr[index], &heapArr[parent(index)]);
       index = parent(index);
    }
}

/*
Prints the elements in the heap
*/
void MinHeap::print()
{
  int iter = 0;
  while(iter < currentSize)
  {
    cout<<heapArr[iter]<<" ";
    iter = iter + 1;
  }
  cout<<endl;
}

// SILVER TODO: Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
  if (currentSize <= 0)
      return INT_MAX;

  if (currentSize == 1)
  {
      currentSize--;
      return heapArr[0];
  }
  //TODO complete the function
  //get last 2 elements (one of them is max)
  int a = 0;
  a = heapArr[currentSize-2];
  //deleteKey(a);
  if(heapArr[currentSize-1] > a){
    a = heapArr[currentSize-1];
    heapArr[currentSize-1] = -1;//replace w/ deleteKey
  }
  else{
    heapArr[currentSize-2] = -1;//replace with deleteKey
  }

  int ret = heapArr[0];
  heapArr[0] = a;
  
  bool invalidHeap = true;
  //index ints
  int parentI = 0;
  int leftI = 0;
  int rightI = 0;

  while(invalidHeap){
    leftI = leftChild(parentI);
    rightI = rightChild(parentI);
    if(heapArr[leftI] < heapArr[parentI] || heapArr[rightI] < heapArr[parentI]){
      //doesn't cover edge children same value
      if(heapArr[leftI] < heapArr[rightI]){
        swap(&heapArr[parentI],&heapArr[leftI]);
      }
      else{
        swap(&heapArr[parentI],&heapArr[rightI]);
      }
    }
    else{
      invalidHeap = false;
    }
  }
  return ret;
}

// GOLD TODO: This function deletes a key
void MinHeap::deleteKey(int key)
{

}
