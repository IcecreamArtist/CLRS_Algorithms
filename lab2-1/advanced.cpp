//
// Created by Artis on 2021/4/10.
//

#include<bits/stdc++.h>

using namespace std;

char mp[14000][14000];
int x, y;  // initial position
int maxx, maxy;
// maximum row, maximum column

void print(int i, int j, char ch) {
    // note that the ascii '\' and '/' have different size
    // therefore, '_' may need to be overwritten.
    if (mp[i][j] == ' ' || mp[i][j] == '_')
        mp[i][j] = ch;
}

void solve(int n, int di) {
    // number and direction
    if (n == 0) {
        switch (di) {
            case 0:
                print(x, y++, '_');
                print(x, y++, '_');
                break;
            case 1:
                print(++x, y++, '\\');
                break;
            case 2:
                print(++x, --y, '/');
                break;
            case 3:
                print(x, --y, '_');  // this or the next '_' will be overwritten
                print(x, --y, '_');
                break;
            case 4:
                print(x--, --y, '\\');
                break;
            case 5:
                print(x--, y++, '/');
                break;
        }
        maxx = max(maxx, x);
        maxy = max(maxy, y);
        return;
    }
    solve(n - 1, di);
    solve(n - 1, (di + 5) % 6);
    solve(n - 1, (di + 1) % 6);
    solve(n - 1, di);
}

int main() {
    int n;
    scanf("%d", &n);
    // print the picture into a file(since the terminal cannot display such large picture well)
    freopen("out.txt", "w", stdout);
    // calculate the initial x position
    if (n > 1) {
        int tmp = n;
        x = 1;
        while (tmp > 1) {
            tmp--;
            x *= 3;
        }
        x--;
    }
    memset(mp, ' ', sizeof(mp));
    solve(n, 0);
    solve(n, 2);
    solve(n, 4);
    for (int i = 0; i <= maxx; ++i) {
        for (int j = 0; j <= maxy; ++j) {
            cout << mp[i][j];
        }
        cout << endl;
    }
}