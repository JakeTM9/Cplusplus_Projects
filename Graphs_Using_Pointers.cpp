// Homework3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Graph {
    public:
        Graph(); //constructor empty
        ~Graph(); //destructor
        Graph(int userInputNumVerticies, vector <int> userInputVerticies); // constructor from user Input
        void addEdge(int source, int destination); //Adds an Edge to its respective header Node
        void deleteEdge(int source, int destination); //Deletes an Edge to its respective header Node
        void printRelations(); //Prints all relations of Graph
        int numVerticies; //number of verticies
        vector <Node*> headers; // array of header nodes
};

Graph::Graph() {
    numVerticies = 0;
    headers = {};
};

Graph::Graph(int userInputNumVerticies, vector <int> userInputVerticies) {
    numVerticies = userInputNumVerticies;
    //Assigns header nodes
    for (int i = 0; i < numVerticies; i++) {
        Node* tmp = new Node;
        tmp->data = i;
        tmp->next = nullptr;
        headers.push_back(tmp);
    }
    //Adds all user Input Edges
    for (int i = 0; i < userInputVerticies.size(); i += 2) {
        addEdge(userInputVerticies.at(i), userInputVerticies.at(i + 1));
    }
};

void Graph::addEdge(int source, int destination) {
    //adds a destination node to the end of its respective source header node
    Node* toAdd = new Node;
    toAdd->data = destination;
    toAdd->next = nullptr;
    //iterates "last" through linked list to the end
    Node* last = headers.at(source);
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = toAdd;
}

void Graph::deleteEdge(int source, int destination) {
    //deletes a destination node from the location of its respective source header node's LL
    Node* toDelete = headers.at(source)->next;
    Node* prev = NULL;
    //In case of first element
    if (toDelete != NULL && toDelete->data == destination) {
        //preserve chain and delete
        headers.at(source)->next = toDelete->next;
        delete toDelete;
        return;
    }
    else {
        //Iterates through until found
        while (toDelete != NULL && toDelete->data != destination) {
            prev = toDelete;
            toDelete = toDelete->next;
        }
        //in case not found
        if (toDelete == NULL) { return; }
        //preserve chain and delete
        prev->next = toDelete->next;
        delete toDelete;
    }
}

void Graph::printRelations() {
    //for each entry in adjacency list, prints all its relations
    for (int i = 0; i < headers.size(); i++) {
        Node* tmp = headers.at(i);
        while (tmp->next != nullptr) {
            cout << "( " << i << " , " << tmp->next->data << " ) ";
            tmp = tmp->next;
        }
        cout << endl;
    }
}

Graph::~Graph() {
    //deletes every Node (every object created with new must be destroyed manually with delete)
    if (headers.size() > 0) { //prevents error on program end
        for (int i = 0; i < numVerticies; i++) {
            Node* tmp = headers.at(i);
            Node* next;
            while (tmp != NULL) {
                next = tmp->next;
                delete tmp;
                tmp = next;
            }
        }
        cout << "graph deleted" << endl;
    }
}

void recursiveDFS(int v, vector<bool>& visited, vector<Node*> headers) {
    visited.at(v) = true;
    Node* destinations = headers.at(v);
    //iterate through all destinations looking for a vertex not visited
    while (destinations->next != nullptr) {
        if (!visited.at(destinations->next->data)) {
            recursiveDFS(destinations->next->data, visited, headers);
        }
        destinations = destinations->next;
    }
}

void DFS(Graph G, int start)
{
    //initialize visited array before calling recursive DFS
    vector<bool> visited(G.numVerticies, false);
    recursiveDFS(start, visited, G.headers);
}

int main()
{
    //HANDLES INPUT OF NUMBERS TO BE VERTICES AND NUM VERTICIES
    string userInput;
    vector <int> userInputVector;
    vector <int> verticies;
    int numVerticies;
    bool validChoice = false;
    while (!validChoice) {
        cout << "Enter number of verticies [n] followed by a sequence of pairs [i] [j] delimited by spaces where i and j are integers between 0 and n-1\n";
        getline(cin, userInput);
        istringstream T(userInput);
        int number{};
        while (T >> number)
        {
            userInputVector.push_back(number);
        }
        numVerticies = userInputVector.at(0);
        for (int i = 1; i < userInputVector.size(); i++) {
            if (userInputVector.at(i) < 0) { break; } // for if negative integer signals end of input, regardless of location
            verticies.push_back(userInputVector.at(i));
        }
        validChoice = true;
    }
    Graph G = Graph(numVerticies, verticies);
    //put intital run code above with the big string and intial prints and whatnot
    bool Exit = false;
    int userChoice;
    int source;
    int destination;
    while (!Exit) {
        cout << endl << "Please Enter the number cooresponding with what you want to do" << endl;
        cout << "(1) Add an edge" << endl;
        cout << "(2) Delete an edge" << endl;
        cout << "(3) Print Relations" << endl;
        cout << "(4) Print Components" << endl;
        cout << "(0) Exit" << endl;
        cin >> userChoice;
        cout << endl;
        
        switch (userChoice) {
            case 0:
                Exit = true;
                break;
            case 1:
                cout << "Enter source [i]:" << endl;
                cin >> source;
                cout << endl << "Enter destination [j]:" << endl;
                cin >> destination;
                //addEdge(source,destination);
                cout << endl << "Done" << endl;
                break;
            case 2:
                cout << "Enter source [i]:" << endl;
                cin >> source;
                cout << endl << "Enter destination [j]:" << endl;
                cin >> destination;
                //deleteEdge(source,destination);
                cout << endl << "Done" << endl;
                break;
            case 3:
                cout << "Printing relations....." << endl;
                //printRelations();
                break;
            case 4:
                cout << "Printing components......." << endl;
                //components();
                break;
            default:
                cout << "Input not recognized, please try again" << endl;
                break;
        }
    }
    //TODO code interface and do components
    /*
    G.deleteEdge(3, 0);
    G.printRelations();
    G.~Graph();*/
}
