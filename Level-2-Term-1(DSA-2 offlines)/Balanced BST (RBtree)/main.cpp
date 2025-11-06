#include <bits/stdc++.h>
#include "rbtree.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    ofstream outfile("output.txt");

    Node *root = nullptr;
    int size = 0;
    while (true)
    {
        char line[50];
        string words[5];
        int count = 0;
        cin.getline(line, 50);
        char *token = strtok(line, " ");
        while (token != nullptr)
        {
            words[count++] = token;
            token = strtok(nullptr, " ");
        }

        if (words[0] == "AI")
        {
            Node *node = findNode(root, stoi(words[1]));
            if (node == nullptr)
            {
                insert(&root, stoi(words[1]), words[2], stoi(words[3]));
                size++;
            }
            else
            {
                node->name = words[2];
                node->stock_value = stoi(words[3]);
            }
            printTree(root);
            cout << endl;
            outfile << printTreeinFile(root) << endl;
        }
        else if (words[0] == "CI")
        {
            int quantity = checkItem(root, stoi(words[1]));
            if (!quantity)
            {
                cout << "Not available" << endl;
                outfile << "Not available" << endl;
            }
            else
            {
                cout << "Stock left : " << quantity << endl;
                outfile << "Stock left : " << quantity << endl;
            }
        }
        else if (words[0] == "BI")
        {
            Node *node = findNode(root, stoi(words[1]));
            if (node->stock_value - stoi(words[2]) > 0)
            {
                node->stock_value = node->stock_value - stoi(words[2]);
            }
            else
            {
                DeleteNode(&root, stoi(words[1]));
                size--;
            }
            printTree(root);
            cout << endl;
            outfile << printTreeinFile(root) << endl;
        }
        else if (words[0] == "Clr")
        {
            size = 0;
            if (deleteTree(&root))
            {
                cout << "Successful\n";
                outfile << "Successful\n";
            }
            else
            {
                cout << "Unsuccessful\n";
                outfile << "Unsuccessful\n";
            }
        }
        else if (words[0] == "S")
        {
            cout << size << endl;
            outfile << size << endl;
        }
        else if (words[0] == "Em")
        {
            if (size == 0)
            {
                cout << "Yes" << endl;
                outfile << "Yes" << endl;
            }
            else
            {
                cout << "no" << endl;
                outfile << "no" << endl;
            }
        }
        else if (words[0] == "Itr")
        {
            Itr(root);
            outfile << ItrinFile(root);
        }
        else if (words[0] == "Br")
        {
            break;
        }
        else
        {
            cout << "invalid command\n";
            outfile << "invalid command\n";
        }
    }

    return 0;
}
