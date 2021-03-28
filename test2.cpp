//
// Created by Artis on 2021/3/28.
//

#include<bits/stdc++.h>

using namespace std;

int mp[1003][1003];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &mp[i][j]);
            }
        }
        int x, y;
        cin >> x >> y;
        int flg = 0;
        if (x > 1 && mp[x][y] < mp[x - 1][y]) flg = 1;
        if (y > 1 && mp[x][y] < mp[x][y - 1]) flg = 1;
        if (x < n && mp[x][y] < mp[x + 1][y]) flg = 1;
        if (y < m && mp[x][y] < mp[x][y + 1]) flg = 1;
        if (flg) cout << "wrong" << endl;
        else cout << "correct" << endl;
    }

}