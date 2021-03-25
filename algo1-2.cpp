//
// Created by Artis on 2021/3/25.
//
#include<bits/stdc++.h>
using namespace std;


//int main(){
//    int n,m;cin>>n>>m;
//    for(int i=1;i<=n;++i){
//        for(int j=1;j<=m;++j){
//            cout<<(int)(rand())%100<<" ";
//        }
//        cout<<endl;
//    }
//}
// 用递归来做？
const int maxn = 1e3+3;
int a[maxn][maxn];

int solve(int sx,int sy,int tx,int ty) {
    if()
    int res1 = solve(sx,sy,tx>>1,ty>>1);
    int res2 = solve(tx>>1|1,sy,tx,ty>>1|1);
    int res3 = solve(sx);
    int res4 = solve();
    return ;
}
int main() {
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) scanf("%d",&a[i][j]);
    cout<<solve(1,1,n,m)<<endl;
}