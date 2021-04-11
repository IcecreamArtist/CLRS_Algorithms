//
// 一直没过，觉得烦人，没耐心了，存档
//
# include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
int sgn(double x) {if(fabs(x)<eps) return 0;return x<0?-1:1;}

struct Point {
    int id;
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    Point operator + (Point B){return Point(x+B.x,y+B.y);}
    Point operator - (Point B){return Point(x-B.x,y-B.y);}
    bool operator == (Point B){return sgn(x-B.x)==0&&sgn(y-B.y)==0;}
    bool operator < (Point B){
        if(sgn(x-B.x) != 0) return sgn(x-B.x) < 0;
        if(sgn(y-B.y) != 0) return sgn(y-B.y) < 0;
        return id < B.id;
    }
} po[200004];

typedef Point Vector;

double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}

int Convex_hull(Point *p, int n, Point *ch) {
    sort(p,p+n);
    int cnt=0;
    for(int i=1;i<n;i++)  //去相同点
        if(p[cnt].x!=p[i].x||p[cnt].y!=p[i].y)
            p[++cnt]=p[i];
    n = cnt + 1;

    int v = 0;
    // 上凸包
    for(int i=0;i<n;++i) {
        while(v>1 && sgn(Cross(ch[v-1]-ch[v-2],p[i]-ch[v-2])) > 0)
            v--;
        ch[v++] = p[i];
    }
    return v; // 凸包顶点数
}

Point conv[200005];

int main () {
    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        for (int i = 0;i<n;++i) {
            po[i].id=i+1;
            scanf("%lf%lf",&po[i].x,&po[i].y);
        }
        int num = Convex_hull(po,n,conv);
        for (int i = 0;i<num-1;++i) {
            cout << conv[i].id << " ";
        }
        cout << conv[num-1].id << endl;
    }
}

