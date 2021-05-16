#include<bits/stdc++.h>

using namespace std;
const int maxn = 504;
typedef long long ll;
#define fo(i, a, b) for(int i=(a);i<=(b);++i)
int sto[maxn];
ll dp[maxn][maxn];
ll sum[maxn];
// 由于该算法for循环较多，为了使代码简洁明了，使用了宏定义
// 将for循环用fo表示
// dp代表区间为[i,j]的答案. sum代表前缀和.

void solve() {
    int n;
    scanf("%d", &n);
    fo(i, 1, n) {
        scanf("%d", &sto[i]);
        sum[i] = sum[i - 1] + sto[i];
    }
    fo(i, 1, n) fo(j, 1, n) dp[i][j] = 0; // 初始化
    fo(len, 1, n - 1) fo(i, 1, n - len) {
            int j = i + len;
            // 先枚举区间长度,再枚举起始点i
            fo(k, i, j - 1) {
                // 枚举分界点
                // a[i]~a[k],a[k+1]~a[j]
                ll leftsum = sum[k] - sum[i - 1];
                ll rightsum = sum[j] - sum[k];
                // 模拟题目给的得分流程
                if (leftsum > rightsum)
                    dp[i][j] = max(dp[i][j], rightsum + dp[k + 1][j]);
                else if (leftsum < rightsum)
                    dp[i][j] = max(dp[i][j], leftsum + dp[i][k]);
                else
                    dp[i][j] = max({dp[i][j], leftsum + dp[i][k],\
                rightsum + dp[k + 1][j]});
            }
        }
    // 答案为dp[1][n]
    printf("%lld\n", dp[1][n]);
}

int main() {
    int t;
    scanf("%d", &t);  // 多次输入
    while (t--) solve();
}