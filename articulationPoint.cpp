#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void dfs(vector<int> adj[], vector<bool> &visited, vector<int> &dis, vector<int> &lowest, int node, int parent, int &timer, set<int> &ans)
    {
        visited[node] = true;
        dis[node] = lowest[node] = timer++;
        int child = 0;
        for (auto nbr : adj[node])
        {
            if (nbr == parent)
                continue;
            if (!visited[nbr])
            {
                dfs(adj, visited, dis, lowest, nbr, node, timer, ans);
                lowest[node] = min(lowest[node], lowest[nbr]);
                if (lowest[nbr] >= dis[node] && parent != -1)
                {
                    ans.insert(node);
                }
                child++;
            }
            else
            {
                lowest[node] = min(lowest[node], dis[nbr]);
            }
        }
        if (parent == -1 && child > 1)
        {
            ans.insert(node);
        }
    }

    vector<int> articulationPoints(int V, vector<int> adj[])
    {
        vector<int> dis(V, -1), lowest(V, -1);
        set<int> ans;
        vector<bool> visited(V, false);
        int timer = 0, parent = -1;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs(adj, visited, dis, lowest, i, parent, timer, ans);
            }
        }

        if (ans.size() == 0)
        {
            ans.insert(-1);
        }

        return vector<int>(ans.begin(), ans.end());
    }
};

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        vector<int> ans = obj.articulationPoints(V, adj);
        for (auto i : ans)
            cout << i << " ";
        cout << "\n";
    }
    return 0;
}