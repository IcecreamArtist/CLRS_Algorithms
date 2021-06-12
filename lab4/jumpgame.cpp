#include<bits/stdc++.h>

using namespace std;

#define fast std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
// 加速cin和cout

int main() {
    fast;
    int t; // multiple test cases
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);  // 数组
        for (auto &i:a) cin >> i; // 输入
        int dp = 0;
        for (int i = 0;;) {   // 循环
            int nxt = 0, mx = 0; // 下一个位置;可以走最远的距离
            if (i == n - 1) break;  // 如果已经走到了目的地,break
            if (a[i] == 0) {  // 如果当前位置不能走,说明无法抵达,break
                dp = -1;
                break;
            }
            //  贪心地选择当前能抵达的位置中,能走的最远的位置,作为下一个位置
            for (int j = 1; j <= a[i]; ++j) {
                if (i + j >= n) break;
                if (a[i + j] + i + j > mx) nxt = i + j, mx = a[i + j] + i + j;
            }
            dp++; // 步数
            i = nxt; // 更新位置
        }
        cout << dp << endl;
    }
}