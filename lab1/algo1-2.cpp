//
// Created by Artis on 2021/3/25.
//
#include<bits/stdc++.h>

using namespace std;


const int maxn = 1e3 + 3;
int a[maxn][maxn];

pair<int, int> solve(int sx, int sy, int tx, int ty) {
    int mx = (sx + tx) >> 1, my = (sy + ty) >> 1;//中间列
    int maxx = 0;
    int posx, posy;
    for (int i = sx; i <= tx; ++i) if (a[i][my] > maxx) maxx = a[i][my], posx = i, posy = my;
    for (int j = sy; j <= ty; ++j) if (a[mx][j] > maxx) maxx = a[mx][j], posx = mx, posy = j;
    if (posx == mx && posy == my) return make_pair(posx, posy);
    if (posx == mx) {
        if ((posx == sx || a[posx - 1][posy] <= a[posx][posy]) &&
            (posx == tx || a[posx + 1][posy] <= a[posx][posy]))
            return make_pair(posx, posy);
        if (posx != sx && a[posx - 1][posy] > a[posx][posy]) {
            if (posy <= my) return solve(sx, sy, mx - 1, my - 1);
            else return solve(sx, my + 1, mx - 1, ty);
        } else {
            if (posy <= my) return solve(mx + 1, sy, tx, my - 1);
            else return solve(mx + 1, my + 1, tx, ty);
        }
    } else {
        if ((posy == sy || a[posx][posy - 1] <= a[posx][posy]) &&
            (posy == ty || a[posx][posy + 1] <= a[posx][posy]))
            return make_pair(posx, posy);
        if (posy != sy && a[posx][posy - 1] > a[posx][posy]) {
            if (posx <= mx) return solve(sx, sy, mx - 1, my - 1);
            else return solve(mx + 1, sy, tx, my - 1);
        } else {
            if (posx <= mx) return solve(sx, my + 1, mx - 1, ty);
            else return solve(mx + 1, my + 1, tx, ty);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    //cout << n << " " << m << endl;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
    //for (int i = 1; i <= n; ++i, cout << endl) for (int j = 1; j <= m; ++j) cout << a[i][j] << " ";

    pair<int, int> res = solve(1, 1, n, m);
    cout << res.first << " " << res.second << endl;
}

int main() {
    int t;
    cin >> t;
    cout << t << endl;
    while (t--) solve();
}