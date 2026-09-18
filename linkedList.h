#include <iostream>
#include <fstream> //Gives us ifstream and ofstream for reading and writing files.
#include <string>  //gves us the string data type.
using namespace std;

template <class T> //So that the linked list can store different data types.


class linkedList
{
private:
    class node
    {
    public:
        T data;     //To store the value
        node *next;  //Pointer to the next node.

        node(T x)
        {
            data = x;  //Stores x in the node's data.
            next = nullptr; //The new node does not point to another node yet.

        }
    };

    node *head;    //Pointer to the first node in the linked list.
    node *tail;    //Pointer to the last node in the linked list.


public:
    //Constructor.
    //Creates an empty linked list.
    //Runtime O(1) --->  because we only initialize two pointers.
    linkedList()
    {
        //The list starts with no first and last node.
        head = nullptr;
        tail = nullptr;
    }

    //Destructor.
    //Deletes all the nodes when the linked list is destroyed.
    //Runtime O(n) --> because we visit every node once.
    ~linkedList()
    {
        //Continue while there are still nodes in the list.
        while(head != nullptr)
        {
            //Save the next node before deleting the current node.
            node *temp = head->next;
            delete head;                //Delete the current first node.
            head = temp;                //Move head to the next node.

        }

        //The list is now empty, so tail is also nullptr.
        tail = nullptr;
    }

    //Adds a new item to the back of the list.
    //Runtime O(1) --> because tail already points to the last node.
    void push_back(T x)
    {
        //Create a new node containing x.
        node *n = new node(x);

        //if list is empty.
        if(head == nullptr)
        {
            //the new node is the head AND tail 
            head = n;
            tail = n;
        }
        else
        {
            // Make the old last node point to the new node.
            tail->next = n;
            //Tail is now the new last node.
            tail = n;
        }
    }

    //Prints all the items in the linked list.
    //Runtime O(n) --> because every node must be visited.
    void print()
    {
        //Start at the first node.
        node *current = head;

        //Continue until there are no more nodes.
        while(current != nullptr)
        {
            //Print the data stored in the current node.
            cout << current->data << " ";

            //Move to the next node.
            current = current->next;
        }

        //Move to the next line after printing the list.
        cout << endl;
    }

    //Splits this linked list into two linked lists.
    //The left list gets the extra item if the size is odd.
    //The original list becomes empty.
    //Runtime O(n) --> because we go through the list a constant number of times.
    void split(linkedList<T> &left, linkedList<T> &right)
    {
        //Variable to count the number of nodes.
        int count = 0;
        //Start at the first node.
        node *current = head;

        //Go through the entire list.
        while(current != nullptr)
        {
            //Increase the node count by one.
            count++;
            //Move to the next node.
            current = current->next;
        }

        //Calculate how many nodes should go into the left list
        //Add 1 (makes the left list receive the extra item when count is odd)
        int leftSize = (count + 1) / 2;

        //Start again at the beginning of the original list.
        current = head;

        //Add the first half of the items to left.
        for(int i = 0; i < leftSize; i++)
        {
            //Copy the current item's data into the left list.
            left.push_back(current->data);
            //Move to the next node.
            current = current->next;
        }

        //Add all remaining items to the right list.
        while(current != nullptr)
        {
            //Copy the current item's data into the right list.
            right.push_back(current->data);
            //Move to the next node.
            current = current->next;
        }

        / Delete the original list.
        while(head != nullptr)
        {
            // Save the next node before deleting the current node.
            node *temp = head->next;
            delete head;
            // Move head to the next node.
            head = temp;
        }

        //The original list is empty
        tail = nullptr;
    }

    //Sorts the list using selection sort.
    //Runtime O(n^2) --> because we repeatedly search through the remaining nodes.
    void slowSort()
    {
        //Start at the first node.
        node *current = head;

        // Continue until we reach the end of the list.
        while(current != nullptr)
        {
            //Assume the current node contains the smallest value.
            node *smallest = current;
            //Start searching at the node after current
            node *search = current->next;

            //Search the rest of the list for a smaller value
            while(search != nullptr)
            {
                //Check if searched value is smaller
                if(search->data < smallest->data)
                {
                    smallest = search;
                }
                // Move to the next node.
                search = search->next;
            }

            //used to swap the two values.
            T temp = current->data;

            //Put the smallest value into the current node.
            current->data = smallest->data;
            //Put the old current value into the smallest node.
            smallest->data = temp;
            //Move to the next position in the list.
            current = current->next;
        }
    }



