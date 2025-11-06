#include <bits/stdc++.h>
#include "rbtreepair.hpp"
using namespace std;

class HashTable_LinearProbing
{
public:
    vector<pair<string, int>> arr;
    int capacity;
    int S;
    int size;
    int collisions;
    HashTable_LinearProbing(int cap)
    {
        int i, j, k = 0;
        for (i = cap;; i++)
        {
            k = 0;
            for (j = 2; j <= sqrt(i); j++)
            {
                if (i % j == 0)
                {
                    k = 1;
                    break;
                }
            }
            if (k == 0)
                break;
        }
        capacity = i;
        size = 0;
        arr = vector<pair<string, int>>(capacity, {"", 0});
        S = 3;
        collisions = 0;
    }
    void insert(string &s)
    {
        unsigned long long assumingindex = search(s);
        if (arr[assumingindex].first == s)
        {
            return;
        }
        size++;
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        if (arr[index].first == ""||arr[index].first == "TOMBSTONE_VALUE")
        {
            arr[index] = {s, size};
        }
        else
        {
            index = linearProbing(s, index);
            arr[index] = {s, size};
        }
    }
    bool Delete(const string &s)
    {
        unsigned long long index = search(s);
        if (index == -1)
            return false;
        size--;
        arr[index] = {"TOMBSTONE_VALUE", -1};
        return true;
    }
    unsigned long long search(const string &s)
    {
        int i = 0;
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        while (arr[(index + i * S) % capacity].first != s && arr[(index + i * S) % capacity].first != "" && i < capacity)
        {
            i++;
        }
        if (i == capacity)
            return -1;
        return (index + i * S) % capacity;
    }

    unsigned linearProbing(string &s, unsigned long long index)
    {
        int linearHash, i = 0;
        while (arr[(index + i * S) % capacity].first != "" && i < capacity)
        {
            i++;
            collisions++;
        }
        if (i == capacity)
            return -1;
        linearHash = (index + i * S) % capacity;
        return linearHash;
    }
    unsigned long long hash1(const string &s)
    {
        unsigned long long hashvalue = 5381;
        for (char c : s)
        {
            hashvalue = ((hashvalue << 5) + hashvalue) + c;
        }
        return (hashvalue % capacity);
    }
    unsigned long long hash2(const string &s)
    {
        unsigned long long hashvalue = 0;
        for (char c : s)
        {
            hashvalue = c + (hashvalue << 6) + (hashvalue << 16) - hashvalue;
        }
        return hashvalue % capacity;
    }
    double loadFactor()
    {
        return (double)size / capacity;
    }
    int countProbe(const string &s)
    {
        int i = 0;
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        while (arr[(index + i * S) % capacity].first != s && arr[(index + i * S) % capacity].first != "" && i < capacity)
        {
            i++;
        }
        return i + 1;
    }
};

class HashTable_DoubleHash
{
public:
    vector<pair<string, int>> arr;
    int capacity;
    int S;
    int size;
    int collisions;
    HashTable_DoubleHash(int cap)
    {
        int i, j, k = 0;
        for (i = cap;; i++)
        {
            k = 0;
            for (j = 2; j <= sqrt(i); j++)
            {
                if (i % j == 0)
                {
                    k = 1;
                    break;
                }
            }
            if (k == 0)
                break;
        }
        capacity = i;
        size = 0;
        arr = vector<pair<string, int>>(capacity, {"", 0});
        S = 3;
        collisions = 0;
    }
    void insert(string &s)
    {
        unsigned long long assumingindex = search(s);
        if (arr[assumingindex].first == s)
        {
            return;
        }
        size++;
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        if (arr[index].first == ""||arr[index].first == "TOMBSTONE_VALUE")
        {
            arr[index] = {s, size};
        }
        else
        {
            index = doubleHashing(s, index);
            arr[index] = {s, size};
        }
    }
    bool Delete(const string &s)
    {
        unsigned long long index = search(s);
        if (index == -1)
            return false;
        size--;
        arr[index] = {"TOMBSTONE_VALUE", -1};
        return true;
    }
    unsigned long long search(const string &s)
    {
        int i = 0;
        unsigned long long index = hash1(s);
        unsigned long long x = hash2(s);
        // unsigned long long index = hash2(s);
        // unsigned long long x = hash1(s);

        unsigned long long u = index, v = x ? x : 1;
        while (arr[(u + i * v) % capacity].first != s && arr[(u + i * v) % capacity].first != "" && i < capacity)
        {
            i++;
        }

        if (i == capacity)
            return -1;
        return (u + i * v) % capacity;
    }
    unsigned long long doubleHashing(string &s, unsigned long long index)
    {
        unsigned long long doubleHash, i = 0, x = hash2(s);
        unsigned long long u = hash1(s), v = x ? x : 1;
        // unsigned long long doubleHash, i = 0, x = hash1(s);
        // unsigned long long u = hash2(s), v = x ? x : 1;
        while (arr[(u + i * v) % capacity].first != "" && i < capacity)
        {
            i++;
            collisions++;
        }
        if (i == capacity)
            return -1;
        doubleHash = (u + i * v) % capacity;
        return doubleHash;
    }

