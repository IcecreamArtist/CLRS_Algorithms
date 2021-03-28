//
// Created by Artis on 2021/3/28.
//

#include<bits/stdc++.h>

using namespace std;

int mp[1002][1002];

int main() {
    int t = 30;
    cout << t << endl;
    while (t--) {
        int n = ((int) rand()) % 988 + 5;
        int m = ((int) rand()) % 988 + 5;
        cout << n << " " << m << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                mp[i][j] = ((int) rand()) % 988 + 5;
                cout << mp[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}