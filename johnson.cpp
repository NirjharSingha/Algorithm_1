#include <bits/stdc++.h>
using namespace std;
vector<int> bellmanFord(int n, vector<vector<int>> edges, bool &flag)
{
    // adding a new source vertex and edges of weight 0
    for (int i = 0; i < n; i++)
    {
        edges.push_back({n, i, 0});
    }
    vector<int> dist(n + 1, 1e9);
    dist[n] = 0;
    // finding shortest path from the new vertex to all other vertices
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[u] != 1e9)
            {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }
    // checking for negative weight cycle

    for (int j = 0; j < edges.size(); j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (dist[u] != 1e9 && dist[u] + w < dist[v])
        {
            flag = true;
        }
    }
    return dist;
}
void Dijkstra(int src, vector<vector<pair<int, int>>> &adj, vector<vector<int>> &distance,
              int &N, vector<vector<vector<int>>> &paths)
{
    priority_queue<pair<int, int>> pq;
    vector<int> vis(N + 1);
    vector<vector<int>> path(N + 1);
    distance[src][src] = 0;
    path[src] = {src};
    pq.push({0, src});
    while (!pq.empty())
    {
        int f = pq.top().second;
        pq.pop();
        if (!vis[f])
        {
            vis[f] = true;
            for (auto u : adj[f])
            {
                int s = u.first;
                int w = u.second;
                if (distance[src][f] + w < distance[src][s])
                {
                    distance[src][s] = distance[src][f] + w;
                    pq.push({-distance[src][s], s});
                    vector<int> newPath = path[f];
                    newPath.push_back(u.first);
                    path[u.first] = newPath;
                }
            }
        }
    }

    paths.push_back(path);
}
void shortest_distance(vector<vector<int>> edges, int n)
{
    bool flag = false;
    // running bellman ford algorithm
    vector<int> C = bellmanFord(n, edges, flag);
    if (flag)
    {
        cout << "negative weight cycle present. No solution" << endl;
        return;
    }
    // reweighting the graph
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        edges[i][2] += (C[u] - C[v]);
    }
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto e : edges)
    {
        adj[e[0]].push_back({e[1], e[2]});
    }
    vector<vector<int>> distance(n + 1, vector<int>(n + 1, 1e9));
    vector<vector<vector<int>>> paths;
    // running dijkstra algorithm for each vertex
    for (int i = 0; i < n; i++)
    {
        Dijkstra(i, adj, distance, n, paths);
    }
    // printing the final result
    cout << "The shortest path distances are" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << distance[i][j] + (C[j] - C[i]) << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int k = 0; k < paths.size(); k++)
    {

        cout << "shortest path to all vertices from vertex " << k << endl;
        for (int i = 0; i < paths[k].size(); i++)
        {
            for (int j = 0; j < paths[k][i].size(); j++)
            {
                cout << paths[k][i][j] << " ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;
    }
}
int main()
{
    int n, e;
    // taking the input
    cin >> n >> e;
    vector<vector<int>> edges;
    for (int i = 0; i < e; i++)
    {
        vector<int> edge;
        int u, v, w;
        cin >> u >> v >> w;
        edge = {u, v, w};
        edges.push_back(edge);
    }
    // calling function to find shortest path
    shortest_distance(edges, n);
    return 0;
}
