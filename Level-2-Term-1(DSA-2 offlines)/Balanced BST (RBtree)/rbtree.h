#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;

class Node
{
public:
    int value;
    Node *parent;
    Node *left;
    Node *right;
    string color;
    string name;
    int stock_value;
    Node(int value = 0, string name = "", int stock_value = 0, string color = "black")
    {
        this->value = value;
        this->stock_value = stock_value;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = color;
        this->name = name;
    }
    Node(const Node &node)
    {
        this->value = node.value;
        this->color = node.color;
        this->name = node.name;
        this->stock_value = node.stock_value;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        if (node.left != nullptr)
        {
            this->left = new Node(*node.left);
            this->left->parent = this;
        }
        if (node.right != nullptr)
        {
            this->right = new Node(*node.right);
            this->right->parent = this;
        }
    }
    Node &operator=(const Node &node)
    {
        if (this == &node)
            return *this;

        if (left)
            delete left;
        if (right)
            delete right;
        this->value = node.value;
        this->color = node.color;
        this->name = node.name;
        this->stock_value = node.stock_value;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        if (node.left != nullptr)
        {
            this->left = new Node(*node.left);
            this->left->parent = this;
        }
        if (node.right != nullptr)
        {
            this->right = new Node(*node.right);
            this->right->parent = this;
        }
        return *this;
    }
};

int find(Node *root, int value)
{
    if (root == nullptr)
        return -1;
    if (value < root->value)
        return find(root->left, value);
    else if (value > root->value)
        return find(root->right, value);
    return value;
}
Node *findNode(Node *root, int value)
{
    if (root == nullptr)
        return nullptr;
    if (value < root->value)
        return findNode(root->left, value);
    else if (value > root->value)
        return findNode(root->right, value);
    return root;
}
int checkItem(Node *root, int value)
{
    if (find(root, value) == -1)
        return 0;
    return findNode(root, value)->stock_value;
}

void left_rotate(Node **root, Node *x)
{
    if (x == nullptr || x->right == nullptr)
        return;

    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;
    y->left = x;

    if (x->parent == nullptr)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    x->parent = y;
}
void right_rotate(Node **root, Node *y)
{
    if ((*root) == nullptr || y == nullptr)
        return;
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }
    x->right = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
    {
        *root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    y->parent = x;
}

