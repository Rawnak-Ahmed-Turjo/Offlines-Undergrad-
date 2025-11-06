#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }

    Node(int value, Node *nextNode)
    {
        data = value;
        next = nextNode;
    }
};

class Queue
{
private:
    Node *peekNode; // Points to the front of the queue
    int currentSize;

public:
    // Constructor
    Queue()
    {
        peekNode = nullptr;
        currentSize = 0;
    }

    // Enqueue an element onto the queueu
    void enqueue(int x)
    {
        // write your code here. Create a new node with the value x and enqueue it onto the queue
        Node *newnode = new Node(x);
        if(peekNode==nullptr)
        {
            peekNode = newnode;
            newnode = nullptr;
            delete newnode;
            currentSize++;
            return;
        }
        Node *ptr = peekNode;
        while (ptr->next != nullptr)
            ptr = ptr->next;
        ptr->next = newnode;
        newnode = nullptr;
        delete newnode;
        // update the peekNode and currentSize
        currentSize++;
    }

    // Remove and return the peek element
    int dequeue()
    {
        // write your code here. Check if the queueu is empty and return -1 if it is.
        if(currentSize==0) return -1;
        // dequeue the peek element and return it
        Node* head = peekNode;
        int deletedvalue = peekNode->data;
        // update the peekNode and currentSize
        peekNode = peekNode->next;
        currentSize--;
        // delete the node that was dequeued
        delete head;
        return deletedvalue;
        
    }

    // Return the peek element without removing it
    int peek()
    {
        // write your code here. Check if the queueu is empty and return -1 if it is.
        if(currentSize==0)  return -1;
        return peekNode->data;
        // return the peek element
    }

    // Return the number of elements in the queueu
    int length()
    {
        // write your code here. Return the number of elements in the queueu
        return currentSize;
    }

    // Check if the queueu is empty
    bool isEmpty()
    {
        // write your code here. Return true if the queueu is empty, false otherwise
        if(currentSize==0) return true;
        return false;
    }

    // Clear the queueu
    void clear()
    {
        while (!isEmpty())
        {
            dequeue(); // Continuously dequeue elements until the queueu is empty
        }
    }

    // Destructor
    ~Queue()
    {
        clear();
    }
};
