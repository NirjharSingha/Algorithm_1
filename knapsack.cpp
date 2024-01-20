#include <bits/stdc++.h>
using namespace std;

int knapSack(int W, int wt[], int val[], int n)
{
    int t[n + 1][W + 1];
    // memset(t, 0, sizeof(t));
    for (int i = 0; i <= n; i++)
    {
        t[i][0] = 0;
    }
    for (int i = 0; i <= W; i++)
    {
        t[0][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (wt[i - 1] <= j)
            {
                if (val[i - 1] + t[i - 1][j - wt[i - 1]] > t[i - 1][j])
                {
                    t[i][j] = val[i - 1] + t[i - 1][j - wt[i - 1]];
                }
                else
                {
                    t[i][j] = t[i - 1][j];
                }
            }
            else
            {
                t[i][j] = t[i - 1][j];
            }
        }
    }

    int i = n;
    int j = W;
    vector<int> chosenItems;

    while (i > 0 && j > 0)
    {
        if (t[i][j] != t[i - 1][j])
        {
            chosenItems.push_back(i);
            j -= wt[i - 1];
        }
        i--;
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
    reverse(chosenItems.begin(), chosenItems.end());
    cout << "Chosen items: ";
    for (int idx : chosenItems)
    {
        cout << idx << " ";
    }
    cout << endl;

    return t[n][W];
}

int main()
{
    int n, W;
    cin >> n >> W;
    int val[n], wt[n];
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
        cin >> val[i];
    }

    int maxValue = knapSack(W, wt, val, n);
    cout << "Max Value: " << maxValue << endl;

    return 0;
}
