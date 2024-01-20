#include <bits/stdc++.h>
using namespace std;

void printOptimalParentheses(int i, int j, vector<vector<int>> &parenthetical)
{
    if (i == j)
    {
        cout << (char)(65 + i - 1);
    }
    else
    {
        cout << "(";
        printOptimalParentheses(i, parenthetical[i][j], parenthetical);
        printOptimalParentheses(parenthetical[i][j] + 1, j, parenthetical);
        cout << ")";
    }
}

int matrixMultiplication(int N, int arr[])
{
    int t[N][N], mn = 1e9, temp, i, j, k;
    vector<vector<int>> parenthetical(N, vector<int>(N, -1)); // To store optimal split positions
    memset(t, 0, sizeof(t));

    for (i = 1; i < N; i++)
    {
        t[i][i] = 0;
    }

    for (i = N - 1; i > 0; i--)
    {
        for (j = i + 1; j < N; j++)
        {
            mn = 1e9;
            for (k = i; k < j; k++)
            {
                temp = arr[i - 1] * arr[k] * arr[j] +
                       t[i][k] + t[k + 1][j];
                if (temp < mn)
                {
                    mn = temp;
                    parenthetical[i][j] = k;
                }
            }
            t[i][j] = mn;
        }
    }

    cout << "Optimal Parenthetical Arrangement: ";
    printOptimalParentheses(1, N - 1, parenthetical);
    cout << endl;
    cout << "Minimum Multiplication Cost: " << t[1][N - 1] << endl;

    cout << "dp table" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
    cout << "parent table" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << parenthetical[i][j] << " ";
        }
        cout << endl;
    }

    return t[1][N - 1];
}

int main()
{
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int result = matrixMultiplication(N, arr);

    return 0;
}
