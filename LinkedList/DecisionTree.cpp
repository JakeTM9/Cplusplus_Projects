// DecisionTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"
using namespace std;
using namespace N;

void linked_list::add(int dataToAdd)
{
    
    if (header.data == -1)
    {
        header.data = dataToAdd;
    }
    else
    {
        node* temp = header.next;
        if (temp == nullptr)
        {
            header.next = new node;
            header.next->data = dataToAdd;
            header.next->next = nullptr;
        }
        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new node;
            temp->next->data = dataToAdd;
            temp->next->next = nullptr;
        }
        
    }
    
}

void linked_list::remove(int dataToRemove) //TODO: destructors
{
    if (header.data == dataToRemove) // CASE 1 Header Remove
    {
        if (header.next == nullptr)
        {
            header.data = -1;
        }
        else
        {
            node temp;
            temp.data = header.next->data;
            temp.next = header.next->next;
            header = temp;
        }
    }
    else
    {
        node* temp = header.next;
        node* prev = new node;
        if (temp == nullptr)
        {
            cout << "Data not in Linked List" << endl;
        }
        else
        {
            if (temp->data == dataToRemove) // CASE 2 HEADER->NEXT REMOVE
            {
                temp->data = -1;
                header.next = temp->next;
                temp->next = nullptr;
            }
            else
            {
                while (temp->next != nullptr)
                {
                    if (temp->data == dataToRemove) // CASE 3 MIDDLE OF LIST 
                    {
                        temp->data = -1;
                        prev->next = temp->next;
                        temp->next = nullptr;
                        break;
                    }
                    prev = temp;
                    temp = temp->next;
                }
                if (temp->data == dataToRemove) //CASE 4 END OF LIST
                {
                    temp->data = -1;
                    prev->next = nullptr;
                    temp->next = nullptr;
                }
                else
                {
                    cout << "Data not in Linked List" << endl;
                }
            }
        }
    }
}

void linked_list::print_list()
{
    if (header.data == -1) {}
    else
    {
        cout << header.data;
        node* temp = header.next;
        if (temp == nullptr) {}
        else
        {
            while (temp->next != nullptr)
            {
                cout << ", " << temp->data;
                temp = temp->next;
            }
            cout << ", " << temp->data;
        }
    }
}

void user_interface::menu()
{
    int userInput;
    if (firstTime) 
    {
        cout << "Welcome to Hell" << endl;
        firstTime = false;
    }
    else
    {
        cout << "Welcome back to Hell" << endl;
    }
    cout << "What would you like to do: " << endl
        << "(1) Add Number to list" << endl
        << "(2) Print list" << endl
        << "(3) Remove Number from list" << endl
        << "(0) Exit" << endl;

    cin >> userInput;

    switch (userInput)
    {
        case 0:
            exit();
            break;
        case 1: 
            add();
            break;

        case 2: 
            print();
            break;

        case 3:
            remove();
            break;

        default: 
            break;
    }
}

void user_interface::exit()
{
    cout << "Come again soon" << endl;
}

void user_interface::add()
{
    int numberToAdd;
    string enterAnother;
    bool exit = false;
    while (!exit)
    {
        cout << "Enter the number to add: " << endl;
        cin >> numberToAdd;

        l.add(numberToAdd);

        cout << "Enter another number? (y/n)" << endl;
        cin >> enterAnother;

        if (enterAnother == "y") {}
        else
        {
            exit = true;
        }
    }
    menu();
}

void user_interface::print()
{
    l.print_list();
    cout << endl;
    menu();
}

void user_interface::remove()
{
    int numberToRemove;
    string enterAnother;
    bool exit = false;
    while (!exit)
    {
        cout << "Enter the number to remove: " << endl;
        cin >> numberToRemove;

        l.remove(numberToRemove);

        cout << "Remove another number? (y/n)" << endl;
        cin >> enterAnother;

        if (enterAnother == "y") {}
        else
        {
            exit = true;
        }
    }
    menu();
}

int main()
{
    user_interface UI;
    UI.menu();
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
