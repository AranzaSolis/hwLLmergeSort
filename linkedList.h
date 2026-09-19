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

        //Delete the original list.
        while(head != nullptr)
        {
            //Save the next node before deleting the current node.
            node *temp = head->next;
            delete head;
            //Move head to the next node.
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

    //Combines two sorted linked lists into this linked list.
    //left and right become empty after the merge.
    //Runtime O(n) --> because every item is processed once.
    void merge(linkedList<T> &left, linkedList<T> &right)
    {
        //Start at the beginning of the left list.
        node *leftCurrent = left.head;
        // Start at the beginning of the right list.
        node *rightCurrent = right.head;


        //Continue while both lists still contain items.
        while(leftCurrent != nullptr && rightCurrent != nullptr)
        {
            //Check which current value is smaller.
            if(leftCurrent->data <= rightCurrent->data)
            {
                //Add the smaller left value to this list.
                push_back(leftCurrent->data);
                //Move to the next node in the left list.
                leftCurrent = leftCurrent->next;
            }
            else
            {
                //Add the smaller right value to this list.
                push_back(rightCurrent->data);
                //Move to the next node in the right list.
                rightCurrent = rightCurrent->next;
            }
        }

        //Add any remaining items from the left list.
        while(leftCurrent != nullptr)
        {
            //Add the remaining left value.
            push_back(leftCurrent->data);
            //Move to the next left node.
            leftCurrent = leftCurrent->next;
        }

        //Add any remaining items from the right list.
        while(rightCurrent != nullptr)
        {
            //Add the remaining right value.
            push_back(rightCurrent->data);
            // Move to the next right node.
            rightCurrent = rightCurrent->next;
        }

        //Delete left list.
        while(left.head != nullptr)
        {
            //Save the next left node.
            node *temp = left.head->next;
            //delete old head assign the new head
            delete left.head;
            left.head = temp;
        }
        //Left is empty.
        left.tail = nullptr;

        //Delete right list
        while(right.head != nullptr)
        {
            //Save the next right node.
            node *temp = right.head->next;
            //delete old head assign the new head            
            delete right.head;
            right.head = temp;
        }
        // Right is empty.
        right.tail = nullptr;
    }


    //Sorts the list using merge sort.
    //Uses split() to divide the list and merge() to combine the sorted halves.
    //Runtime O(n log n) --> because we are using merge sort.
    void mergeSort()
    {
        //zero or one node (already sorted)
        if(head == nullptr || head->next == nullptr)
        {
           return;
        }

        //Creates left and right halves of the list.
        linkedList<T> left;
        linkedList<T> right;

        //Split current list into left and right.
        split(left, right);

        //Recursively sort the left and right halves.
        left.mergeSort();
        right.mergeSort();

        //Merge the two sorted halves back into this list.
        merge(left, right);
    }


    //Will read items from a file and adds them to the linked list.
    //Runtime O(n) --> because every item in the file is visited once.
    void loadFromFile(string filename)
    {
        //Open the file to read it
        ifstream input(filename);
        //Variable used to store each item read from the file.
        T item;

        //Continue reading while there are items in the file.
        while(input >> item)
        {
            push_back(item);   //Adds the item to the back of the linked list.

        }
        input.close();     // Close the input file.

    }


    //Writes every item in the linked list to a file.
    //Runtime O(n) --> because every node must be visited.
    void writeToFile(string filename)
    {
        //Open the output file.
        ofstream output(filename);
        //Start at the first node.
        node *current = head;

        //Continue until we reach the end of the list.
        while(current != nullptr)
        {
            //Write the current item's data to the file.
            output << current->data << endl;
            current = current->next;   //Move to the next node.

        }
        output.close();     // Close the output file.
    }
};