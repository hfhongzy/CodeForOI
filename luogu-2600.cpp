#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 610;

const db eps = 1e-7;
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
  point u, v; db a;
  point vec() { return v - u; }
  db alpha() { return atan2(vec().y, vec().x); }
  db val(db x) {
    db k = (u.y - v.y) / (u.x - v.x), b = u.y - k * u.x;
    return k * x + b;
  }
};
typedef vector<point> VP;
typedef vector<line> VL;
point intersect(line a, line b) {
  a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
int ql, qr;
VL q; VP t;
void HPI(VL a) {
  int n = a.size();
  q.resize(n + 1); t.resize(n + 1); ql = 0; qr = 0;
  for(int i = 0; i < n; i ++) a[i].a = a[i].alpha();
  sort(a.begin(), a.end(), [&](line a, line b) {
    return eq(a.a, b.a) ? lt(cross(a.u, a.v, b.u), 0) : lt(a.a, b.a);
  });
  for(int i = 0; i < n; i ++) {
    if(eq(a[i].a, a[i - 1].a)) continue ;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[qr - 1]), 0)) qr --;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[ql + 1]), 0)) ql ++;
    q[qr ++] = a[i];
    if(qr - ql > 1) t[qr - 1] = intersect(q[qr - 2], q[qr - 1]);
  }
  while(qr - ql > 1 && lt(cross(q[ql].u, q[ql].v, t[qr - 1]), 0)) qr --;
}
point a[N];
line b[N];
int n;
int main() {
  scanf("%d", &n);
  vector<db> pos;
  rep(i, 1, n) scanf("%lf", &a[i].x), pos.pb(a[i].x);
  rep(i, 1, n) scanf("%lf", &a[i].y);
  VL s;
  rep(i, 1, n - 1) s.pb(b[i] = (line){a[i], a[i + 1]});
  HPI(s);
  for(int i = ql + 1; i < qr; i ++) pos.pb(t[i].x);
  sort(pos.begin(), pos.end());
  db ans = 1e30;
  int p = ql, p2 = 1;
  for(db x : pos) {
    while(p < qr - 1 && x > t[p + 1].x) p ++;
    while(p2 < n && x > a[p2 + 1].x) p2 ++;
    db c = q[p].val(x) - b[p2].val(x);
    if(c < eps) c = 0;
    ans = min(ans, c);
  }
  printf("%.3f\n", ans);
  return 0;
}