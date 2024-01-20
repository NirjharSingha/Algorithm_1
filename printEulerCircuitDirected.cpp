#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &adj, stack<int> &toposort, vector<bool> &visited, int node)
{
    visited[node] = true;
    for (auto i : adj[node])
    {
        if (!visited[i])
        {
            dfs(adj, toposort, visited, i);
        }
    }
    toposort.push(node);
}

void revDfs(vector<vector<int>> &revAdj, vector<bool> &visited, int node)
{
    visited[node] = true;
    for (auto i : revAdj[node])
    {
        if (!visited[i])
        {
            revDfs(revAdj, visited, i);
        }
    }
}

int stronglyConnectedComponents(int v, vector<vector<int>> &adj, vector<vector<int>> &revAdj)
{
    stack<int> toposort;
    vector<bool> visited(v, false);
    int ct = 0;
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
            revDfs(revAdj, visited, topnode);
            ct++;
        }
    }
    return ct;
}

void printCircuit(vector<vector<int>> &adj)
{
    vector<int> curr_path;
    curr_path.push_back(0);

    vector<int> circuit;

    while (curr_path.size() > 0)
    {
        int curr_v = curr_path[curr_path.size() - 1];

        if (adj[curr_v].size() > 0)
        {
            int next_v = adj[curr_v].back();
            adj[curr_v].pop_back();
            curr_path.push_back(next_v);
        }

        else
        {
            circuit.push_back(curr_path.back());
            curr_path.pop_back();
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        cout << circuit[i];
        if (i)
            cout << " -> ";
    }
    cout << endl;
}

void printEulerCircuit(vector<vector<int>> &edges, int n)
{
    vector<vector<int>> adjList(n), revAdj(n);
    vector<int> inDegree(n, 0);

    for (vector<int> &edge : edges)
    {
        int u = edge[0], v = edge[1];
        adjList[u].push_back(v);
        revAdj[v].push_back(u);
        inDegree[v]++;
    }

    for (int node = 0; node < n; node++)
    {
        if (inDegree[node] != adjList[node].size())
        {
            cout << "No Euler Circuit exists." << endl;
            return;
        }
    }

    int stronglyConnectedComps = stronglyConnectedComponents(n, adjList, revAdj);

    if (stronglyConnectedComps > 1)
    {
        cout << "No Euler Circuit exists." << endl;
        return;
    }

    printCircuit(adjList);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m, vector<int>(2));
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1];
    }
    printEulerCircuit(edges, n);

    return 0;
}
