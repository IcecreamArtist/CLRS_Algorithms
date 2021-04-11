//
// Created by Artist on 2021/4/11.
//

#include<bits/stdc++.h>

using namespace std;

struct Treap {

    struct node {
        int key;
        int priority;
        struct node *lch, *rch;

        node(int i) {
            key = i;
            priority = rand();
            lch = nullptr;
            rch = nullptr;
        }
    };

    node *root = nullptr;

    pair<node *, node *> split(node *u, int key) {
        if (u == nullptr)
            return make_pair(nullptr, nullptr);
        if (key < u->key) {
            pair<node *, node *> o = split(u->lch, key);
            u->lch = o.second;
            return make_pair(o.first, u);
        } else {
            pair<node *, node *> o = split(u->rch, key);
            u->rch = o.first;
            return make_pair(u, o.second);
        }
    }

    node *merge(node *u, node *v) {
        if (u == nullptr) return v;
        if (v == nullptr) return u;
        if (u->priority > v->priority) {
            u->rch = merge(u->rch, v);
            return u;
        } else {
            v->lch = merge(u, v->lch);
            return v;
        }
    }

    int find(node *u, int key) {
        if (u == nullptr) return 0;
        if (key == u->key) return 1;
        if (key < u->key) return find(u->lch, key);
        else return find(u->rch, key);
    }

    void insert(int key) {
        pair<node *, node *> o = split(root, key);
        if (find(root, key) == 0)
            o.first = merge(o.first, new node(key));
        root = merge(o.first, o.second);
    }

    void dfs(node *u) {
        if (u == nullptr) return;
        dfs(u->lch);
        printf("%d ", u->key);
        dfs(u->rch);
    }

    void inorder_display() {
        dfs(root);
    }
};


int main() {
    srand(time(NULL));
    int n;
    printf("please input the sum of node:");
    scanf("%d", &n);
    Treap tree;

    printf("please input the value of node:");
    for (int i = 1; i <= n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        tree.insert(tmp);
    }
    printf("the inorder tra is: ");
    tree.inorder_display();
    printf("\nTreap Tree has been successfully constructed!\n");
}