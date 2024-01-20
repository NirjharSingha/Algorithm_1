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

int matrixMultiplication(int N, int arr[], vector<vector<int>> &t, vector<vector<int>> &parenthetical, int i, int j)
{
    if (t[i][j] < INT_MAX)
    {
        return t[i][j];
    }
    if (i == j)
    {
        return t[i][j] = 0;
    }
    int mn = 1e9;
    for (int k = i; k < j; k++)
    {
        int temp = arr[i - 1] * arr[k] * arr[j] +
                   matrixMultiplication(N, arr, t, parenthetical, i, k) + matrixMultiplication(N, arr, t, parenthetical, k + 1, j);
        if (temp < mn)
        {
            mn = temp;
            parenthetical[i][j] = k;
        }
    }
    return t[i][j] = mn;
}

int main()
{
    int N;
    cin >> N;
    int arr[N]; // Example matrix dimensions
    int mn = 1e9, temp, i, j, k;
    vector<vector<int>> parenthetical(N, vector<int>(N, -1)), t(N, vector<int>(N, INT_MAX)); // To store optimal split positions
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    matrixMultiplication(N, arr, t, parenthetical, 1, N - 1);

    cout << "Optimal Parenthetical Arrangement: ";
    printOptimalParentheses(1, N - 1, parenthetical);
    cout << endl;
    cout << "Minimum Multiplication Cost: " << t[1][N - 1] << endl;

    return 0;
}
