#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
typedef pair<int, int> pii;

const db eps = 1e-10;

#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
//notice twice calc
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ( ( (v) - (u) ).det( (w) - (u) ) )
struct point {
  db x, y, z;
  void in() { scanf("%lf%lf%lf", &x, &y, &z); }
  void in_int() { int a, b, c; scanf("%d%d%d", &a, &b, &c); x = a; y = b; z = c; }
  db norm() { return sqrt(x * x + y * y + z * z); }
  db norm2() { return x * x + y * y + z * z; }
  point operator + (point b) { return (point) {x + b.x, y + b.y, z + b.z}; }
  point operator - (point b) { return (point) {x - b.x, y - b.y, z - b.z}; }
  point operator - () const { return (point) {-x, -y, -z}; }
  void operator += (point b) { *this = *this + b; }
  void operator -= (point b) { *this = *this - b; }
  db operator * (point b) { return x * b.x + y * b.y + z * b.z; }
  point operator * (db b) { return (point) {x * b, y * b, z * b}; }
  point operator / (db b) { return (point) {x / b, y / b, z / b}; }
  point det(point b) { return point{y * b.z - b.y * z, z * b.x - b.z * x, x * b.y - y * b.x}; }
  bool operator < (point b) { return lt(x, b.x) || (leq(x, b.x) && (lt(y, b.y) || leq(y, b.y) && lt(z, b.z))); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y) && eq(z, b.z); }
};

namespace ConvexHull3D {

void disturb(vector<point> &p) {
  mt19937 mt(chrono::system_clock::now().time_since_epoch().count());
  uniform_real_distribution<db> ran(-1e-7, 1e-7);
  rep(i, 0, int(p.size()) - 1) {
    p[i].x += ran(mt); p[i].y += ran(mt); p[i].z += ran(mt);
  }
}

//return (+) when right-hand rule
db volume(point a, point b, point c, point d) {
  return (b - a).det(c - a) * (d - a);
}

struct triangle {
  point a, b, c;
};
db det2D(point a, point b) {
  return a.x * b.y - a.y * b.x;
}
int sz;
set<pii> e;
vector<point> p;
vector<triangle> res;
void wrap(int u, int v) {
  if(e.find({u, v}) != e.end()) return ;
  int w = -1;
  rep(i, 0, sz - 1)
    if(i != u && i != v && (-1 == w || geq(volume(p[u], p[v], p[w], p[i]), 0)))
      w = i;
  if(w == -1) return ;
  // printf("%d %d %d!\n", u, v, w);
  res.pb({p[u], p[v], p[w]});
  e.insert({u, v}); e.insert({v, w}); e.insert({w, u});
  wrap(w, v); wrap(u, w);
}
void solve(vector<point> vp) {
  p = vp; e.clear(); res.clear(); sz = p.size();
  disturb(p);
  int u = 0, v = -1;
  rep(i, 1, sz - 1) if(p[i] < p[u]) u = i;
  rep(i, 0, sz - 1) if(u != i && (-1 == v || leq(det2D(p[v] - p[u], p[i] - p[u]), 0))) v = i;
  wrap(u, v);
}
db area() {
  db ans = 0;
  for(auto it : res)
    ans += (it.b - it.a).det(it.c - it.a).norm();
  return ans / 2;
}

}
int main() {
  int n;
  scanf("%d", &n);
  vector<point> p;
  rep(i, 1, n) {
    point o; o.in();
    p.pb(o);
  }
  ConvexHull3D::solve(p);
  printf("%.3f\n", ConvexHull3D::area());
  return 0;
}