    unsigned long long hash1(const string &s)
    {
        unsigned long long hashvalue = 5381;
        for (char c : s)
        {
            hashvalue = ((hashvalue << 5) + hashvalue) + c;
        }
        return (hashvalue % capacity);
    }
    unsigned long long hash2(const string &s)
    {
        unsigned long long hashvalue = 0;
        for (char c : s)
        {
            hashvalue = c + (hashvalue << 6) + (hashvalue << 16) - hashvalue;
        }
        return hashvalue % capacity;
    }
    double loadFactor()
    {
        return (double)size / capacity;
    }
    int countProbe(const string &s)
    {
        int i = 0;
        unsigned long long index = hash1(s);
        unsigned long long u = index, v = hash2(s) ? hash2(s) : 1;
        // unsigned long long index = hash2(s);
        // unsigned long long u = index, v = hash1(s) ? hash1(s) : 1;
        while (arr[(u + i * v) % capacity].first != s && arr[(u + i * v) % capacity].first != "" && i < capacity)
        {
            i++;
        }

        return i + 1;
    }
};
class HashTable_RBtree
{

public:
    vector<Node *> arr_root;
    int capacity;
    int S;
    int size;
    int collisions;
    HashTable_RBtree(int cap)
    {
        int i, j, k = 0;
        for (i = cap;; i++)
        {
            k = 0;
            for (j = 2; j <= sqrt(i); j++)
            {
                if (i % j == 0)
                {
                    k = 1;
                    break;
                }
            }
            if (k == 0)
                break;
        }
        capacity = i;
        size = 0;
        arr_root = vector<Node *>(capacity, nullptr);
        S = 3;
        collisions = 0;
    }
    void insert(string &s)
    {
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        if (search(s) == -1)
        {
            size++;

            if (arr_root[index] != nullptr)
                collisions++;
            insert_rbtree(&arr_root[index], {s, size});
        }
    }
    bool Delete(const string &s)
    {
        unsigned long long index = search(s);
        if (index == -1)
            return false;
        size--;
        DeleteNode(&arr_root[index], s);
        return true;
    }
    unsigned long long search(const string &s)
    {
        int i = 0;
        unsigned long long index = hash1(s);
        // unsigned long long index = hash2(s);
        if (arr_root[index] != nullptr && findNode(arr_root[index], s) != nullptr)
        {
            return index;
        }
        return -1;
    }

    unsigned long long hash1(const string &s)
    {
        unsigned long long hashvalue = 5381;
        for (char c : s)
        {
            hashvalue = ((hashvalue << 5) + hashvalue) + c;
        }
        return (hashvalue % capacity);
    }
    unsigned long long hash2(const string &s)
    {
        unsigned long long hashvalue = 0;
        for (char c : s)
        {
            hashvalue = c + (hashvalue << 6) + (hashvalue << 16) - hashvalue;
        }
        return hashvalue % capacity;
    }
    double loadFactor()
    {
        return (double)size / capacity;
    }
};

