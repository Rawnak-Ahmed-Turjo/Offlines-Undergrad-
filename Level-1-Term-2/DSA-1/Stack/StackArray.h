#include <iostream>
using namespace std;

class Stack
{
private:
    int *array;
    // write your code here. Add additional private variables if necessary
    int Capacity;
    int topNodeindex;

public:
    // Constructor
    Stack(int initialcapacity = 1){
        array = new int[initialcapacity];
        Capacity = initialcapacity;
        topNodeindex = -1;
    }
    // Destructor
    ~Stack()
    {
        delete[] array; // Free dynamically allocated memory
    }

    // Helper function to resize the array when full
    void resize(int newCapacity)
    {
        int *newArray = new int[newCapacity]; // Allocate new array

        // write your code here. Copy the elements from the old array to the new array
        for (int i = 0; i <= topNodeindex; i++)
            newArray[i] = array[i];
        delete[] array; // Free old memory
        // write your code here. Update the capacity and array pointers
        Capacity = newCapacity;
        array = newArray;
    }

    // Push an element onto the stack
    void push(int x)
    {
        // write your code here. Check if the array is full and resize if necessary.
        // push the element onto the stack
        if (topNodeindex + 1 == Capacity)
        {
            resize(Capacity * 2);
        }
        array[++topNodeindex] = x;
    }

    // Remove and return the top element
    int pop()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        // pop the top element and return it
        // resize the array if necessary
        if (topNodeindex == -1)
            return -1;

        int removed_value = array[topNodeindex];
        topNodeindex--;
        if ((topNodeindex + 1) < (Capacity / 4) )
        {
            resize(Capacity / 2);
        }
        return removed_value;
    }

    // Return the top element without removing it
    int top()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        // return the top element
        if (topNodeindex == -1)
            return -1;
        return array[topNodeindex];
    }

    // Return the number of elements in the stack
    int length()
    {
        // write your code here. Return the number of elements in the stack
        return topNodeindex + 1;
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        // write your code here. Return true if the stack is empty, false otherwise
        return topNodeindex == -1;
    }

    // Clear the stack
    void clear()
    {
        // write your code here. Clear the stack. resize the array to 1
        topNodeindex = -1;
        resize(1);
    }
    
};
