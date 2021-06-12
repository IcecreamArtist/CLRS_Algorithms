#include<bits/stdc++.h>

using namespace std;
#define fast std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int inf = 0x7f7f7f7f;

int main() {
    fast;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> dp(n, inf); // 最少的数目能到这个位置,初始化为无穷
        for (auto &i:a) cin >> i; // 输入
        dp[0] = 0; // base case
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= a[i]; ++j) { // 遍历后面能抵达的位置
                if (i + j >= n) break;
                dp[i + j] = min(dp[i + j], dp[i] + 1); // 向后更新
            }
        }
        if (dp[n - 1] != inf) cout << dp[n - 1] << endl;
        else cout << -1 << endl;  // 如果不能抵达
    }
}