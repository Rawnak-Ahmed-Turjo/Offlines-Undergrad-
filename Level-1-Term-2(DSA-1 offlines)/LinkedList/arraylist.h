#include <iostream>
#include <stdlib.h>
using namespace std;

class ArrayList
{
    int *arr;
    int size;
    int currentposition;
    int capacity;

public:
    ArrayList()
    {
        arr = new int[1];
        size = 0;
        currentposition = 0;
        capacity = 1;
    }
    ArrayList(int capacity)
    {
        this->capacity = capacity;
        this->size = 0;
        this->currentposition = 0;
    }
    void resize(int new_capacity)
    {
        int *newarr = new int[new_capacity];
        for (int i = 0; i < size; i++)
        {
            newarr[i] = arr[i];
        }
        delete[] arr;
        arr = newarr;
        this->capacity = new_capacity;
    }
    void clear()
    {
        printf("cleared list\n");
        // clear the list but do not free the array
        fill(arr, arr + capacity, 0);
        size = 0;
        currentposition = 0;
    }
    int get_size()
    {
        printf("size is %d\n", size);
        return size;
    }

    void append(int value)
    {
        if (size == capacity)
        {
            resize(capacity * 2);
        }
        arr[size] = value;
        size++;
        // call resize if necessary
        // add value to the end of the list
    }

    void insert(int value)
    {
        if (size == 0)
        {
            cout << "Unable to insert\n";
            return;
        }
        else if (size == capacity)
        {
            resize(capacity * 2);
        }
        for (int i = size; i > currentposition; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[currentposition] = value;
        size++;
    }

    int remove_at_current()
    {
        if (size == 0)
        {
            cout << "Unable to remove at current\n";
            return -1;
        }
        for (int i = currentposition; i < size; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;
        return arr[size-1];
        // save the value of the current element in a variable
        // shift the elements to the left to fill the gap
        // change the size, and current position as necessary
        // call resize if necessary
        // return the saved value
    }

    int find(int value)
    {
        for (int i; i < size; i++)
        {
            if (arr[i] == value)
                return i;
        }
        return -1;
    }

    void move_to_start()
    {
        if (size == 0)
        {
            cout << "Unable to move to start because list is empty\n";
            return;
        }
        currentposition = 0;
        // if (list->size > 0)
        // {
        //     list->current = 0;
        //     printf("moved current position to 0\n");
        //     return;
        // }
        // printf("unable to change position because list is empty\n");
        // // consider the cases when the list is empty
    }

    void move_to_end()
    {
        if (size == 0)
        {
            cout << "CAnnot move to end because list is empty\n";
            return;
        }
        currentposition = size - 1;
        cout << "Moved to end\n";
        // if (list->size > 0)
        // {
        //     list->current = list->size - 1;
        //     printf("moved current position to end at index %d\n", list->size - 1);
        //     return;
        // }
        // printf("unable to change position because list is empty\n");
        // // printf("Implement move_to_end\n");
        // //  consider the cases when the list is empty
    }

    void prev()
    {
        if (size == 0 || currentposition == 0)
        {
            cout << "Cannot move to previous\n";
        }
        currentposition--;
        cout << "Moved to orevious\n";
        // // no change if the current position is at the start
        // if (list->current == 0)
        //     printf("cannot go behind already in starting position\n");
        // else
        // {
        //     list->current--;
        //     printf("moved current position from %d to %d\n", list->current + 1, list->current);
        // }
    }

    void next()
    {
        if (size == 0 || currentposition == size - 1)
        {
            cout << "Unable to go to next\n";
            return;
        }
        currentposition++;
        // //  no change if the current position is at the end
        // if (list->current == list->size - 1)
        //     printf("cannot go forward already in end position\n");
        // else
        // {
        //     list->current++;
        //     printf("moved from %d to %d\n", list->current - 1, list->current);
        // }
    }

    void move_to_position(int position)
    {
        if (size == 0 || currentposition < 0 || currentposition >= size)
        {
            cout << "Unable to move position\n";
            return;
        }
        currentposition = position;
    }

    int get_current_position()
    {
        if (size == 0)
        {
            cout << "List is empty\n";
            return -1;
        }
        return currentposition;
    }

    int get_current_element()
    {
        if (size == 0)
        {
            cout << "unable to retrive\n";
            return -1;
        }
        return arr[currentposition];
    }

    void print_list()
    {
        printf("< ");
        for (int i = 0; i < size; i++)
        {
            if (currentposition == i)
                printf("|");
            printf("%d  ", *(arr + i));
        }
        printf(">");
        printf("\n");
    }

    ~ArrayList()
    {
        delete[] arr;
    }
};