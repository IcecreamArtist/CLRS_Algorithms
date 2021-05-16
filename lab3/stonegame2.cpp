#include<bits/stdc++.h>

using namespace std;
const int maxn = 504;
typedef long long ll;
#define fo(i, a, b) for(int i=(a);i<=(b);++i)
int sto[maxn];
ll sum[maxn];
int g[maxn][maxn];
ll lef[maxn][maxn], rig[maxn][maxn];
// dp为答案;sum记录前缀和;g记录区间[i,j]的分界点位置
// lef记录从某一特定i开始,[i,j]答案的最大值
// rig记录从某一特定j开始,[i,j]答案的最大值(与dp数组相互补充,
// 为后续更新dp作优化准备)

void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &sto[i]);
        sum[i] = sum[i - 1] + sto[i];
    }
    // 初始化
    ll dp;
    fo(i, 1, n) fo(j, 1, n) dp = 0, g[i][j] = 0, lef[i][j] = 0, rig[i][j] = 0;
    // 预处理g数组,即区间[i,j]的分界点位置.
    // 使用队列,因为g[i,j]具有单调性,可以将复杂度均摊为O(n^2)
    queue<int> q;
    fo(i, 1, n) {
        while (!q.empty()) q.pop();
        q.push(i);
        fo(j, i + 1, n) {
            q.push(j);
            g[i][j] = g[i][j - 1];
            // 利用了前缀和
            while ((sum[q.front()] - sum[i - 1]) * 2 <= sum[j] - sum[i - 1]) {
                g[i][j] = q.front();
                q.pop();
            }
            // g[i][j]为最后一个小于等于[i,j]区间和的一半的下标位置
        }
    }
    // 自底向上dp,枚举区间长度,再枚举区间起点i
    fo(len, 1, n - 1) fo(i, 1, n - len) {
            lef[i][i] = rig[i][i] = sto[i];
            int j = i + len;
            int mid = g[i][j];
            dp = 0;
            // 若该值介于i,j之中,则可以更新
            if (i <= mid)
                dp = max(dp, lef[i][mid]);
            if (mid + 2 <= j)
                dp = max(dp, rig[mid + 2][j]);
            // 若左右两个部分长度相等,特判,再次更新
            if ((sum[mid] - sum[i - 1]) * 2 == sum[j] - sum[i - 1])
                dp = max(dp, rig[mid + 1][j]);
            // 与dp数组并行处理,为dp数组的计算提供优化
            lef[i][j] = max(lef[i][j - 1], sum[j] - sum[i - 1] + dp);
            rig[i][j] = max(rig[i + 1][j], sum[j] - sum[i - 1] + dp);
        }

    printf("%lld\n", dp);
}


int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}