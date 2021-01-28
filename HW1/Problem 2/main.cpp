#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Park{
    std::string parkname;
    std::string state;
    int area;
};

void addPark (Park parks[], std::string parkname, std::string state, int area, int length);
void printList(const Park parks[], int length);

using namespace std;
int main(int argc, char** argv){
    string iFileName = argv[0];
    string oFileName = argv[1];
    int lowerBound = stoi(argv[2]);
    int upperBound = stoi(argv[3]);
    Park parks[100];
    
    ifstream iFile;
    iFile.open(iFileName);
    string line,parkname,state,areaTemp;
    int area;
    int i = 0;
    while(getline(iFile,line)){  
        istringstream s(line); 
        getline(s,parkname,',');
        getline(s,state,',');
        getline(s,areaTemp,',');
        area = stoi(areaTemp);
        addPark(parks,parkname,state,area,i);
        i++;
    }
    printList(parks, i);
    ofstream oFile;
    oFile.open(oFileName);
    for(int j = 0; j < i; j++){
        Park a = parks[j];
        if(a.area >= lowerBound && a.area <= upperBound){
            oFile << a.parkname << ',' << a.state << ',' << a.area << endl;
        }
    }
}

void addPark(Park parks[], string parkname, string state, int area, int length){
    Park a;
    a.parkname = parkname;
    a.state = state;
    a.area = area;
    parks[length] = a;
}

using namespace std;
void printList(const Park parks[], int length){
    for(int i = 0; i < length; i++){
        Park a = parks[i];
        cout << a.parkname << " [" << a.state << "] area: " << a.area << endl;
    }
}
