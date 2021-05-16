//
// 二维偏序(LIS)
//

#include<bits/stdc++.h>

using namespace std;
const int maxn = 5e3 + 3;
vector<pair<int, int> > eve; // 信封
#define h second
#define w first
int dp[maxn];

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.w == b.w) return a.h < b.h;
    else return a.w < b.w;
}

void solve() {
    int n;
    scanf("%d", &n);
    eve.clear();
    for (int i = 0; i < n; ++i) dp[i] = 0;
    for (int i = 1, w, h; i <= n; ++i) scanf("%d%d", &w, &h), eve.push_back(make_pair(w, h));
    sort(eve.begin(), eve.end(), cmp);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (eve[j].w < eve[i].w && eve[j].h < eve[i].h)
                dp[i] = max(dp[i], dp[j] + 1);
    int ans = 0;
    for (int i = 0; i < n; ++i) ans = max(dp[i], ans);
    printf("%d\n", ans + 1);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}