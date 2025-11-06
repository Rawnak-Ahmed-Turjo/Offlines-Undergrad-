#include "arraylist.h"
// #include "linkedlist.h"
#include <stdio.h>

int main()
{
    FILE *file = fopen("in.txt", "r");
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    int capacity;
    int size;
    fscanf(file, "%d %d", &size, &capacity);

    ArrayList list;
    // LinkedList list;
    // init_linkedlist(&list);
    int i;
    for (i = 0; i < size; i++)
    {
        int value;
        fscanf(file, "%d", &value);
        list.append(value);
    }
    list.print_list();

    int func, param;
    while (fscanf(file, "%d %d", &func, &param) == 2 && func != 0)
    {
        if (func == 1)
        {
            list.append(param);
        }
        else if (func == 2)
        {
            int value = list.remove_at_current();
        }
        else if (func == 3)
        {
            int ret = list.find(param);
        }
        else if (func == 4)
        {
            list.move_to_start();
        }
        else if (func == 5)
        {
            list.move_to_end();
        }
        else if (func == 6)
        {
            list.prev();
        }
        else if (func == 7)
        {
            list.next();
        }
        else if (func == 8)
        {
            int pos = list.get_current_position();
        }
        else if (func == 9)
        {
            list.move_to_position(param);
        }
        else if (func == 10)
        {
            int len = list.get_size();
        }
        else if (func == 11)
        {
            int value = list.get_current_element();
        }
        else if (func == 12)
        {
            list.append(param);
        }
        else if (func == 13)
        {
            list.clear();
        }
        else
        {
            printf("Invalid function\n");
        }
        list.print_list();
    }
    printf("Program ended\n");
    fclose(file);
    return 0;
}