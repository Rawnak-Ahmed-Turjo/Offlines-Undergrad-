
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int MIN_L = 5;
    int MAX_L = 10;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> len_dist(MIN_L, MAX_L);
    uniform_int_distribution<> char_dist('a', 'z');
    int num_strings[] = {4446, 5557, 6668, 7779, 8890, 10000};
    int n;
    ofstream result("result.txt");

    n = 10000;
    ofstream words(("words_" + to_string(n) + ".txt").c_str());
    set<string> strings;
    for (int i = 0; i < n; i++)
    {
        int length = len_dist(gen);
        string s;
        for (int j = 0; j < length; j++)
        {
            s += (char)(char_dist(gen));
        }
        if (strings.find(s) != strings.end())
        {
            i--;
            result << "found duplicate"<< endl;
            continue;
        }
        strings.insert(s);
        words << s << endl;
    }
    result.close();
    words.close();
    return 0;
}