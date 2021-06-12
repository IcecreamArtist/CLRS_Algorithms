#include<bits/stdc++.h>

using namespace std;

// 快速读入,用于减小复杂度常数
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())if (ch == '-')f = -1;
    for (; isdigit(ch); ch = getchar())x = x * 10 + ch - '0';
    return x * f;
}

int n, m;
int adj[103][103]; // 邻接矩阵存图


int main() {
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        u++, v++; // 程序中以1开始编号
        adj[u][v] = adj[v][u] = 1;
    }
    int res = 0;
    vector<int> ans;  // 用来储存feasible solution的点集
    while (1) {
        // 每个点的度数, 最大度数的点的度数, 最大度数的点的编号
        int d[104], mx = 0, id;
        for (int i = 1; i <= n; ++i) d[i] = 0; // 清空
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (adj[i][j]) d[i]++; // 对每个点计算剩余图的度数
            }
            if (d[i] > mx) id = i, mx = d[i];
        }
        if (mx == 0) break; // 如果图已空
        res++; // 加入该点
        ans.push_back(id);
        for (int i = 1; i <= n; ++i)  // 删掉该点连接的边
            if (adj[id][i] == 1) adj[i][id] = adj[id][i] = 0;
    }
    printf("%d\n", res);
    for (auto i:ans) printf("%d ", i - 1);
    return 0;
}
