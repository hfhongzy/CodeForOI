#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1e5 + 5;

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
  point rot90() { return point{y, -x}; }
  bool operator < (point b) { return lt(x, b.x) || (leq(x, b.x) && lt(y, b.y)); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
} a[N];
struct line {
  point u, v;
};
typedef vector<point> VP;
typedef vector<line> VL;
point intersect(line a, line b) {
  // a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
struct circle {
  point o; db r;
  bool inc(point d) {
    return leq((d - o).norm2(), r * r);
  }
} c;
int n;
circle circum_circle(point a, point b, point c) {
  circle C;
  C.o = intersect(line{(b + a) / 2, (b - a).rot90()}, line{(c + a) / 2, (c - a).rot90()});
  C.r = (C.o - a).norm();
  return C;
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) a[i].in();
  random_shuffle(a + 1, a + n + 1);
  rep(i, 1, n) {
    if(!c.inc(a[i])) {
      c = {a[i], 0};
      rep(j, 1, i - 1) if(!c.inc(a[j])) {
        c = {(a[i] + a[j]) / 2, (a[i] - a[j]).norm() / 2};
        rep(k, 1, j - 1) if(!c.inc(a[k])) {
          c = circum_circle(a[i], a[j], a[k]);
        }
      }
    }
  }
  printf("%.10f\n%.10f %.10f\n", c.r, c.o.x, c.o.y);
  return 0;
}