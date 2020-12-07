#pragma once
// my_class.h
namespace N
{
    struct node 
    {
        int data;
        node* next;
    };

    class linked_list
    {
    public:
        linked_list()       
        {
            header.data = -1;
            header.next = nullptr;
        }
        void add(int dataToAdd); //adds an element to the list
        void remove(int dataToRemove); //removes an element from the list
        void print_list(); //prints the list
        node header;
    };

    class user_interface
    {
    public:
        user_interface()
        {
            l = linked_list();
            firstTime = true;
        }
        void menu();
        void exit();
        void add();
        void print();
        void remove();

        linked_list l;

    private:
        bool firstTime;
    };

}