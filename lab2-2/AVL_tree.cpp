//
// Created by Artist on 2021/4/10.
//

#include<bits/stdc++.h>

using namespace std;
const int maxn = 22;

struct AVL {
    int tot; // 总共的节点数
    struct _node {
        int val;
        int bal; // balance value, left - right
        int lson, rson;
        int h; // height

        _node(int Val = 0, int Bal = 0, int Lson = 0, int Rson = 0, int H = 0) {
            val = Val;
            bal = Bal;
            lson = Lson;
            rson = Rson;
            h = H;
        }
    } node[maxn];

    void init(int n) {
        tot = 0;
        node[0].h = -1; // 高度初始化为-1
    }

    void leftrotate(int u) {
        // 左旋
        int rson = node[u].rson;
        _node tmp = node[u];
        node[u].lson = rson;
        node[u].rson = node[rson].rson;
        node[u].val = node[rson].val;

        node[rson].val = tmp.val;
        node[rson].lson = tmp.lson;
        node[rson].rson = node[rson].lson;

        node[rson].h = max(node[node[rson].lson].h, node[node[rson].rson].h) + 1;
        node[u].h = max(node[node[u].lson].h, node[node[u].rson].h) + 1;
    }

    void rightrotate(int u) {
        // 右旋
        int lson = node[u].lson; // 左儿子序号
        _node tmp = node[u]; // 暂存内部信息
        node[u].lson = node[lson].lson;
        node[u].rson = lson;
        node[u].val = node[lson].val;

        node[lson].lson = node[lson].rson;
        node[lson].rson = tmp.rson;
        node[lson].val = tmp.val;

        node[lson].h = max(node[node[lson].lson].h, node[node[lson].rson].h) + 1;
        node[u].h = max(node[node[u].lson].h, node[node[u].rson].h) + 1;
    }

    void balance(int u) {
        node[u].h = max(node[node[u].lson].h, node[node[u].rson].h) + 1;
        node[u].bal = node[node[u].lson].h - node[node[u].rson].h;

        if (node[u].bal > 1) {
            // 左重
            if (node[node[u].lson].bal > 0) {
                // LL
                rightrotate(u);
            } else {
                // LR
                leftrotate(node[u].lson);
                rightrotate(u);
            }
        }
        if (node[u].bal < -1) {
            // 右重
            if (node[node[u].rson].bal <= 0) {
                // RR
                leftrotate(u);
            } else {
                // RL
                rightrotate(node[u].rson);
                leftrotate(u);
            }
        }
    }

    void dfs(int u, int opt) {
        if (node[u].lson) dfs(node[u].lson, opt);
        if (opt) printf("%d ", node[u].val);
        else printf("%d ", node[node[u].lson].h - node[node[u].rson].h);
        if (node[u].rson) dfs(node[u].rson, opt);
    }

    void insert(int u, int val) {
        if (!node[1].val) {
            // build tree
            node[++tot] = _node(val, 0, 0, 0, 0);
            return;
        }
        if (node[u].val == val) {
            return;
        } else if (node[u].val > val) {
            if (node[u].lson) insert(node[u].lson, val);
            else {
                node[u].lson = ++tot;
                node[tot] = _node(val, 0, 0, 0, 0);
            }
        } else {
            if (node[u].rson) insert(node[u].rson, val);
            else {
                node[u].rson = ++tot;
                node[tot] = _node(val, 0, 0, 0, 0);
            }
        }
        // trace back
        balance(u);
    }
};

int main() {
    int n;
    printf("please input the sum of node:");
    scanf("%d", &n);
    AVL tree;
    tree.init(n);

    printf("please input the value of node:");
    for (int i = 1; i <= n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        tree.insert(1, tmp);
    }
    printf("the inorder tra is: ");
    tree.dfs(1, 1);
    printf("\nthe bf(balance flag) of each node: ");
    tree.dfs(1, 0);
    printf("\nAVL Tree has been successfully constructed!\n");
}