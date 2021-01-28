#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct wordItem{
    int count;
    string word;    
};

//void doubleArray(wordItem* ptr, int size);
bool isStopWord(string word, string * ignoreWords);
int getTotalNumberNonStopWords(wordItem * uniqueWords, int length);
int isWord(string word, wordItem * uniqueWords, int totalWords);
void getStopWords(const char * ignoreWordFileName, string * ignoreWrods);
void arraySort(wordItem * uniqueWords, int length);
void printNext10(wordItem * wordItemList, int startRank, int totalWords);

int main(int argc, char** argv){
    int N = stoi(argv[1]);
    string inputName = argv[2];
    char * ignoreName = argv[3];
    string ignoreWords[50];
    getStopWords(ignoreName, ignoreWords);
    int size = 100;
    int doubles = 0;
    int totalWords = 0;
    int totalUniqueWords = 0;
    wordItem *uniqueWords = new wordItem[size];
    ifstream inFile(inputName);
    string temp = "";
    string str;
    int i = 0;
    while(getline(inFile,str)){
    for (char x : str){ 
        if (x == ' '){ 
            if(!isStopWord(temp,ignoreWords)){
                totalWords++;
                //cout << totalUniqueWords << " " << size << "\n\n";
                if(totalUniqueWords==size){
                    size = size * 2;
                    doubles++;
                    wordItem * newPtr = new wordItem[size];
                    for(int i = 0; i < size/2; i++){
                        newPtr[i] = uniqueWords[i];
                    }
                    delete [] uniqueWords;
                    uniqueWords = newPtr;
                }
                i = isWord(temp,uniqueWords,totalUniqueWords);
                if(i == -1){
                    wordItem w;
                    w.count = 1;
                    w.word = temp;
                    uniqueWords[totalUniqueWords] = w;
                    totalUniqueWords++;
                }
                else{
                    uniqueWords[i].count++;
                }
            } 
            temp = ""; 
        } 
        else
        { 
            temp = temp + x; 
        } 
    }
    if(!isStopWord(temp,ignoreWords)){
                totalWords++;
                if(totalUniqueWords==size){
                    size = size * 2;
                    doubles++;
                    wordItem * newPtr = new wordItem[size];
                    for(int i = 0; i < size; i++){
                        newPtr[i] = uniqueWords[i];
                    }
                    delete [] uniqueWords;
                    uniqueWords = newPtr;
                }
                i = isWord(temp,uniqueWords,totalUniqueWords);
                if(i == -1){
                    wordItem w;
                    w.count = 1;
                    w.word = temp;
                    uniqueWords[totalUniqueWords] = w;
                    totalUniqueWords++;
                }
                else{
                    uniqueWords[i].count++;
                }
    }
    }
    arraySort(uniqueWords,totalUniqueWords);
    cout << "Array doubled: " << doubles << "\n#\n";
    cout << "Unique non-common words: " << totalUniqueWords << "\n#\n";
    cout << "Total non-common words: "  << totalWords <<  "\n#\n";
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;
    printNext10(uniqueWords,N,totalWords);
}

/*void doubleArray(wordItem* ptr, int size){
    wordItem * newPtr = new wordItem[size];
    for(int i = 0; i < size; i++){
        newPtr[i] = ptr[i];
    }
    delete [] ptr;
    ptr = newPtr;
} */

void getStopWords(const char * ignoreWordFileName, string * ignoreWords){
    ifstream in(ignoreWordFileName);
    string line;
    int i = 0;
    while(getline(in,line)){
        ignoreWords[i] = line;
        i++;
    }
}

bool isStopWord(string word, string * ignoreWords){
    string ignore;
    for(int i = 0; i < 50; i++){
        ignore = ignoreWords[i];
        if(word.compare(ignore) == 0){
            return true;
        }
    }
    return false;
}

int isWord(string word, wordItem * uniqueWords, int totalWords){
    for(int i = 0; i < totalWords; i ++){
        if(word.compare(uniqueWords[i].word) == 0){
            return i;
        }
    }
    return -1;
}

int getTotalNumberNonStopWords(wordItem * uniqueWords, int length){
    int count = 0;
    wordItem word;
    for(int i = 0; i < length; i++){
        word = uniqueWords[i];
        count += word.count;
    }
    return count;
}

void arraySort(wordItem * uniqueWords, int length){
    wordItem * temp = new wordItem[length];
    wordItem w1, w2;
    for(int i = 0; i < length; i++){
        w1 = uniqueWords[i];
        for(int j = 0; j < length; j++){
            cout << length << endl;
            getchar();
            w2 = uniqueWords[j];
            if(w1.count >= w2.count){
                if(j==i){
                    temp[j] = w1;
                }
                else{
                    for(int k = i; k >= j; k--){
                        temp[k] = temp[k-1];
                    }
                    temp[j] = w1;
                }
                j = length;
            }
        }
    }
    delete [] uniqueWords;
    uniqueWords = temp;
    /*for(int i = 0; i < length; i++){
        uniqueWords[i] = temp[i];
    }*/
}

void printNext10(wordItem * wordItemList, int startRank, int totalWords){
    float prob;
    cout << fixed;
    cout << setprecision(4);
    for(int i = startRank; i < startRank + 10; i ++){
        prob = (float) (wordItemList[i]).count / totalWords;
        cout << prob << " - " << (wordItemList[i]).word << endl;
    }
}
