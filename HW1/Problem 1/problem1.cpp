#include <iostream>
#include <fstream>
#include <string>
//functions
int insertIntoSortedArray(float *myArray, int numEntries, float newVal);
using namespace std;
int main(int argc, char* argv[]) {
    string fileName = argv[1];
    getline(cin,fileName);
    
    //fileName = "arr.txt";

    fstream inf(fileName,ios_base::in);
    if(inf.fail()){
        cout << "Failed to open the file." << endl;
    }
    float a;
    float nums[100];
    int i = 0;

    while(inf >> a) {
        nums[i] = a;
        i++;
    }
    
    for(int j = 0; j < i; j++){
        float *arr = &myArray[0];
        
        insertIntoSortedArray(arr, j, nums[j]);

    }
}
using namespace std;

/*code runner broke.exe*/
int lineNum = 0;
int insertIntoSortedArray(float myArray[], int numEntries, float newVal){
    float newArray[100];
    for(int i = 0; i <= numEntries; i++){
        newArray[i] = myArray[i];
    }
    
    for(int i = 0; i <= numEntries; i++){
        if(newVal >= newArray[i]){

            for(int j = numEntries + 1; j >= i; j--){
                newArray[j] = newArray[j-1];
            }
            
            newArray[i] = newVal;
            i = numEntries + 1;
            
        }
    }
    
    for(int i = 0; i <= numEntries; i++){
        myArray[i] = newArray[i];
    }
    return numEntries+1;
}

