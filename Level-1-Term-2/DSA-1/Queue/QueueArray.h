#include <iostream>
using namespace std;

class Queue
{
private:
    int *array;
    // write your code here. Add additional private variables if necessary
    int capacity;
    int size;
    int front;
    int end;

public:
    // Constructor

    Queue(int initialCapacity = 1)
    {
        capacity = initialCapacity;
        array = new int[initialCapacity];
        front = 0;
        end = 0;
        size = 0;
    }
    // Destructor
    ~Queue()
    {
        delete[] array; // Free dynamically allocated memory
    }

    // Helper function to resize the array when full
    void resize(int newCapacity)
    {
        int *newarray = new int[newCapacity];
        int index = 0;
        for (int i = front; i < end; i++)
        {
            newarray[index] = array[i];
            index++;
        }
        delete[] array;
        array = newarray;
        capacity = newCapacity;
        front = 0;
        end = index;
    }

    // Enqueue an element onto the queue
    void enqueue(int x)
    {
        // write your code here. Check if the array is full and resize if necessary.

        // if (front == -1 && end == -1) // when nothing in array
        // {
        //     ++front;
        //     ++end;
        //     array[end] = x;
        //     ++size;
        // }
        // else if (front == 0) // when front of array is not empty
        // {
        //     if (size == capacity)
        //         resize(capacity * 2);
        //     ++end;
        //     array[end] = x;
        //     ++size;
        // }
        // else // when front is empty
        // {
        //     if (size == capacity)
        //         resize(capacity * 2);
        //     end = (end + 1) % capacity;
        //     array[end] = x;
        //     ++size;
        // }
        if (size == capacity)
        {
            resize(2 * capacity);
        }
        array[end] = x;
        size++;
        if (end == capacity)
        {
            end = 0;
        }
        else
        {
            end++;
        }
    }

    // Remove and return the peek element
    int dequeue()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        // if (size == 0)
        //     return -1;
        // int peek_element = array[front];
        // size--;
        // front = (front + 1) % capacity;

        // if (size == 0)
        // {
        //     front = -1;
        //     end = -1;
        //     return peek_element;
        // }
        // if (size < capacity / 4)
        // {
        //     resize(capacity / 2);
        // }

        // return peek_element;
        if(size==0) return -1;
        int peek = array[front];
        if(front < capacity-1){
            front++;
        }
        else
        {
            front++;
        }
        size--;
        if(size==0){
            front = 0; end = 0; resize(1);capacity  = 1;
            return peek;
        }
        if(size < capacity/4) resize(capacity/2);
        return peek;
        // remove the peek element and return it
        // resize the array if necessary
    }

    // Return the peek element without removing it
    int peek()
    {
        // write your code here. Check if the queue is empty and return -1 if it is.
        if (!size)
            return -1;
        return array[front];
        // return the peek element
    }

    // Return the number of elements in the queue
    int length()
    {
        // write your code here. Return the number of elements in the queue
        return size;
    }

    // Check if the queue is empty
    bool isEmpty()
    {
        // write your code here. Return true if the queue is empty, false otherwise
        if (size)
            return false;
        return true;
    }

    // Clear the queue
    void clear()
    {
        // write your code here. Clear the queue. resize the array to 1
        resize(1);
        capacity = 1;
        size = 0;
        front = 0;
        end = 0;
    }
};
