#include<bits/stdc++.h>
// 树状数组优化:二位偏序
using namespace std;
const int maxn = 5e3 + 3;
vector<pair<int, int> > eve; // 信封
#define h second
#define w first
#define all(x) x.begin(),x.end()

int n;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.w == b.w) return a.h < b.h;
    else return a.w < b.w;
}

void solve() {
    scanf("%d", &n);
    eve.clear();
    vector<pair<int, int> > dp(maxn, make_pair(1 << 30, 1 << 30));
    for (int i = 1, w, h; i <= n; ++i) scanf("%d%d", &w, &h), eve.push_back(make_pair(w, h));
    sort(all(eve), cmp);
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(all(dp), eve[i], cmp) - dp.begin();
        if (pos && (dp[pos - 1].w == eve[i].w || dp[pos - 1].h == eve[i].h)) continue; // 不加
        dp[pos] = eve[i];
    }

    printf("%d\n", lower_bound(all(dp), make_pair(1 << 30, 1 << 30)) - dp.begin());
}

/*
 * 2 3/ 5 4/ 6 4/ 6 7
1
4
5 4
6 4
6 7
2 3

 */
int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}