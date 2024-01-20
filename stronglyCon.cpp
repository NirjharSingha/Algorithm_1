#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<pair<int, int>>> &adj, stack<int> &toposort, vector<bool> &visited, int node)
{
    visited[node] = true;
    for (auto i : adj[node])
    {
        if (!visited[i.first])
        {
            dfs(adj, toposort, visited, i.first);
        }
    }
    toposort.push(node);
}
void revDfs(vector<vector<pair<int, int>>> &revAdj, vector<bool> &visited, int node, vector<int> &component)
{
    visited[node] = true;
    component.push_back(node);

    for (auto i : revAdj[node])
    {
        if (!visited[i.first])
        {
            revDfs(revAdj, visited, i.first, component);
        }
    }
}
int stronglyConnectedComponents(int v, vector<vector<int>> &edges)
{
    stack<int> toposort;
    int e = edges.size(), ct = 0;
    vector<vector<pair<int, int>>> adj(v), revAdj(v);
    vector<bool> visited(v, false);
    vector<int> component;
    for (int i = 0; i < e; i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];
        int w = edges[i][2];
        adj[a].push_back({b, w});
        revAdj[b].push_back({a, w});
    }
    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            dfs(adj, toposort, visited, i);
        }
    }
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }
    while (!toposort.empty())
    {
        int topnode = toposort.top();
        toposort.pop();
        if (!visited[topnode])
        {
            revDfs(revAdj, visited, topnode, component);
            ct++;
            for (auto i : component)
            {
                cout << i << " ";
            }
            cout << endl;
            component.clear();
        }
    }
    return ct;
}
