#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node *next;
    Node *prev;
    Node(int value = 0)
    {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

class LinkedList
{
    Node *head;
    Node *tail;
    Node *currentposition;

public:
    LinkedList()
    {
        printf("linkedlist implemented\n");
        head = nullptr;
        tail = nullptr;
    }

    void clear(LinkedList *list)
    {
        printf("cleared list\n");
        for (Node *ptr = head; ptr != nullptr; ptr = ptr->next)
            delete ptr;
        list->head = NULL;
        list->tail = NULL;
    }

    int get_size(LinkedList *list)
    {
        int count = 0;
        for (Node *ptr = list->head; ptr != NULL; ptr = ptr->next)
            count++;

        printf("size is %d\n", count);
        return count;
    }

    void append(LinkedList *list, int value)
    {
        printf("appended %d\n", value);
        Node *newnode = new Node(value);
        newnode->next = nullptr;
        if (!head)
        {

            newnode->prev = nullptr;
            head = tail = newnode;
            currentposition = head;
        }
        else
        {
            newnode->prev = tail;
            tail->next = newnode;
            tail = newnode;
        }
    }

    void insert(LinkedList *list, int value)
    {
        Node *newnode = new Node(value);
        if (!head)
        {
            newnode->prev = nullptr;
            newnode->next = nullptr;
            head = newnode;
            currentposition = newnode;
            tail = head;
        }
        else if (currentposition == head)
        {
            newnode->prev = nullptr;
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
            currentposition = head;
        }
        else if (currentposition == tail)
        {
            newnode->next = nullptr;
            newnode->prev = tail;
            tail->next = newnode;
            tail = newnode;

        }
        else
        {
            newnode->prev = currentposition->prev;
            newnode->next = currentposition;
            currentposition->prev->next = newnode;
            currentposition->prev = newnode;
            currentposition = newnode;
        }
        printf("inserted %d\n", value);
    }

    int remove_at_current()
    {
        if (!head)
        {
            printf("unable to remove because list is empty\n");
            return -1;
        }
        int removeddata = currentposition->value;
        //Node *ptr ;
        if (currentposition == head)
        {
            // ptr = list->head;
            // list->current_position = list->current_position->next;
            // list->head = list->current_position;
            // list->head->prev = NULL;
            currentposition = head->next;
            delete currentposition->prev;
            currentposition->prev = nullptr;
            head = currentposition;
        }
        else if (currentposition == tail)
        {
            // ptr = list->tail;
            // list->current_position = list->current_position->prev;
            // list->tail = list->current_position;
            // list->tail->next = NULL;
            currentposition = currentposition->prev;
            delete currentposition->next;
            currentposition->next = nullptr;
            tail = currentposition;
        }
        else
        {
            // ptr = list->current_position;
            // list->current_position = list->current_position->next;
            // ptr->prev->next = list->current_position;
            // list->current_position->prev = ptr->prev;
            currentposition->prev->next = currentposition->next;
            currentposition->next->prev = currentposition->prev;
            Node* deletingnode = currentposition;
            currentposition = currentposition->next;
            delete deletingnode;
        }
        printf("removed %d\n", removeddata);
        return removeddata;
    }

    int find(int value)
    {
        int i = 0;
        Node *ptr ;
        for (ptr = head; ptr != NULL; ptr = ptr->next)
        {
            if (value == ptr->value)
            {
                printf("found %d at %d\n", value, i);
                return i;
            }
            i++;
        }
        printf("did not find %d in the list\n", value);
        return -1;
    }

    void move_to_start( )
    {
        printf("moved current position to 0\n");
        currentposition = head;
    }

    void move_to_end()
    {
        printf("moved current position to end\n");
        currentposition =tail;
    }

    void prev()
    {
        if (currentposition == head)
            printf("cannot go behind already in starting position\n");
        else
        {
            int i = 0;
            Node *ptr ;
            for (ptr = head; ptr != currentposition; ptr = ptr->next)
            {
                i++;
            }
           
            currentposition = currentposition->prev;
            printf("moved current position from %d to %d\n", i, i - 1);
        }
    }

    void next()
    {
        if (currentposition == tail)
            printf("cannot go forward already in end position\n");
        else
        {
            int i = 0;
            Node *ptr ;
            for (ptr = head; ptr != currentposition; ptr = ptr->next)
            {
                i++;
            }

            currentposition = currentposition->next;
            printf("moved current position from %d to %d\n", i, i + 1);
        }
    }

    void move_to_position(int position)
    {
        int i;
        int j = 0;
        Node *ptr;
        for (ptr = head; ptr != currentposition; ptr = ptr->next)
        {
            j++;
        }
        printf("moved current position from %d to %d\n", j, position);
        ptr = head;
        for (i = 0; i < position; i++)
        {
            ptr = ptr->next;
        }
        currentposition = ptr;
    }

    int get_current_position()
    {
        int i = 0;
        Node *ptr = (Node *)malloc(sizeof(Node));
        for (ptr = head; ptr != currentposition; ptr = ptr->next)
        {
            i++;
        }
        printf("current position is %d\n", i);
        return i;
    }

    int get_current_element()
    {
        printf("current element is %d\n",currentposition->value);
        return currentposition->value;
    }

    void print_list()
    {
        Node *ptr;
        printf("< ");
        for (ptr = head; ptr != NULL; ptr = ptr->next)
        {
            if (currentposition == ptr)
                printf("|");
            printf("%d  ", ptr->value);
        }
        printf(">");
        printf("\n");
    }

    void free_list(LinkedList *list)
    {
        Node *ptr = (Node *)malloc(sizeof(Node));
        for (ptr = list->head; ptr != NULL; ptr = ptr->next)
        {
            free(ptr);
        }
    }
};