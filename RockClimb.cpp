#include <bits/stdc++.h>
using namespace std;
int main()
{
    int m, n;
    cin >> m >> n;
    int mat[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat[i][j];
        }
    }
    int dp[m + 1][n + 2];
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = INT_MAX;
        dp[i][n + 1] = INT_MAX;
    }
    for (int i = 1; i <= n; i++)
    {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = mat[i - 1][j - 1] + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i - 1][j + 1]));
        }
    }
    int ans = INT_MAX;
    vector<int> path;
    int colIdx = -1;
    for (int i = 1; i <= n; i++)
    {
        if (dp[m][i] < ans)
        {
            ans = dp[m][i];
            colIdx = i;
        }
    }
    path.push_back(mat[m - 1][colIdx - 1]);
    for (int i = m - 1; i > 0; i--)
    {
        int temp = dp[i + 1][colIdx] - mat[i][colIdx - 1];
        if (dp[i][colIdx - 1] == temp)
        {
            colIdx = colIdx - 1;
        }
        else if (dp[i][colIdx + 1] == temp)
        {
            colIdx = colIdx + 1;
        }
        path.push_back(mat[i - 1][colIdx - 1]);
    }
    cout << ans << endl;
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
    cout << endl;
    return 0;
}
