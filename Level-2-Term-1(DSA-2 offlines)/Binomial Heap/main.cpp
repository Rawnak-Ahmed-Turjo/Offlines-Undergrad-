#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int value;
    int degree;
    Node *parent;
    Node *sibling;
    Node *child;
    Node(int value = 0)
    {
        this->value = value;
        parent = NULL;
        sibling = NULL;
        child = NULL;
        degree = 0;
    }
};

class BinomialHeap
{
public:
    Node *root;
    BinomialHeap()
    {
        root = NULL;
    }
    void insert(int value)
    {
        Node *newNode = new Node(value);
        BinomialHeap temp;
        temp.root = newNode;
        Union(temp);
    }
    void Union(BinomialHeap &tree)
    {
        root = mergeList(root, tree.root);
        if (root == NULL)
            return;
        Node *ptr = root, *ptr2 = root->sibling, *prev = NULL;
        while (ptr2)
        {
            if (ptr->degree != ptr2->degree || (ptr2->sibling != NULL && ptr2->sibling->degree == ptr2->degree))
            {
                prev = ptr;
                ptr = ptr2;
            }
            else
            {
                if (ptr->value <= ptr2->value)
                {
                    ptr->sibling = ptr2->sibling;
                }
                else
                {
                    if (!prev)
                    {
                        root = ptr2;
                    }
                    else
                    {
                        prev->sibling = ptr2;
                    }
                }
                ptr = mergeTree(ptr, ptr2);
            }
            ptr2 = ptr->sibling;
        }
    }
    Node *mergeTree(Node *ptr, Node *ptr2)
    {
        if (ptr->value <= ptr2->value)
        {
            ptr2->parent = ptr;
            ptr2->sibling = ptr->child;
            ptr->child = ptr2;
            ptr->degree++;
            return ptr;
        }
        ptr->parent = ptr2;
        ptr->sibling = ptr2->child;
        ptr2->child = ptr;
        ptr2->degree++;
        return ptr2;
    }
    Node *mergeList(Node *l1, Node *l2)
    {
        if (l1 == NULL)
        {
            return l2;
        }
        if (l2 == NULL)
        {
            return l1;
        }
        Node *tmp = new Node(0);
        Node *tail = tmp;
        while (l1 && l2)
        {
            if (l1->degree <= l2->degree)
            {
                tail->sibling = l1;
                l1 = l1->sibling;
            }
            else
            {
                tail->sibling = l2;
                l2 = l2->sibling;
            }
            tail = tail->sibling;
        }
        if (l1)
        {
            tail->sibling = l1;
        }
        else if (l2)
        {
            tail->sibling = l2;
        }
        Node *Root = tmp->sibling;
        delete tmp;
        return Root;
    }
    void update_key(int value, int newValue)
    {
        Node *target = find(value);
        if (target == NULL)
        {
            cout << "The node with the value " << target << " not found\n";
            return;
        }
        target->value = newValue;
        siftup(target);
    }
    void removeKey(int value)
    {
        update_key(value, INT_MIN);
        extract_min();
    }
    int extract_min()
    {
        if (!root)
            return INT_MAX;
        Node *ptr = root;
        Node *minNode = NULL;
        Node *prev = NULL;
        Node *prevMin = NULL;
        int minValue = INT_MAX;
        while (ptr)
        {
            if (ptr->value < minValue)
            {
                minValue = ptr->value;
                minNode = ptr;
                prevMin = prev;
            }
            prev = ptr;
            ptr = ptr->sibling;
        }
        if (minNode == root)
        {
            root = minNode->sibling;
        }
        else if (prevMin)
        {
            prevMin->sibling = minNode->sibling;
        }
        BinomialHeap newHeap;
        newHeap.root = reverselListwithModifyingParent(minNode->child);
        Union(newHeap);
        delete minNode;
        return minValue;
    }
    Node *reverselListwithModifyingParent(Node *head)
    {
        Node *curr = head;
        Node *prev = NULL;
        Node *nextnode;
        while (curr)
        {
            nextnode = curr->sibling;
            curr->sibling = prev;
            curr->parent = NULL;
            prev = curr;
            curr = nextnode;
        }
        return prev;
    }
    void siftup(Node *ptr)
    {
        if (ptr == NULL || ptr->parent == NULL)
            return;
        if (ptr->value < ptr->parent->value)
        {
            swap(ptr->value, ptr->parent->value);
            siftup(ptr->parent);
        }
    }
    Node *find(int value)
    {
        Node *ptr, *ptr2;
        int flag;
        ptr = root;
        while (ptr)
        {
            flag = 0;
            ptr2 = ptr;
            while (ptr2)
            {
                if (ptr2->value == value)
                {
                    return ptr2;
                }
                if (flag == 0 && ptr2->child)
                {
                    ptr = ptr2->child;
                    flag = 1;
                }
                ptr2 = ptr2->sibling;
            }
            if (flag == 0)
                break;
        }
        return NULL;
    }
    int find_Min()
    {
        Node *ptr, *ptr2;
        int flag, minValue = INT_MAX;
        ptr = root;
        while (ptr)
        {
            if (ptr->value < minValue)
            {
                minValue = ptr->value;
            }
            ptr = ptr->sibling;
        }
        return minValue;
    }

    void printHeap()
    {
        if (root == NULL)
        {
            cout << "Empty heap\n";
            return;
        }
        cout << "Printing Binomial Heap...\n";

        Node *tree = root;
        while (tree)
        {
            printTree(tree);
            tree = tree->sibling;
        }
    }
    void printTree(Node *Root)
    {
        Node *ptr, *ptr2;
        int flag, depth = 0;
        ptr = Root;
        cout << "Binomial tree, B" << findDepth(Root) << endl;
        cout << "Level " << depth << ": " << ptr->value << endl;
        ptr = ptr->child;
        depth++;
        while (ptr)
        {
            flag = 0;
            ptr2 = ptr;
            cout << "Level " << depth << ": ";
            while (ptr2)
            {
                cout << ptr2->value << " ";
                if (flag == 0 && ptr2->child)
                {
                    ptr = ptr2->child;
                    flag = 1;
                }
                ptr2 = ptr2->sibling;
            }
            cout << endl;
            depth++;
            if (flag == 0)
                break;
        }
    }
    int findDepth(Node *Root)
    {
        if (Root == NULL)
            return -1;
        int depth = 0;
        while (Root->child)
        {
            depth++;
            Root = Root->child;
        }
        return depth;
    }
};
int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt","w",stdout);
    BinomialHeap heap;
    char command;
    int value, newValue;
    while (cin >> command)
    {
        if (command == 'I')
        {
            cin >> value;
            heap.insert(value);
        }
        else if (command == 'P')
        {
            heap.printHeap();
        }
        else if (command == 'R')
        {
            cin >> value;
            heap.removeKey(value);
        }
        else if (command == 'D')
        {
            cin >> value >> newValue;
            heap.update_key(value, newValue);
        }
        else if (command == 'E')
        {
            cout << "Extract Min returned : " << heap.extract_min() << endl;
        }
        else if (command == 'F')
        {
            cout << "Find Min returned : " << heap.find_Min() << endl;
        }
    }
    return 0;
}
