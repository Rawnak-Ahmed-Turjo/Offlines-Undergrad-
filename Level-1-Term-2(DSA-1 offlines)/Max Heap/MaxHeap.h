#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>

#define MAX_CAPACITY 100 // Defines the maximum capacity of the heap
class MaxHeap
{
private:
    int heap[MAX_CAPACITY]; // Array to store heap elements
    int size;               // Current number of elements in the heap

    // Sifts up the node at index i to maintain heap property
    void siftUp(int i)
    {
        /**Write your code here**/
        int parent = (int)(i / 2.0 + 0.5) - 1;
        int largest = parent;
        if (heap[largest] < heap[i])
        {
            largest = i;
        }

        if (largest != parent)
        {
            int temp = heap[parent];
            heap[parent] = heap[largest];
            heap[largest] = temp;
            siftUp(parent);
        }
    }

    // Sifts down the node at index i to maintain heap property
    void siftDown(int i)
    {
        /**Write your code here**/
        int leftIndex = 2 * i + 1;
        int rightIndex = 2 * i + 2;
        int largest = i;
        if (heap[largest] < heap[leftIndex] && leftIndex < size)
        {
            largest = leftIndex;
        }
        if (heap[largest] < heap[rightIndex] && rightIndex < size)
        {
            largest = rightIndex;
        }
        if (largest != i)
        {
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            siftDown(largest);
        }
    }

public:
    // Constructor initializes an empty heap
    MaxHeap() : size(0) {}

    // Inserts a new element x into the heap
    void insert(int x)
    {
        if (size == MAX_CAPACITY)
        {
            throw std::length_error("insert() called, but the heap is full.");
        }

        /**Write your code here**/
        if (size == 0)
        {
            heap[size++] = x;
            return;
        }
        heap[size++] = x;
        int lastindex = size - 1;
        int parent = (int)(lastindex / 2.0 + 0.5) - 1;
        if (heap[parent] < heap[lastindex])
        {
            siftUp(lastindex);
        }
    }

    // Returns the maximum element without removing it
    int findMax()
    {
        if (size == 0)
        {
            throw std::runtime_error("findMax() called, but the heap is empty.");
        }
        /**Write your code here**/
        return heap[0];
    }

    // Removes and returns the maximum element from the heap
    int extractMax()
    {
        if (size == 0)
        {
            throw std::runtime_error("extractMax() called, but the heap is empty.");
        }

        /**Write your code here**/
        int max = heap[0];
        heap[0] = heap[--size];
        siftDown(0);
        return max;
    }

    // Returns the number of elements in the heap
    int getSize()
    {
        /**Write your code here**/
        return size;
    }

    // Checks if the heap is empty. Returns true if the heap is empty, false otherwise.
    bool isEmpty()
    {
        /**Write your code here**/
        if (size == 0)
            return true;
        return false;
    }

    // Increases the value of the element at index i to new_value
    void increaseKey(int i, int newValue)
    {
        if (i < 0 || i >= size || heap[i] >= newValue)
        {
            throw std::invalid_argument("increaseKey() called with invalid index or invalid new value.");
        }

        /**Write your code here**/
        heap[i] = newValue;
        if (i != 0)
        {
            int parent = (int)(i / 2.0 + 0.5) - 1;
            if (heap[parent] < heap[i])
            {
                siftUp(i);
            }
        }
    }

    // Deletes the element at index i
    void deleteKey(int i)
    {
        /**Write your code here**/
        if (size == 0 || i < 0 || i >= size)
            throw std::invalid_argument("deleteKey() called with invalid index or heap is empty.");
        int c, j;
        heap[i] = heap[--size];
        if ((heap[i] < heap[2 * i + 1] && 2 * i + 1 < size) || (heap[i] < heap[2 * i + 2]  && 2 * i + 2 < size))
            siftDown(i);
        else if(heap[i] > heap[(int)(i/2.0 +0.5)-1])
            siftUp(i);
    }

    // Prints the heap's content to the output file
    void printHeap(std::ofstream &outfile)
    {
        /**Write your code here**/
        for (int i = 0; i < size; i++)
        {
            outfile << heap[i] << " ";
        }
        outfile << std::endl;
    }

    // Checkes whether the Max Heap property is preserved or not. Returns true if the Max Heap property is valid and returns false otherwise.
    bool isValidMaxHeap()
    {
        /**Write your code here**/
        if (size == 0||size==1)
            return true;
      
        else
        {
            for (int i = 0; i < size / 2; i++)
            {
                if (2 * i + 1 < size && 2 * i + 2 < size)
                {
                    if (heap[i] < heap[2 * i + 1] || heap[i] < heap[2 * i + 2])
                        return false;
                }
                else if (2 * i + 1 < size)
                {
                    if (heap[i] < heap[2 * i + 1])
                        return false;
                }
            }
            return true;
        }
    }
};

#endif // MAXHEAP_H
