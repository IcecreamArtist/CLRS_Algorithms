//
// Created by Artis on 2021/4/9.
//

#include <bits/stdc++.h>

using namespace std;

int solve(int n) {
    if (n == 0) return 3;
    int ans = 4 * solve(n - 1);
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", solve(n));
}