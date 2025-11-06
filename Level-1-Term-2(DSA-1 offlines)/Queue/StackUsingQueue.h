#include <iostream>
#include "QueueLinkedList.h"
using namespace std;

class Stack
{
private:
    // write your code here. Add additional private variables if necessary
    Queue stack;

public:
    // Constructor
    Stack()
    {
        // write your code here. Initialize additional private variables if necessary
    }
    Stack(int initialCapacity)
    {
        // write your code here. Initialize additional private variables if necessary
        // stack = new Queue;
    }

    // Destructor
    ~Stack()
    {
        // delete stack;
    }

    // Push an element onto the stack
    void push(int x)
    {
        // write your code here.
        // push the element onto the stack
        stack.enqueue(x);
    }

    // Remove and return the top element
    int pop()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        if (stack.isEmpty())
            return -1;
        Queue tempstack;
        int poppedvalue;
        int stacklength = stack.length();
        for (int i = 0; i < stacklength - 1; i++)
        {
            tempstack.enqueue(stack.dequeue());
        }
        poppedvalue = stack.dequeue();
        while (!tempstack.isEmpty())
        {
            stack.enqueue(tempstack.dequeue());
        }
        return poppedvalue;
        // pop the top element and return it
    }

    // Return the top element without removing it
    int top()
    {
        if (stack.isEmpty())
            return -1;
        Queue tempstack;
        int topvalue;
        int stacklength = stack.length();
        for (int i = 0; i < stacklength - 1; i++)
        {
            tempstack.enqueue(stack.dequeue());
        }
        topvalue = stack.dequeue();
        while (!tempstack.isEmpty())
        {
            stack.enqueue(tempstack.dequeue());
        }
        stack.enqueue(topvalue);

        // delete tempstack;
        return topvalue;
        // return the top element
    }

    // Return the number of elements in the stack
    int length()
    {
        // write your code here. Return the number of elements in the stack
        return stack.length();
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        // write your code here. Return true if the stack is empty, false otherwise
        return stack.isEmpty();
    }

    // Clear the stack
    void clear()
    {
        // write your code here. Clear the stack.
        stack.clear();
    }
};
