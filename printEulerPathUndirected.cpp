#include <bits/stdc++.h>
using namespace std;

void addEdge(int u, int v, vector<vector<int>> &adj)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void deleteEdge(int u, int v, vector<vector<int>> &adj)
{
    for (int i = 0; i < adj[u].size(); i++)
    {
        if (adj[u][i] == v)
        {
            adj[u][i] = -1;
            break;
        }
    }

    for (int i = 0; i < adj[v].size(); i++)
    {
        if (adj[v][i] == u)
        {
            adj[v][i] = -1;
            break;
        }
    }
}

// Function to count all reachable nodes from given node.
void dfs(int u, int &count, vector<vector<int>> &adj, vector<bool> &vis)
{
    vis[u] = 1;
    count++;

    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v != -1 and vis[v] == false)
        {
            dfs(v, count, adj, vis);
        }
    }
}

// Function to check whether given edge is Non - bridge edge or not.
bool isNonbridge(int u, int v, vector<vector<int>> &adj)
{

    int countAdjacentNodes = 0;
    for (int i = 0; i < adj[u].size(); i++)
    {
        if (adj[u][i] != -1)
        {
            countAdjacentNodes++;
        }
    }
    if (countAdjacentNodes == 1)
    {
        return true;
    }

    int n = adj.size();
    vector<bool> vis(n, false);
    int withoutRemove = 0, withRemove = 0;
    dfs(u, withoutRemove, adj, vis);

    vis = vector<bool>(n, false);
    deleteEdge(u, v, adj);
    dfs(u, withRemove, adj, vis);

    addEdge(u, v, adj);

    if (withRemove >= withoutRemove)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to get Euler path.
void eulerPath(int u, vector<vector<int>> &adj, vector<int> &answer)
{
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v != -1 and isNonbridge(u, v, adj) == true)
        {
            answer.push_back(v);
            deleteEdge(u, v, adj);
            eulerPath(v, adj, answer);
        }
    }
}

vector<int> printEulerPath(int n, vector<vector<int>> &edgeList)
{
    vector<int> answer;
    vector<vector<int>> adj(n);

    // Build adjacency list.
    for (int i = 0; i < edgeList.size(); i++)
    {
        int u = edgeList[i][0], v = edgeList[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int odd = 0;

    // Count nodes with odd degree.
    for (int i = 0; i < n; i++)
    {
        if (adj[i].size() % 2 == 1)
        {
            odd++;
        }
    }

    // Check if Euler path is not possible.
    if (odd != 0 and odd != 2)
    {
        answer.push_back(-1);
        return answer;
    }

    if (odd == 0)
    {
        answer.push_back(0);
        eulerPath(0, adj, answer);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (adj[i].size() % 2 == 1)
            {
                answer.push_back(i);
                eulerPath(i, adj, answer);
                break;
            }
        }
    }

    return answer;
}