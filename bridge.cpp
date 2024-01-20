#include <bits/stdc++.h>
using namespace std;
void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dis, vector<int> &lowest, int node, int parent, int &timer, vector<vector<int>> &ans)
{
    visited[node] = true;
    dis[node] = lowest[node] = timer++;
    for (auto nbr : adj[node])
    {
        if (nbr == parent)
            continue;
        if (!visited[nbr])
        {
            dfs(adj, visited, dis, lowest, nbr, node, timer, ans);
            lowest[node] = min(lowest[node], lowest[nbr]);
            if (lowest[nbr] > dis[node])
            {
                vector<int> temp;
                temp.push_back(node);
                temp.push_back(nbr);
                ans.push_back(temp);
            }
        }
        else
        {
            lowest[node] = min(lowest[node], dis[nbr]);
        }
    }
}
vector<vector<int>> findBridges(vector<vector<int>> &edges, int v, int e)
{
    vector<vector<int>> adj(v), ans;
    vector<int> dis(v, -1), lowest(v, -1);
    vector<bool> visited(v, false);
    int timer = 0, parent = -1;
    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            dfs(adj, visited, dis, lowest, i, parent, timer, ans);
        }
    }
    return ans;
}