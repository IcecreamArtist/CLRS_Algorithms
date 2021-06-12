#include<bits/stdc++.h>

using namespace std;

// 快读,用于卡常
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())if (ch == '-')f = -1;
    for (; isdigit(ch); ch = getchar())x = x * 10 + ch - '0';
    return x * f;
}

const int N = 1002;
const double eps = 1e-8; // 控制精度
double a[N][N], ans[N]; // 储存simplex矩阵, 储存答案
int B[N << 1], n, m; // 储存轴位置

void Pivot(int l, int e) {
    swap(B[n + l], B[e]); // 交换基本变量(n+l)与非基本变量(e)
    double t = a[l][e];
    a[l][e] = 1;
    for (int j = 0; j <= n; ++j) a[l][j] /= t;
    for (int i = 0; i <= m; ++i)
        if (i != l && abs(a[i][e]) > eps) {
            t = a[i][e]; // t表示系数
            a[i][e] = 0;
            for (int j = 0; j <= n; ++j) a[i][j] -= t * a[l][j];
            // 消去非基变量
        }
}

bool Simplex() {
    while (true) {
        int l = 0, e = 0;
        double mn = 1e18;
        for (int j = 1; j <= n; ++j)
            if (a[0][j] > eps) {
                e = j;
                break;
            }
        if (!e) return true;
        for (int i = 1; i <= m; ++i)
            if (a[i][e] > eps && a[i][0] / a[i][e] < mn)
                mn = a[i][0] / a[i][e], l = i; // 找到约束最紧的
        if (!l) {
            puts("Unbounded");
            return false;
        }
        Pivot(l, e);
    }
}

bool init() {
    // 寻找初始化解
    while (true) {
        int e = 0, l = 0;
        for (int i = 1; i <= m; ++i)
            if (a[i][0] < -eps && (!l || (rand() & 1))) l = i;
        if (!l) return true;
        for (int j = 1; j <= n; ++j)
            if (a[l][j] < -eps && (!e || (rand() & 1))) e = j;
        if (!e) {
            puts("Infeasible");
            return false;
        }
        Pivot(l, e);
    }
}

void process() {
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        u++, v++;
        a[i][u] = -1; // m条约束,因为是求最小,为转化为标准型,取-1
        a[i][v] = -1;
    }
    for (int i = 1; i <= n; ++i) a[0][i] = -1; // 目标函数,参数取-1
    for (int i = 1; i <= m; ++i) a[i][0] = -1; // 约束条件的右边部分
}

int main() {
    process();
    for (int i = 1; i <= n; ++i) B[i] = i; // 储存轴的位置
    if (init() && Simplex()) {
        //printf("%.8lf\n",a[0][0]);
        for (int i = 1; i <= m; ++i) ans[B[i + n]] = a[i][0];
        //for(int i=1;i<=n;++i) printf("%.2lf ",ans[i]);
        int res = 0;
        vector<int> ress;
        // rounding approach: 最简单的四舍五入
        for (int i = 1; i <= n; ++i) if (round(ans[i]) == 1) res++, ress.push_back(i);
        printf("%d\n", res);
        for (auto i:ress) printf("%d ", i - 1);
    }
    return 0;
}
