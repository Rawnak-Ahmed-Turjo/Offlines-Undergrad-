#include <iostream>
#include <vector>
#include "traversal.h"
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, a, b, x, count = 0;
    cin >> n >> m;
    vector<bool> visited(n + 1, false);
    vector<int> remaining;

    vector<vector<int>> adjlist(n + 1);
    //vector<vector<int>> adjM(n + 1, vector<int>(n + 1, 0));

    x = m;
    while (x--)
    {
        cin >> a >> b;
        addEdgeList(adjlist, a, b);
        //addEdgeMatrix(adjM, a, b);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            remaining.push_back(i);
            dfs(adjlist, i, visited);
            //bfs(adjM, i, visited);
            count++;
        }
    }
    cout << count - 1 << endl;
    if (count > 0)
    {
        for (int i = 0; i < remaining.size() - 1; i++)
        {
            cout << remaining[i] << " " << remaining[i + 1] << endl;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}