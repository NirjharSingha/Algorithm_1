#include <bits/stdc++.h>
using namespace std;
void printPath(int i, int j, vector<vector<int>> &path, bool &flag)
{
    if (path[i][j] == -1)
    {
        cout << "no path" << endl;
        flag = false;
        return;
    }
    else if (path[i][j] == i)
    {
        cout << i << " ";
    }
    else
    {
        printPath(i, path[i][j], path, flag);
        printPath(path[i][j], j, path, flag);
    }
}
void floydWarshall(int n, int m, vector<vector<int>> &edges)
{
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 1e9));
    vector<vector<int>> path(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        matrix[u][v] = wt;
    }
    for (int i = 1; i <= n; i++)
    {
        matrix[i][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (matrix[i][j] != 1e9 && i != j)
            {
                path[i][j] = i;
            }
        }
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (matrix[i][k] == 1e9 || matrix[k][j] == 1e9)
                    continue;
                else if (matrix[i][j] == 1e9)
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    path[i][j] = path[k][j];
                }
                else
                {
                    if (matrix[i][j] > matrix[i][k] + matrix[k][j])
                    {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                        path[i][j] = path[k][j];
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "---------" << endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << "printing path from " << i << " to all other vertices" << endl;
        bool flag = true;
        for (int j = 1; j <= n; j++)
        {
            printPath(i, j, path, flag);
            if (flag)
                cout << j << endl;
            else
                flag = true;
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    for (int i = 0; i < m; i++)
    {
        vector<int> edge(3);
        cin >> edge[0] >> edge[1] >> edge[2];
        edges.push_back(edge);
    }
    floydWarshall(n, m, edges);
    return 0;
}