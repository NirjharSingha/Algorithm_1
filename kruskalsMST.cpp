#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}
void makeSet(vector<int> &rank, vector<int> &parent, int n)
{
    for (int i = 0; i < n; i++)
    {
        rank[i] = 0;
        parent[i] = i;
    }
}
int findParent(vector<int> &parent, int node)
{
    if (parent[node] == node)
    {
        return node;
    }
    return parent[node] = findParent(parent, parent[node]);
}
void unionSet(vector<int> &rank, vector<int> &parent, int a, int b)
{
    if (rank[a] > rank[b])
    {
        parent[b] = a;
    }
    else if (rank[a] < rank[b])
    {
        parent[a] = b;
    }
    else
    {
        parent[b] = a;
        rank[a]++;
    }
}
int minimumSpanningTree(vector<vector<int>> &edges, int n)
{
    sort(edges.begin(), edges.end(), cmp);
    vector<int> parent(n), rank(n);
    int e = edges.size(), ans = 0;
    makeSet(rank, parent, n);
    for (int i = 0; i < e; i++)
    {
        int wt = edges[i][2];
        int u = findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        if (u != v)
        {
            unionSet(rank, parent, u, v);
            ans += wt;
            cout << edges[i][0] << " " << edges[i][1] << endl;
        }
    }
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    int ans = minimumSpanningTree(edges, n);
    cout << ans << endl;

    return 0;
}