double measureSearchTime_LinearProbing(HashTable_LinearProbing &ht, const string &key)
{
    auto start = chrono::high_resolution_clock::now();
    ht.search(key);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, micro>(end - start).count();
}
double measureSearchTime_DoubleHashing(HashTable_DoubleHash &ht, const string &key)
{
    auto start = chrono::high_resolution_clock::now();
    ht.search(key);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, micro>(end - start).count();
}
double measureSearchTimeRB(HashTable_RBtree &ht, const string &key)
{
    auto start = chrono::high_resolution_clock::now();
    ht.search(key);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, micro>(end - start).count();
}
int main()
{
    vector<int> nums = {4002, 5003, 6004, 7004, 8005, 9006};
    freopen("output_hash1.txt", "w", stdout);

    for (int n : nums)
    {
        freopen(("words_" + to_string(n) + ".txt").c_str(), "r", stdin);
        cin.clear();
        HashTable_LinearProbing H_LinearProbing(10000);
        HashTable_DoubleHash H_DoubleHash(10000);
        HashTable_RBtree H_RBtree(10000);
        vector<string> allwords;

        string s;

        while (cin >> s)
        {
            H_LinearProbing.insert(s);
            H_DoubleHash.insert(s);
            H_RBtree.insert(s);
            allwords.push_back(s);
        }
        int totalwordscount = allwords.size();
        cout << "----- Load factor " << " = " << H_LinearProbing.loadFactor() << " -----" << endl;
        cout << "collisons of insertion in Hashtable (seperate chaining)   : " << H_RBtree.collisions << endl;
        cout << "collisons of insertion in Hashtable (Linear Probing)      : " << H_LinearProbing.collisions << endl;
        cout << "collisons of insertion in Hashtable (Double Hashing)      : " << H_DoubleHash.collisions << endl;

        int countofsearch = 0.1 * totalwordscount; // 1000
        int countofdelete = 0.1 * totalwordscount; // 1000
        vector<string> search_keys;

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> dist(0, allwords.size() - 1);

        for (int i = 0; i < countofsearch; i++)
        {
            search_keys.push_back(allwords[dist(gen)]);
        }
        double total_probes_linear = 0, total_probes_double = 0,
               total_time_linear = 0, total_time_double = 0, total_time_rbt = 0;
        for (auto key : search_keys)
        {
            total_probes_linear += H_LinearProbing.countProbe(key);
            total_probes_double += H_DoubleHash.countProbe(key);
            total_time_linear += measureSearchTime_LinearProbing(H_LinearProbing, key);
            total_time_double += measureSearchTime_DoubleHashing(H_DoubleHash, key);
            total_time_rbt += measureSearchTimeRB(H_RBtree, key);
        }

        cout << "Average Search Time (Seperate chaining, microsecond): " << total_time_rbt / countofsearch << endl;
        cout << "Average Search Time (Linear Probing, microsecond)   : " << total_time_linear / countofsearch << endl;
        cout << "Average Search Time (Double Hashing, microsecond)   : " << total_time_double / countofsearch << endl;
        cout << "Average probes (Linear probing)                     : " << total_probes_linear / countofsearch << endl;
        cout << "Average probes (Double hashing)                     : " << total_probes_double / countofsearch << endl;
        int half = countofsearch / 2; // half = 500
        int k;
        shuffle(allwords.begin(), allwords.end(), gen);
        vector<string> deleted_keys;
        vector<int> generatedindices;
        for (int i = 0; i < countofdelete; i++) // delete any 10% from hashable and put them in deleted keys(90% in hashtable)
        {
            k = dist(gen);
            if (/*generatedindices.find(k)*/ find(generatedindices.begin(), generatedindices.end(), k) != generatedindices.end())
            {
                i--;
                continue;
            }
            generatedindices.push_back(k);
            H_LinearProbing.Delete(allwords[k]);
            H_DoubleHash.Delete(allwords[k]);
            H_RBtree.Delete(allwords[k]);
            deleted_keys.push_back(allwords[k]);
        }
        for (int i = 0; i < countofdelete; i++) // delete those 10% words from allwords (90% is  allwords)
        {
            auto it = find(allwords.begin(), allwords.end(), deleted_keys[i]);
            if (it != allwords.end())
                allwords.erase(it);
        }
        shuffle(allwords.begin(), allwords.end(), gen);           // shuffle allwords(9000)
        uniform_int_distribution<> dist2(0, allwords.size() - 1); // 0-8999 = 9000
        search_keys.clear();
        for (int i = 0; i < half; i++)
        {
            search_keys.push_back(allwords[dist2(gen)]); // insert  new 5%  wrds from current allwords in search set(now 10%)
        }
        uniform_int_distribution<> dist3(0, deleted_keys.size() - 1);
        for (int i = 0; i < half; i++)
        {
            search_keys.push_back(deleted_keys[dist3(gen)]); // insert  more  500  wrds from deletedkeys in search set
        }
        shuffle(search_keys.begin(), search_keys.end(), gen); // shuffle searchkeys
        shuffle(allwords.begin(), allwords.end(), gen);
        total_time_linear = 0;
        total_time_double = 0;
        total_time_rbt = 0;
        total_probes_linear = 0;
        total_probes_double = 0;
        for (const auto key : search_keys)
        {
            total_time_linear += measureSearchTime_LinearProbing(H_LinearProbing, key);
            total_time_double += measureSearchTime_DoubleHashing(H_DoubleHash, key);
            total_time_rbt += measureSearchTimeRB(H_RBtree, key);
            total_probes_linear += H_LinearProbing.countProbe(key);
            total_probes_double += H_DoubleHash.countProbe(key);
        }
        cout << "Post-Deletion :" << endl;
        cout << "Average Search Time (Seperate chaining, microsecond): " << total_time_rbt / countofsearch << endl;
        cout << "Average Search Time (Linear Probing, microsecond)   : " << total_time_linear / countofsearch << endl;
        cout << "Average Search Time (Double Hashing, microsecond)   : " << total_time_double / countofsearch << endl;
        cout << "Average Probes (Linear Probing)                     : " << total_probes_linear / countofsearch << endl;
        cout << "Average Probes (Double Hashing)                     : " << total_probes_double / countofsearch << endl;
        cout << endl;
        cout << endl;
        fclose(stdin);
    }
    fclose(stdout);

    return 0;
}
