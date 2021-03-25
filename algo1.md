# Problem 1-1

## code

```c++
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

// sol1: 普通递归，O(2^n)
ll cal(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    return cal(n - 1) + cal(n - 2);
}

// sol2: 递推，O(n)
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

// sol3: 矩阵快速幂计算，O(lg n)
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

// 矩阵乘法
Matrix Multi(Matrix a, Matrix b) {
    Matrix res;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return res;
}

// 快速幂
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
    Matrix cur, pro;
    cur.m[0][0] = 2, cur.m[0][1] = 1;
    pro.m[0][0] = pro.m[0][1] = pro.m[1][0] = 1;
    cout << Multi(cur, fastm(pro, n - 2)).m[0][0] << endl;
}

```
## Results

![img_1.png](img_1.png)

![img_2.png](img_2.png)

![img_3.png](img_3.png)

![img_4.png](img_4.png)

![img_5.png](img_5.png)

![img_6.png](img_6.png)

![img_7.png](img_7.png)

we can also input numbers that are larger than the size of integer since the time complexity is O(lg n).

## Algorithm description

for solution 1:

We use recursion to solve the problem. To climb to the $n$ th step, there are two situations, one is to take one step from the $n-1$ th step, and the second is to take two steps from the $n-2$ th step. Then the problem switches to climb the $n-1$ th and $n-2$ th step.

$$f(x) = f(x-1) + f(x-2)$$

However, since this solution will divide a function into two function with only slightly small size, it will take $O(2^n)$ time to solve, which is really slow. (space complexity is also $O(2^n), since we invoke that much functions$)

## Other solutions

for solution 2:

As stated above, this problem can be divided into two sub-problems, and the two have the parameters smaller than the original function's parameter for only 1. Moreover, the two sub-problems are crossed with each other. Therefore, we can write a linear for-loop and use only two space to store the intermediate values. For convenience, I use XOR operation to switch between the two space.
The time complexity is $O(n)$, and space complexity is $O(1)$.

for solution 3:

We can find that this linear recurrence relation can be represented by matrix multiplication:
