#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 2e5 + 10;

const db eps = 1e-11;
#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ((v - u).det(w - u))
struct point {
  db x, y;
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
  return res;
}
//half-plane intersection
//left hand side
VP HPI(VL a) {
  int n = a.size();
  for(int i = 0; i < n; i ++) a[i].a = a[i].alpha();
  sort(a.begin(), a.end(), [&](line a, line b) {
    return eq(a.a, b.a) ? lt(cross(a.u, a.v, b.u), 0) : lt(a.a, b.a);
  });
  VL q(n + 1); VP t(n + 1); VP res;
  int ql = 0, qr = 0;
  for(int i = 0; i < n; i ++) {
    if(i && eq(a[i].a, a[i - 1].a)) continue ;
    if(qr - ql > 1 && eq(q[ql].vec().det(q[ql + 1].vec()), 0)) return res;
    if(qr - ql > 1 && eq(q[qr - 2].vec().det(q[qr - 1].vec()), 0)) return res;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[qr - 1]), 0)) qr --;
    while(qr - ql > 1 && lt(cross(a[i].u, a[i].v, t[ql + 1]), 0)) ql ++;
    q[qr ++] = a[i];
    if(qr - ql > 1) t[qr - 1] = intersect(q[qr - 2], q[qr - 1]);
  }
  while(qr - ql > 1 && lt(cross(q[ql].u, q[ql].v, t[qr - 1]), 0)) qr --;
  if(qr - ql > 1) t[qr] = intersect(q[ql], q[qr - 1]), qr ++;
  
  for(int i = ql + 1; i < qr; i ++)
    res.pb(t[i]);
  return res;
}
VL con;
void addline(db A, db B, db C) { //Ax + By + C <= 0
  if(eq(A, 0) && eq(B, 0)) {
    if(lt(C, 0)) return ;
    puts("0.0000"); exit(0);
  }
  if(eq(B, 0)) {
    db x0 = -C / A;
    if(lt(A, 0)) con.pb(line{{x0, 1}, {x0, 0}});
    else con.pb(line{{x0, 0}, {x0, 1}});
    return ;
  }
  if(lt(B, 0)) {
    A = -A; B = -B; C = -C; //Ax + By + C >= 0
    con.pb(line{{0, -C/B}, {B, -C/B - A}});
  } else {
    con.pb(line{{B, -C/B - A}, {0, -C/B}});
  }
}
int main() {
  int n;
  scanf("%d", &n);
  VP a(n);
  for(int i = 0; i < n; i ++) a[i].in_int();
  db sum = area(a);
  a.pb(a[0]);
  for(int i = 0; i < n; i ++) con.pb(line{a[i], a[i + 1]});
  for(int i = 1; i < n; i ++) {
    db A = a[0].y - a[1].y - (a[i].y - a[i + 1].y);
    db B = a[1].x - a[0].x - (a[i + 1].x - a[i].x);
    db C = a[0].x * a[1].y - a[1].x * a[0].y - (a[i].x * a[i + 1].y - a[i + 1].x * a[i].y);
    addline(A, B, C);
  }
  db o = area(HPI(con));
  printf("%.4Lf\n", o / sum);
  return 0;
}