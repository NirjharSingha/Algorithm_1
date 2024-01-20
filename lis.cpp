#include <bits/stdc++.h>
using namespace std;
vector<int> getSequence(vector<int>&arr,vector<int> &dp,vector<int>&path, int n) {
    int ans = dp[0], position = 0;
    for (int i = 1; i < n; i++)
    {
        if (ans < dp[i])
        {
            position = i;
            ans = dp[i];
        }
    }

    vector<int> sequence;
    while (position != -1)
    {
        sequence.push_back(arr[position]);
        position = path[position];
    }
    return sequence;
}
vector<int> lis(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1), path(n, -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i] && dp[i] < dp[j] + 1)
            {
                path[i] = j;
                dp[i] = dp[j] + 1;
            }
        }
    }

    vector<int> sequence = getSequence(arr,dp,path,n);

    for (int i = 0; i < n; i++)
    {
        cout << dp[i] << " ";
    }
    cout << endl;
    
    reverse(sequence.begin(),sequence.end());
    return sequence;
}
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> ans = lis(arr);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}
