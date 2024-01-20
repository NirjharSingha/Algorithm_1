#include <bits/stdc++.h>
using namespace std;

int bellmanFord(int n, int m, int src, int dest, vector<vector<int>> &edges)
{
    vector<int> dist(n + 1, 1e9);
    vector<int> parent(n + 1, -1); // To store parent nodes for reconstructing path
    dist[src] = 0;
    parent[src] = src; // Parent of source is itself

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[u] != 1e9 && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u; // Update parent for reconstructing path
            }
        }
    }

    // Check for negative cycles
    bool negativeCycle = false;
    for (int j = 0; j < m; j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (dist[u] != 1e9 && dist[u] + w < dist[v])
        {
            negativeCycle = true;
            break;
        }
    }

    // If there is a negative cycle, path is not well-defined
    if (negativeCycle)
    {
        cout << "Negative cycle detected, shortest path is not well-defined." << endl;
        return -1;
    }

    // Reconstruct and print path
    vector<int> path;
    int node = dest;
    while (node != src)
    {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());

    cout << "Shortest distance from " << src << " to " << dest << ": " << dist[dest] << endl;
    cout << "Path: ";
    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl;

    return dist[dest];
}

int main()
{
    int n, m, src, dest;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;
    cout << "Enter the source node: ";
    cin >> src;
    cout << "Enter the destination node: ";
    cin >> dest;

    vector<vector<int>> edges(m, vector<int>(3));
    cout << "Enter the edge list in the format (u v weight) for each edge:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int shortestDistance = bellmanFord(n, m, src, dest, edges);

    if (shortestDistance != -1)
    {
        cout << "Shortest distance from " << src << " to " << dest << ": " << shortestDistance << endl;
    }

    return 0;
}
