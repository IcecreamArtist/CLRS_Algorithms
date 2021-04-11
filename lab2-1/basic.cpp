
#include <bits/stdc++.h>

using namespace std;

int solve(int n) {
    // when the snowflake is in its base shape
    // it is a triangle. therefore, return 3.
    if (n == 0) return 3;
    // otherwise, each edge can be partitioned into four parts
    return 4 * solve(n - 1);
}

int main() {
    int n;
    while(~scanf("%d",&n)&&(n!=-1)){
        printf("%d\n",solve(n));
    }
}