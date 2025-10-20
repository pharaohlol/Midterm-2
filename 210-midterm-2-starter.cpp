#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    string remove_at(int pos){
        if (!head) return "";
        int s = 0;
        Node* c = head;
        while (c) { s++; c = c->next; }
        if (pos < 0 || pos >= s) return "";
        if (pos == 0) return pop_front();
        if (pos == s-1) return pop_back();
        c = head;
        for (int i = 0; i < pos; i++) c = c->next;
        string v = c->data;
        c->prev->next = c->next;
        c->next->prev = c->prev;
        delete c;
        return v;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    string pop_front() {

        if (!head) {
            return "";
        }

        Node * temp = head;
        string v = temp->data;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        return v;
    }

    void pop_back() {
        if (!tail) {
            return "";
        }
        Node * temp = tail;
        string v = temp->data;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        return v;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    int size(){
        int c=0; Node* t=head;
        while(t){ c++; t=t->next; }
        return c;
    }
    bool empty(){
        return head==nullptr;
    }
};

vector<string> loadNames(string fn){
    vector<string> names;
    ifstream fin(fn);
    string s;
    while(getline(fin,s)){
        if(!s.empty()) names.push_back(s);
    }
    if(names.empty()){
        names={"Jean","Iris","Omar","Andy","Drew","Leah","Hope","John","Emma"};
    }
    return names;
}

string pickRand(vector<string>&v){
    return v[rand()%v.size()];
}

int main() {
    srand(time(NULL));

    vector<string> names = loadNames("names.txt");
    DoublyLinkedList line;

    cout << "Store opens:\n";
    for(int i=0;i<5;i++){
        string who = pickRand(names);
        cout<<"    "<<who<<" joins the line\n";
        line.push_back(who);
    }
    line.print();
    cout << endl;
    
    for (int t=2; t<=20; ++t){
        cout << "Time step #" << t << ":\n";
        
        line.print();
        count << endl;
    }
    return 0;
}