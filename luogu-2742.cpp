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
  bool operator < (point b) const { return lt(x, b.x) || (leq(x, b.x) && lt(y, b.y)); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
};

void ConvexHull(vector<point> &ps, vector<point> &qs) {
  int n = ps.size();
  if(n <= 1) { qs = ps; return ; }
  sort(ps.begin(), ps.end());
  qs.resize(2 * n); int r = 0;
  rep(i, 0, n - 1) {
    while(r >= 2 && leq(cross(qs[r - 2], qs[r - 1], ps[i]), 0)) r --;
    qs[r ++] = ps[i];
  }
  int t = r;
  per(i, n - 2, 0) {
    while(r >= t + 1 && leq(cross(qs[r - 2], qs[r - 1], ps[i]), 0)) r --;
    qs[r ++] = ps[i];
  }
  qs.resize(r);
  //return in counterclockwise
}

int main() {
  int n; scanf("%d", &n);
  vector<point> p, ans;
  for(int i = 1; i <= n; i ++) {
    db x, y;
    scanf("%lf%lf", &x, &y);
    p.pb({x, y});
  }
  ConvexHull(p, ans);
  db res = (ans[0] - ans[int(ans.size()) - 1]).norm();
  for(int i = 1; i < ans.size(); i ++) {
    res += (ans[i] - ans[i - 1]).norm();
  }
  printf("%.2f\n", res);
  return 0;
}