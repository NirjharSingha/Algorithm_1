#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>> &adj, vector<int> &path)
{
    while (!adj[node].empty())
    {
        int nextNode = adj[node].back();
        adj[node].pop_back();
        dfs(nextNode, adj, path);
    }
    path.push_back(node);
}

void printEulerPath(vector<vector<int>> &edges, int n)
{
    vector<vector<int>> adj(n);
    vector<int> inDegree(n, 0), outDegree(n, 0);

    for (vector<int> &edge : edges)
    {
        int u = edge[0], v = edge[1];
        adj[u].push_back(v);
        inDegree[v]++;
        outDegree[u]++;
    }

    int startNode = -1, endNode = -1;
    int lessInDegree = 0, lessOutDegree = 0;

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] < outDegree[i])
        {
            startNode = i;
            lessInDegree++;
        }
        else if (outDegree[i] < inDegree[i])
        {
            endNode = i;
            lessOutDegree++;
        }
    }

    if (!((lessInDegree == 0 && lessOutDegree == 0) || (lessInDegree == 1 && lessOutDegree == 1)))
    {
        cout << "no path" << endl;
        return;
    }

    if (startNode == -1 && endNode == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (!adj[i].empty())
            {
                startNode = i;
                break;
            }
        }
    }
    else if (startNode != -1 && endNode == -1)
    {
        endNode = startNode;
    }
    else if (startNode == -1 && endNode != -1)
    {
        startNode = endNode;
    }

    vector<int> path;
    dfs(startNode, adj, path);

    reverse(path.begin(), path.end());

    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl;
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
    printEulerPath(edges, n);

    return 0;
}
