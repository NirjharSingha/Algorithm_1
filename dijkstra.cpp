#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

vector<pair<int, vector<int>>> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source)
{
    vector<int> dist(vertices, INT_MAX);
    vector<pair<int, vector<int>>> paths(vertices, {INT_MAX, vector<int>()}); // Pair of distance and path
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<vector<pair<int, int>>> adj(vertices);

    for (int i = 0; i < edges; i++)
    {
        int u = vec[i][0];
        int v = vec[i][1];
        int wt = vec[i][2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    dist[source] = 0;
    pq.push({0, source});
    paths[source] = {0, {source}}; // Initialize path for source node

    while (!pq.empty())
    {
        auto temp = pq.top();
        pq.pop();

        int topnode = temp.second;
        int distance = temp.first;

        for (auto i : adj[topnode])
        {
            if (distance + i.second < dist[i.first])
            {
                dist[i.first] = distance + i.second;
                pq.push({dist[i.first], i.first});

                // Update path
                vector<int> newPath = paths[topnode].second; // Copy the path from the previous node
                newPath.push_back(i.first);                  // Append the current node to the path
                paths[i.first] = {dist[i.first], newPath};
            }
        }
    }

    return paths;
}

int main()
{
    int vertices, edges, source = 0;
    cin >> vertices;
    cin >> edges;

    vector<vector<int>> vec(edges, vector<int>(3));
    for (int i = 0; i < edges; i++)
    {
        cin >> vec[i][0] >> vec[i][1] >> vec[i][2];
    }

    vector<pair<int, vector<int>>> result = dijkstra(vec, vertices, edges, source);

    for (int i = 0; i < vertices; i++)
    {
        cout << "Shortest distance from " << source << " to " << i << ": " << result[i].first << endl;
        cout << "Path: ";
        for (int node : result[i].second)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
