#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int k;
    cin >> n >> k;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    long long sum = 0;
    long long sum_squares = 0;
    for (int i = 0; i < k; ++i)
    {
        sum += arr[i];
        sum_squares += arr[i]*arr[i];
    }

    long double minVariance = -1;
    for (int i = 0; i < n - k + 1; ++i)
    {
        long double average = sum / (double) k;
        long double variance = 0.0;
        variance = sum_squares + k * average * average - 2.0 * average * sum;
        if (variance < minVariance || minVariance == -1)
        {
            minVariance = variance;
        }

        sum -= arr[i];
        sum_squares -= arr[i]*arr[i];
        if (k + i < n)
        {
            sum += arr[k + i];
            sum_squares += arr[k+i]*arr[k+i];
        }
    }

    cout << fixed << setprecision(12) << minVariance;
}

int main() {
    solve();

    return 0;
}