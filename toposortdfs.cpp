#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void dfs(vector<int> adj[], vector<bool> &vis, vector<int> &ans, int node)
    {
        vis[node] = true;
        for (auto nbr : adj[node])
        {
            if (!vis[nbr])
            {
                dfs(adj, vis, ans, nbr);
            }
        }
        ans.push_back(node);
    }
    vector<int> topoSort(int V, vector<int> adj[])
    {
        vector<int> ans;
        vector<bool> vis(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfs(adj, vis, ans, i);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};