#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

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
    void insert_after(string /*value*/, int /*position*/) { } // for the ones i have done a comment on i dont think i need them, i was thinking about deleting them but i just subed it out to make them exists.
    void delete_val(string /*value*/) { }
    void delete_pos(int /*pos*/) { }

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
        if (!head) return "";
        Node * temp = head;
        string v = temp->data;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
        return v;
    }

    string pop_back() {
        if (!tail) return "";
        Node * temp = tail;
        string v = temp->data;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
        return v;
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
    bool empty(){ return head==nullptr; }
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

        int p = rand()%100+1;
        if(!line.empty() && p<=40){
            string w=line.pop_front();
            cout<<"    "<<w<<" is served\n";
        }

        p = rand()%100+1;
        if(p<=60){
            string w=pickRand(names);
            line.push_back(w);
            cout<<"    "<<w<<" joins the line\n";
        }

        p = rand()%100+1;
        if(!line.empty() && p<=20){
            string w=line.pop_back();
            cout<<"    "<<w<<" (at the rear) left the line\n";
        }

        p = rand()%100+1;
        if(line.size()>=2 && p<=10){
            int idx = rand()%(line.size()-1);
            string w=line.remove_at(idx);
            cout<<"    "<<w<<" left the line\n";
        }

        p = rand()%100+1;
        if(p<=10){
            string w=pickRand(names);
            line.push_front(w);
            cout<<"    "<<w<<" (VIP) joins the front of the line\n";
        }

        line.print();
        cout << endl;
    }

    return 0;
}