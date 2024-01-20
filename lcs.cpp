#include <bits/stdc++.h>
using namespace std;

int lcs(int x, int y, string s1, string s2)
{
    int dp[x + 1][y + 1];
    memset(dp,0,sizeof(dp));
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    string ans = "";
    int i = x, j = y;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            ans.push_back(s1[i - 1]);
            i--;
            j--;
        }
        else
        {
            if (dp[i][j] == dp[i - 1][j])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
    }
    for (int i = 0; i <= x; i++)
    {
        for (int j = 0; j <= y; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    reverse(ans.begin(), ans.end());
    cout << ans.length() << endl;
    cout << ans << endl;
    return dp[x][y];
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    lcs(s1.length(), s2.length(), s1, s2);
    return 0;
}
