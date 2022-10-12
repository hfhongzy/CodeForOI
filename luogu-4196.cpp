#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1010;

const db eps = 1e-9;
#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ((v - u).det(w - u))
struct point {
  db x, y;
  void in() { scanf("%lf%lf", &x, &y); }
  void in_int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
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
};
typedef vector<point> VP;
typedef vector<line> VL;
point intersect(line a, line b) {
  a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
//polygon area (res > 0 when counter-cw)
db area(VP a) {
  int n = a.size();
  db res = 0;
  for(int i = 0; i < n; i ++)
    res += a[i].det(a[(i + 1) % n]);
  return res * 0.5;
}
//half-plane intersection
//left hand side
VP HPI(VL a) {
  int n = a.size();
  for(int i = 0; i < n; i ++) a[i].a = a[i].alpha();
  sort(a.begin(), a.end(), [&](line a, line b) {
    return eq(a.a, b.a) ? lt(cross(a.u, a.v, b.u), 0) : lt(a.a, b.a);
  });
  VL q(n + 1); VP t(n + 1);
  int ql = 0, qr = 0;
  for(int i = 0; i < n; i ++) {
    if(i && eq(a[i].a, a[i - 1].a)) continue ;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[qr - 1]), 0)) qr --;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[ql + 1]), 0)) ql ++;
    q[qr ++] = a[i];
    if(qr - ql > 1) t[qr - 1] = intersect(q[qr - 2], q[qr - 1]);
  }
  while(qr - ql > 1 && lt(cross(q[ql].u, q[ql].v, t[qr - 1]), 0)) qr --;
  if(qr - ql > 1) t[qr] = intersect(q[ql], q[qr - 1]), qr ++;
  VP res;
  for(int i = ql + 1; i < qr; i ++)
    res.pb(t[i]);
  return res;
}
int main() {
  VL s;
  int p, n, c = 0; scanf("%d", &p);
  for(int T = 1; T <= p; T ++) {
    scanf("%d", &n);
    VP a(n);
    for(int i = 0; i < n; i ++) a[i].in_int();
    for(int i = 0; i < n; i ++)
      s.pb((line){a[i], a[(i + 1) % n]});
  }
  printf("%.3f\n", area(HPI(s)));
  return 0;
}