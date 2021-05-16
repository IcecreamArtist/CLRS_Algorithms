#include<bits/stdc++.h>
// 树状数组优化:二位偏序
using namespace std;
const int maxn = 5e3 + 3;
vector<pair<int, int> > eve; // 信封
#define h second
#define w first
#define lowbit(x) ((x)&-(x))
int tree[maxn];
int n;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.w == b.w) return a.h < b.h;
    else return a.w < b.w;
}

void add(int x, int d) {
    while (x <= n) {
        tree[x] = max(tree[x], d);
        x += lowbit(x);
    }
}

int query(int x) {
    int maxx = 0;
    while (x > 0) {
        maxx = max(maxx, tree[x]);
        x -= lowbit(x);
    }
    return maxx;
}

void solve() {
    scanf("%d", &n);
    eve.clear();
    for (int i = 0; i <= n; ++i) tree[i] = 0;
    for (int i = 1, w, h; i <= n; ++i) scanf("%d%d", &w, &h), eve.push_back(make_pair(w, h));
    sort(eve.begin(), eve.end(), cmp);
    int ans = 0, cur;
    queue<pair<int, int> > q;
    // 均摊时间复杂度O(nlgn)
    for (int i = 0; i < eve.size(); ++i) { // 在这之前， 比他宽度小
        if (i != 0 && eve[i].w != eve[i - 1].w)
            while (!q.empty()) {
                add(q.front().first, q.front().second);
                q.pop();
            }
        cur = query(eve[i].h - 1);   // 比他高度小
        cur++;
        q.push(make_pair(eve[i].h, cur));
        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}