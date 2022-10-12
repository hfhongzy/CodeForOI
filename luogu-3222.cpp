#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 4e5 + 10;

const db eps = 1e-19;
const db inf = 2e9;
#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ((v - u).det(w - u))
struct point {
  db x, y;
  db norm() { return sqrt(x * x + y * y); }
  db norm2() { return x * x + y * y; }
  point operator + (point b) { return (point) {x + b.x, y + b.y}; }
  point operator - (point b) { return (point) {x - b.x, y - b.y}; }
  point operator - () const { return (point) {-x, -y}; }
  void operator += (point b) { *this = *this + b; }
  void operator -= (point b) { *this = *this - b; }
  db operator * (point b) { return x * b.x + y * b.y; }
  point operator * (db b) { return (point) {x * b, y * b}; }
  point operator / (db b) { return (point) {x / b, y / b}; }
  db det(point b) { return x * b.y - y * b.x; }
  bool operator < (point b) { return lt(x, b.x) || (leq(x, b.x) && lt(y, b.y)); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
};
struct line {
  point u, v; db a; int id;
  point vec() { return v - u; }
  db alpha() { return atan2(vec().y, vec().x); }
};
typedef vector<point> VP;
typedef vector<line> VL;
point intersect(line a, line b) {
  a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
//half-plane intersection
//left hand side
bool HPI(VL a, int mid) {
  int n = a.size();
  VL q(n + 1); VP t(n + 1);
  int ql = 0, qr = 0, la = -1;
  for(int i = 0; i < n; i ++) {
    if(a[i].id > mid) continue ;
    if(~la && eq(a[i].a, a[la].a)) continue ;
    la = i;
    if(qr - ql > 1 && eq(q[ql].vec().det(q[ql + 1].vec()), 0)) return 0;
    if(qr - ql > 1 && eq(q[qr - 2].vec().det(q[qr - 1].vec()), 0)) return 0;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[qr - 1]), 0)) qr --;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[ql + 1]), 0)) ql ++;
    q[qr ++] = a[i];
    if(qr - ql > 1) t[qr - 1] = intersect(q[qr - 2], q[qr - 1]);
  }
  while(qr - ql > 1 && lt(cross(q[ql].u, q[ql].v, t[qr - 1]), 0)) qr --;
  return qr - ql > 2;
}
int n, x[N], l[N], r[N];
VL v;
bool check(int mid) {
  return HPI(v, mid);
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    scanf("%d%d%d", x + i, l + i, r + i);
  }
  v.pb({{eps, eps}, {inf, eps}, 0, 0});
  v.pb({{inf, eps}, {inf, inf}, 0, 0});
  v.pb({{inf, inf}, {eps, inf}, 0, 0});
  v.pb({{eps, inf}, {eps, eps}, 0, 0});
  rep(i, 1, n) {
    line a, b;
    a.u = point{0, (db)l[i] / x[i]};
    a.v = point{1, (db)l[i] / x[i] + x[i]};;
    b.v = point{0, (db)r[i] / x[i]};
    b.u = point{1, (db)r[i] / x[i] + x[i]};;
    a.id = b.id = i;
    v.pb(a); v.pb(b);
  }
  for(int i = 0; i < int(v.size()); i ++) v[i].a = v[i].alpha();
  sort(v.begin(), v.end(), [&](line a, line b) {
    return eq(a.a, b.a) ? lt(cross(a.u, a.v, b.u), 0) : lt(a.a, b.a);
  });
  int ans = 0;
  {
    int l = 1, r = n;
    while(l <= r) {
      int mid = (l + r) >> 1;
      if(check(mid)) l = (ans = mid) + 1;
      else r = mid - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}