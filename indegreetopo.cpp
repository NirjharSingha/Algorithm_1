#include <bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int>> &adj, queue<int> &q, vector<int> &ans, vector<int> &inDegree)
{
    while (!q.empty())
    {
        int frontNode = q.front();
        q.pop();
        ans.push_back(frontNode);
        for (int neighbour : adj[frontNode])
        {
            inDegree[neighbour]--;
            if (inDegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }
}
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)
{
    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }
    queue<int> q;
    vector<int> ans, inDegree(v, 0);
    for (int i = 0; i < v; i++)
    {
        for (int neighbour : adj[i])
        {
            inDegree[neighbour]++;
        }
    }
    for (int i = 0; i < v; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    bfs(adj, q, ans, inDegree);
    return ans;
}