#include <iostream>
#include <string>

using namespace std;

class List {
    private:
        string * list;
        int size;
        int capacity;
    public:
        List();
        ~List();
        void insert(string data, int index);
        void traverse();
};
List::List(){
    cout<<"Constructor Called"<<'\n';
    list = new string[1000];
    size = 0;
    capacity = 1000;
}
List::~List(){
    delete[] list;
    list = 0;
}
void List::insert(string data, int index){
    if(index > size){
        cout << "operation not allowed" << '\n';
    }
    else{
        list[index] = data;
    }
}
void List::traverse(){
    for(int i = 0; i < size; i++){
        cout<< list[i] << '\n';
    }
}

int main(){
    List l;
    l.insert("bruh", 0);
    l.insert("yeet",1);
    l.traverse;
    l.~List;
}