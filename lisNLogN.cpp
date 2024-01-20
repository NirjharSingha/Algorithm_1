#include <bits/stdc++.h>
using namespace std;
int binarySearch(vector<int> &temp, int x, int r)
{
    int l = 1, mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (temp[mid] >= x && temp[mid - 1] < x)
        {
            return mid;
        }
        else if (temp[mid] < x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return 0;
}
int longestIncreasingSubsequence(int arr[], int n)
{
    vector<int> temp;
    int sz = 1, mx = 1, p;
    temp.push_back(arr[0]);
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > temp.back())
        {
            temp.push_back(arr[i]);
            sz++;
        }
        else
        {
            int p = binarySearch(temp, arr[i], sz - 1);
            // p=lower_bound(temp.begin(), temp.end(), arr[i])-temp.begin();
            temp[p] = arr[i];
        }
    }
    return sz;
}
