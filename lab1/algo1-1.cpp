#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;


ll cal(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    return cal(n - 1) + cal(n - 2);
}

ll cal2(int n) {
    if (n == 1) return 1;
    ll ans[2];
    ans[0] = 2, ans[1] = 1;
    int t = 0;
    for (int i = 3; i <= n; ++i) {
        ans[t ^ 1] = (ans[t] + ans[t ^ 1]) % mod;
        t ^= 1;
    }
    return ans[t];
}

double fastm(double a,int n){
    double ans = 1.0;
    while(n){
        if(n&1) ans = a*ans;
        a=a*a;
        n>>=1;
    }
    return ans;
}

// 公式计算
ll cal3(int n){
    double root5 = sqrt(5);
    return (ll)((1+root5)/(2*root5)*fastm((1+root5)/2,n)+(3-root5)/(5-root5)*fastm((1-root5)/2,n));
}

// 矩阵快速幂计算
/*
 * [x_2, x_1]   [ 1 , 1  ]^(n-2)
 * [ 0 ,  0 ]   [ 1 , 0  ]
 *
 */

struct Matrix {
    ll m[2][2];

    Matrix() {
        memset(m, 0, sizeof(m));
    }
};

Matrix Multi(Matrix a, Matrix b) {
    Matrix res;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return res;
}

Matrix fastm(Matrix a, int n) {
    Matrix res;
    for (int i = 0; i < 2; ++i) res.m[i][i] = 1;
    while (n) {
        if (n & 1) res = Multi(res, a);
        a = Multi(a, a);
        n >>= 1;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
   // cout << cal(n) << endl;
   // cout << cal2(n) << endl;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    if (n == 2) {
        cout << 2 << endl;
        return 0;
    }
    cout<<cal3(n)<<endl;
    /*
    Matrix cur, pro;
    cur.m[0][0] = 2, cur.m[0][1] = 1;
    pro.m[0][0] = pro.m[0][1] = pro.m[1][0] = 1;
    cout << Multi(cur, fastm(pro, n - 2)).m[0][0] << endl;
     */

}
