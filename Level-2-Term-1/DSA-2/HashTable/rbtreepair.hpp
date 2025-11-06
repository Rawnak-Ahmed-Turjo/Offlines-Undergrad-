#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    pair<string, int> value;
    Node *parent;
    Node *left;
    Node *right;
    string color;
    Node(string key = "", int val = 0, string color = "black")
    {
        this->value = make_pair(key, val);
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = color;
    }
};

Node *findNode(Node *root, string key)
{
    if (root == nullptr || root->value.first == "")
        return nullptr;
    if (key < root->value.first)
        return findNode(root->left, key);
    else if (key > root->value.first)
        return findNode(root->right, key);
    return root;
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
            if (y != nullptr && y->color == "red")
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
void insert_rbtree(Node **Root, pair<string, int> value)
{
    Node *searchingfornode = findNode(*Root, value.first);
    if (searchingfornode != nullptr && searchingfornode->value == value)
    {
        searchingfornode->value = value;
        return;
    }
    Node *x, *y = nullptr;
    x = *Root;
    while (x != nullptr && x->value.first != "")
    {
        y = x;
        if (value.first < x->value.first)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    Node *newnode = new Node(value.first, value.second, "red");
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
    if (newnode->value.first < y->value.first)
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
    if (Root == nullptr || Root->value.first == "")
    {
        return;
    }
    if (Root->left->value.first == "" && Root->right->value.first == "")
    {

        cout << Root->value.first << "_" << Root->value.second;

        return;
    }
    cout << Root->value.first << "_" << Root->value.second;

    cout << "(";
    printTree(Root->left);
    cout << ",";
    printTree(Root->right);
    cout << ")";
}
string parent(Node *root, string key)
{
    if (key < root->value.first)
    {
        return parent(root->left, key);
    }
    else if (root->value.first < key)
    {
        return parent(root->left, key);
    }
    else
        return root->parent->value.first;
}
Node *findMin(Node *root)
{
    if (root != nullptr && root->left->value.first != "")
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
            if ((sibling->left&&sibling->right)&&sibling->left->color == "black" && sibling->right->color == "black")
            {
                sibling->color = "red";
                x = x->parent;
            }
            else if(sibling->left&&sibling->right)
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
            else
            {
                x->parent->color = "black";
                break;   
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
            if ((sibling->left&&sibling->right)&&sibling->right->color == "black" && sibling->left->color == "black")
            {
                sibling->color = "red";
                x = x->parent;
            }
            else if(sibling->left&&sibling->right)
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
            else
            {
                x->parent->color = "black";
                break;   
            }
        }
    }
    x->color = "black";
}

pair<Node *, string> deleteNode(Node **root, string key)
{
    string original_color;
    if (*(root) == nullptr)
        return make_pair(*(root), "");
    if (key < (*root)->value.first)
        return deleteNode(&((*root)->left), key);
    else if (key > (*root)->value.first)
        return deleteNode(&((*root)->right), key);
    if ((*root)->left->value.first == "" && (*root)->right->value.first == "")
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
    else if ((*root)->left->value.first == "")
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

        delete toDelete->left;
        delete toDelete;
        return make_pair(*(root), original_color);
    }
    else if ((*root)->right->value.first == "")
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
        delete toDelete->right;
        delete toDelete;
        return make_pair(*(root), original_color);
    }
    Node *MinNodeinRightSubtree = findMin((*root)->right);
    (*root)->value = MinNodeinRightSubtree->value;

    return deleteNode(&((*root)->right), (*root)->value.first);
}
void DeleteNode(Node **root, string key)
{
    pair<Node *, string> result = deleteNode(root, key);
    if (result.second == "black" && result.first != nullptr)
        delete_fix(root, result.first);
}
bool clearTree(Node **root)
{
    if (*root == nullptr)
        return true;
    DeleteNode(root, (*root)->value.first);
    return (*root == nullptr);
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
