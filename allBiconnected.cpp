#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<int> &disc, vector<int> &low, stack<pair<int, int>> &st, vector<int> &parent, vector<vector<int>> &adj, vector<vector<int>> &biconnectedComps)
{

    static int time = 0;

    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : adj[u])
    {
        if (disc[v] == -1)
        {
            children++;
            parent[v] = u;
            st.push(pair<int, int>(u, v));
            dfs(v, disc, low, st, parent, adj, biconnectedComps);

            low[u] = min(low[u], low[v]);

            if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
            {
                vector<int> comp;
                while (st.top().first != u || st.top().second != v)
                {
                    comp.push_back(st.top().first);
                    comp.push_back(st.top().second);
                    st.pop();
                }
                comp.push_back(st.top().first);
                comp.push_back(st.top().second);
                st.pop();
                biconnectedComps.push_back(comp);
            }
        }
        else if (v != parent[u])
        {
            low[u] = min(low[u], disc[v]);
            if (disc[v] < disc[u])
            {
                st.push(pair<int, int>(u, v));
            }
        }
    }
}

vector<vector<int>> getAllBiconnectedComponents(int n, vector<pair<int, int>> &edges)
{
    vector<vector<int>> adj(n + 1);

    for (auto &x : edges)
    {
        adj[x.first].push_back(x.second);
        adj[x.second].push_back(x.first);
    }

    vector<vector<int>> biconnectedComps;
    vector<int> disc(n + 1, -1);
    vector<int> low(n + 1, -1);
    vector<int> parent(n + 1, -1);
    stack<pair<int, int>> st;

    for (int i = 1; i <= n; i++)
    {
        if (disc[i] == -1)
            dfs(i, disc, low, st, parent, adj, biconnectedComps);

        while (!st.empty())
        {
            st.pop();
        }
    }

    return biconnectedComps;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<vector<int>> biconnectedComps = getAllBiconnectedComponents(n, edges);

    cout << "Number of biconnected components: " << biconnectedComps.size() << endl;
    cout << "Biconnected components:" << endl;
    for (const vector<int> &comp : biconnectedComps)
    {
        for (int node : comp)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