void insert_fix(Node **root, Node **newnode)
{
    while ((*newnode) != *root && (*newnode)->parent != nullptr && (*newnode)->parent->color == "red")
    {
        if ((*newnode)->parent->parent->left == (*newnode)->parent)
        {
            Node *y = (*newnode)->parent->parent->right; // y is uncle of newnode
            if (y != nullptr && y->value != 0 && y->color == "red")
            {
                (*newnode)->parent->color = y->color = "black";
                y->parent->color = "red";
                *newnode = y->parent;
            }
            else
            {
                if ((*newnode)->parent->right == (*newnode))
                {
                    *newnode = (*newnode)->parent;
                    left_rotate(root, (*newnode));
                }
                (*newnode)->parent->parent->color = "red";
                (*newnode)->parent->color = "black";

                right_rotate(root, (*newnode)->parent->parent);
            }
        }
        else
        {

            if ((*newnode)->parent->parent->right == (*newnode)->parent)
            {
                Node *y = (*newnode)->parent->parent->left; // y is uncle of newnode
                if (y != nullptr && y->color == "red")
                {

                    (*newnode)->parent->color = y->color = "black";
                    y->parent->color = "red";
                    *newnode = y->parent;
                }
                else
                {

                    if ((*newnode)->parent->left == (*newnode))
                    {
                        *newnode = (*newnode)->parent;
                        right_rotate(root, (*newnode));
                    }
                    (*newnode)->parent->parent->color = "red";
                    (*newnode)->parent->color = "black";
                    left_rotate(root, (*newnode)->parent->parent);
                }
            }
        }
    }
    (*root)->color = "black";
}
void insert(Node **Root, int value, string name, int stock_value)
{
    Node *searchingfornode = findNode(*Root, value);
    if (searchingfornode != nullptr && searchingfornode->value == value)
    {
        searchingfornode->value = value;
        searchingfornode->name = name;
        searchingfornode->stock_value = stock_value;
        return;
    }
    Node *x, *y = nullptr;
    x = *Root;
    while (x != nullptr && x->value != 0)
    {
        y = x;
        if (value < x->value)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    Node *newnode = new Node(value, name, stock_value, "red");
    newnode->left = new Node();
    newnode->left->parent = newnode;
    newnode->right = new Node();
    newnode->right->parent = newnode;

    if (!y)
    {
        *Root = newnode;
        insert_fix(Root, &newnode);
        return;
    }
    newnode->parent = y;
    if (newnode->value < y->value)
    {
        delete y->left;
        y->left = newnode;
    }
    else
    {
        delete y->right;
        y->right = newnode;
    }

    insert_fix(Root, &newnode);
}
void printTree(Node *Root)
{
    if (Root == nullptr || Root->value == 0)
    {
        return;
    }
    if (Root->left->value == 0 && Root->right->value == 0)
    {
        if (Root->color == "red")
            cout << dye::red(Root->value) << "_" << dye::red(Root->name);
        else
            cout << dye::black(Root->value) << "_" << dye::black(Root->name);

        return;
    }
    if (Root->color == "red")
        cout << dye::red(Root->value) << "_" << dye::red(Root->name);
    else
        cout << dye::black(Root->value) << "_" << dye::black(Root->name);

    cout << "(";
    printTree(Root->left);
    cout << ",";
    printTree(Root->right);
    cout << ")";
}
int parent(int val, Node *root)
{
    if (val < root->value)
    {
        return parent(val, root->left);
    }
    else if (root->value < val)
    {
        return parent(val, root->right);
    }
    else
        return root->parent->value;
}
Node *findMin(Node *root)
{
    if (root != nullptr && root->left->value != 0)
        return findMin(root->left);
    return root;
}

void delete_fix(Node **root, Node *x)
{
    while ((x)->color == "black" && (x)->parent != nullptr)
    {
        if (x->parent->left == x)
        {
            Node *sibling = x->parent->right;
            if (sibling->color == "red")
            {
                sibling->color = "black";
                x->parent->color = "red";
                left_rotate(root, x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == "black" && sibling->right->color == "black")
            {
                sibling->color = "red";
                x = x->parent;
            }
            else
            {
                if (sibling->right->color == "black")
                {
                    sibling->left->color = "black";
                    sibling->color = "red";
                    right_rotate(root, sibling);
                    sibling = x->parent->right;
                }
                sibling->color = x->parent->color;
                x->parent->color = "black";
                sibling->right->color = "black";
                left_rotate(root, x->parent);
                x = *root;
            }
        }

        else
        {
            Node *sibling = x->parent->left;
            if (sibling->color == "red")
            {
                sibling->color = "black";
                x->parent->color = "red";
                right_rotate(root, x->parent);
                sibling = x->parent->left;
            }
            if (sibling->right->color == "black" && sibling->left->color == "black")
            {
                sibling->color = "red";
                x = x->parent;
            }
            else
            {
                if (sibling->left->color == "black")
                {
                    sibling->right->color = "black";
                    sibling->color = "red";
                    left_rotate(root, sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = "black";
                sibling->left->color = "black";
                right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = "black";
}

pair<Node *, string> deleteNode(Node **root, int val)
{
    string original_color;
    if (*(root) == nullptr)
        return make_pair(*(root), "");
    if (val < (*root)->value)
        return deleteNode(&((*root)->left), val);
    else if (val > (*root)->value)
        return deleteNode(&((*root)->right), val);
    if ((*root)->left->value == 0 && (*root)->right->value == 0)
    {
        delete (*root)->left;
        delete (*root)->right;
        original_color = (*root)->color;
        Node *parent = (*root)->parent;
        Node *toDelete = (*root);
        if (parent != nullptr)
        {
            if (parent->left == (*root))
            {
                parent->left = new Node();
                (*root) = parent->left;
            }
            else
            {
                parent->right = new Node();
                (*root) = parent->right;
            }
            (*root)->parent = parent;
        }
        else
        {
            (*root) = nullptr;
        }
        delete toDelete;
        return make_pair((*root), original_color);
    }
    else if ((*root)->left->value == 0)
    {
        Node *toDelete = (*root);
        Node *child = (*root)->right;
        original_color = (*root)->color;
        if ((*root)->parent != nullptr)
        {
            if ((*root)->parent->left == (*root))
            {
                (*root)->parent->left = child;
            }
            else
                (*root)->parent->right = child;
        }
        else
        {
            (*root) = child;
        }

        child->parent = (*root);

        int deletedValue = toDelete->value;
        delete toDelete->left;
        delete toDelete;
        return make_pair(*(root), original_color);
    }
    else if ((*root)->right->value == 0)
    {
        Node *toDelete = (*root);
        Node *child = (*root)->left;
        original_color = (*root)->color;
        if ((*root)->parent != nullptr)
        {
            if ((*root)->parent->left == (*root))
            {
                (*root)->parent->left = child;
            }
            else
                (*root)->parent->right = child;
        }
        else
        {
            (*root) = child;
        }
        child->parent = (*root);
        int deletedValue = toDelete->value;
        delete toDelete->right;
        delete toDelete;
        return make_pair(*(root), original_color);
    }
    Node *MinNodeinRightSubtree = findMin((*root)->right);
    (*root)->value = MinNodeinRightSubtree->value;
    (*root)->name = MinNodeinRightSubtree->name;
    (*root)->stock_value = MinNodeinRightSubtree->stock_value;
    return deleteNode(&((*root)->right), (*root)->value);
}
void DeleteNode(Node **root, int value)
{
    pair<Node *, string> result = deleteNode(root, value);
    if (result.second == "black" && result.first != nullptr)
        delete_fix(root, result.first);
}
bool clearTree(Node **root)
{
    if (*root == nullptr)
        return true;
    DeleteNode(root, (*root)->value);
    return (*root == nullptr);
}

void Itr(Node *Root)
{
    if (Root == nullptr || Root->value == 0)
    {
        return;
    }
    if (Root->left->value == 0 && Root->right->value == 0)
    {
        if (Root->color == "red")
            cout << dye::red(Root->value) << "=>" << dye::red(Root->name) << "(" << dye::red(Root->stock_value) << ")" << endl;
        else
            cout << dye::black(Root->value) << "=>" << dye::black(Root->name) << "(" << dye::black(Root->stock_value) << ")" << endl;

        return;
    }
    Itr(Root->left);

    if (Root->color == "red")
        cout << dye::red(Root->value) << "=>" << dye::red(Root->name) << "(" << dye::red(Root->stock_value) << ")" << endl;
    else
        cout << dye::black(Root->value) << "=>" << dye::black(Root->name) << "(" << dye::black(Root->stock_value) << ")" << endl;

    Itr(Root->right);
}

bool deleteTree(Node **root)
{
    if ((*root) == nullptr)
    {
        return false;
    }

    deleteTree(&((*root)->left));
    deleteTree(&((*root)->right));
    if ((*root)->left == nullptr && (*root)->right == nullptr)
    {
        delete (*root);
        *root = nullptr;
    }
    return true;
}

string printTreeinFile(Node *Root)
{
    if (Root == nullptr || Root->value == 0)
    {
        return "";
    }
    if (Root->left->value == 0 && Root->right->value == 0)
    {

        return to_string(Root->value) + "_" + Root->name;
    }
    return to_string(Root->value) + "_" + Root->name + "(" + printTreeinFile(Root->left) + "," + printTreeinFile(Root->right) + ")";
}
string ItrinFile(Node *Root)
{
    if (Root == nullptr || Root->value == 0)
    {
        return "";
    }
    if (Root->left->value == 0 && Root->right->value == 0)
    {
        return to_string(Root->value) + "=>" + Root->name + "(" + to_string(Root->stock_value) + ")" + "\n";
    }
    return ItrinFile(Root->left) + to_string(Root->value) + "=>" + Root->name + "(" + to_string(Root->stock_value) + ")" + "\n" + ItrinFile(Root->right);
}
