#include <bits/stdc++.h>
using namespace std;
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    // n is number of vertices and m is number of edges
    vector<pair<pair<int, int>, int>> ans;
    vector<vector<pair<int, int>>> adj(n + 1);
    set<vector<int>> st;
    vector<bool> visited(n + 1, false);
    for (int i = 0; i < m; i++)
    {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int wt = g[i].second;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    // priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>;
    vector<int> temp, t;
    temp = {0, 1, 1};
    st.insert(temp);
    int i = 1;
    while (!st.empty())
    {
        temp = *st.begin();
        st.erase(temp);
        if (!visited[temp[2]])
        {
            visited[temp[2]] = true;
            if (i != 1)
            {
                ans.push_back({{temp[1], temp[2]}, temp[0]});
            }
            for (auto &x : adj[temp[2]])
            {
                if (!visited[x.first])
                {
                    t = {x.second, temp[2], x.first};
                    st.insert(t);
                }
            }
            i++;
        }
    }
    return ans;
}
