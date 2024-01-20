#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int cutRod(int price[], int n)
{
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            dp[i] = max(price[j - 1] + dp[i - j], dp[i]);
        }
    }
    return dp[n];
}

int main()
{
    int n;
    cin >> n;
    int price[n];
    for (int i = 0; i < n; i++)
    {
        cin >> price[i];
    }
    auto t1 = high_resolution_clock::now();
    int ans = cutRod(price, n);
    auto t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1);

    cout << "result : " << ans << endl;
    cout << "runtime in microseconds : " << duration.count() << endl;

    return 0;
}