#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 10005;
const db pi = acos(-1);
const db eps = 1e-9;
const db COS = cos(pi / 100);
const db SIN = sin(pi / 100);
#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ((v - u).det(w - u))
mt19937 mt(time(0));
uniform_real_distribution<double> ran(- 0.5 * eps, 0.5 * eps);
struct point {
  db x, y;
  void in() { scanf("%lf%lf", &x, &y); }
  void in_int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
  void out() { printf("%lf %lf!\n", x, y); }
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
  point rot90() { return point{-y, x}; }
  point rot(db t) { return point{x * COS - y * SIN, x * SIN + y * COS}; }
  bool operator < (point b) const { return x < b.x; }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
  void perturb() { x += ran(mt); y += ran(mt); }
} a[N];
struct line { point u, v; };
typedef vector<point> VP;
typedef vector<line> VL;
point intersect(line a, line b) {
  // a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
struct circle {
  point o; db r;
  bool inc(point d) { return leq((d - o).norm2(), r); }
};
int n;
circle circum_circle(point a, point b, point c) {
  circle C;
  C.o = intersect(line{(b + a) * 0.5, (b - a).rot90()}, line{(c + a) * 0.5, (c - a).rot90()});
  C.r = (C.o - a).norm2();
  return C;
}
db min_circle_cover(const point *b, int n) {
  if(n == 0) return 0;
  static point a[N]; copy(b + 1, b + n + 1, a + 1);
  random_shuffle(a + 1, a + n + 1);
  circle c = {{0, 0}, 0};
  rep(i, 1, n) {
    if(!c.inc(a[i])) {
      c = {a[i], 0};
      rep(j, 1, i - 1) if(!c.inc(a[j])) {
        c.o = (a[i] + a[j]) * 0.5;
        c.r = (a[i] - c.o).norm2();
        rep(k, 1, j - 1) if(!c.inc(a[k])) {
          c = circum_circle(a[i], a[j], a[k]);
        }
      }
    }
  }
  return sqrt(c.r);
}
int main() {
  while(scanf("%d", &n), n) {
    rep(i, 1, n) a[i].in(), a[i].perturb();
    db ans = 1e18;
    const db t = 2 * pi / 200;
    for(int i = 0; i < 200; i ++) {
      rep(j, 1, n) a[j] = a[j].rot(t);
      sort(a + 1, a + n + 1);
      int l = 1, r = n;
      while(l <= r) {
        int j = (l + r) >> 1;
        db s1 = min_circle_cover(a, j);
        db s2 = min_circle_cover(&a[j], n - j);
        if(ans <= min(s1, s2)) break ;
        ans = min(ans, max(s1, s2));
        if(s1 > s2) r = j - 1;
        else l = j + 1;
      }
      // db s1 = min_circle_cover(a, l);
      // db s2 = min_circle_cover(&a[l], n - l);
      // ans = min(ans, max(s1, s2));
      // break ;
    }
    printf("%.2lf\n", ans);
  }
  return 0;
}