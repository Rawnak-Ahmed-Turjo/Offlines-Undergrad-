#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
};

Node *insertNode(Node *node, int val)
{
    if (node == nullptr)
    {
        Node *newnode = new Node;
        newnode->val = val;
        newnode->left = nullptr;
        newnode->right = nullptr;
        return newnode;
    }
    else if (node->val < val)
    {
        node->right = insertNode(node->right, val);
    }
    else if (val < node->val)
    {
        node->left = insertNode(node->left, val);
    }
    return node;
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be inserted
    // Returns the pointer to the root of the modified BST.
}

Node *deleteNode(Node *node, int val)
{
    if (node == nullptr)
        return node;
    if (val < node->val)
        node->left = deleteNode(node->left, val);
    else if (node->val < val)
        node->right = deleteNode(node->right, val);

    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            Node *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            Node *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            Node *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->val = temp->val;
            node->right = deleteNode(node->right, node->val);
        }
    }
    return node;
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be deleted.
    // Returns the pointer to the root of the modified BST.
}

Node *find(Node *node, int val)
{
    if (node == nullptr)
        return nullptr;
    if (node->val == val)
        return node;
    if (node->val < val)
        return find(node->right, val);
    return find(node->left, val);
    // Write your codes here
    // This function takes a pointer to the root of the BST and
    // the value to be searched.
    // Returns the pointer to the node that contains val.
    // Returns NULL if not found.
}

void inOrder(Node *node)
{
    if (node == nullptr)
        return;
    if (node->left == nullptr && node->right == nullptr)
    {
        cout << node->val << " ";
        return;
    }
    inOrder(node->left);
    cout << node->val << " ";
    inOrder(node->right);

    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the in-order traversal of the given BST
}

void preOrder(Node *node)
{
    if (node == nullptr)
        return;
    if (node->left == nullptr && node->right == nullptr)
    {
        cout << node->val << " ";
        return;
    }
    cout << node->val << " ";

    preOrder(node->left);
    preOrder(node->right);
    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the pre-order traversal of the given BST
}

void postOrder(Node *node)
{
    if (node == nullptr)
        return;
    if (node->left == nullptr && node->right == nullptr)
    {
        cout << node->val << " ";
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    cout << node->val << " ";

    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints the post-order traversal of the given BST
}

void printTree(Node *root)
{
    if (root == nullptr)
    {
        cout << "_";
        return;
    }
    cout << root->val << " ";
    if (root->left != nullptr || root->right != nullptr)
    {
        cout << " (";
        printTree(root->left);
        cout << " , ";
        printTree(root->right);
        cout << ")";
    }

    // Write your codes here
    // This function takes a pointer to the root of the BST
    // Prints parenthesized representation of the given BST
}