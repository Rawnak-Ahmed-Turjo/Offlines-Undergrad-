#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void addEdgeMatrix(vector<vector<int>> &adjM, int a, int b)
{
    adjM[a][b] = 1;
    adjM[b][a] = 1;
}
queue<int> temp;

void bfs(vector<vector<int>> &adjM, int start, vector<bool> &visited)
{
    int i, j;
    visited[start] = true;
    temp.push(start);
    while (!temp.empty())
    {
        j = temp.front();
        temp.pop();
        for (i = 1; i <= adjM[j].size() - 1; i++)
        {
            if (!visited[i] && adjM[j][i] == 1)
            {
                temp.push(i);
                visited[i] = true;
            }
        }
    }
}

void addEdgeList(vector<vector<int>> &adjlist, int a, int b)
{
    adjlist[a].push_back(b);
    adjlist[b].push_back(a);
}

void dfs(vector<vector<int>> &adjlist, int start, vector<bool> &visited)
{

    visited[start] = true;
    for (int i = 0; i < (int)adjlist[start].size(); i++)
    {
        if (!visited[adjlist[start][i]])
        {
            dfs(adjlist, adjlist[start][i], visited);
        }
    }
}
