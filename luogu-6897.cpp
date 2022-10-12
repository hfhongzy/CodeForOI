#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 5e4 + 10;
const db eps = 1e-7;
int n, m;
bool lt(db x, db y) { return x < y - eps; }
bool leq(db x, db y) { return x <= y + eps || x <= y * 1.00000000001; }
struct point {
  db x, y;
  void in_int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
  db norm() { return sqrt(x * x + y * y); }
  db norm2() { return x * x + y * y; }
  point e() { db z = norm(); return (point){x / z, y / z}; }
  point operator + (point b) { return (point){x + b.x, y + b.y}; }
  point operator - (point b) { return (point){x - b.x, y - b.y}; }
  point operator - () const { return (point){-x, -y}; }
  void operator += (point b) { *this = *this + b; }
  void operator -= (point b) { *this = *this - b; }
  db operator * (point b) { return x * b.x + y * b.y; }
  point operator * (db b) { return (point){x * b, y * b}; }
  point operator / (db b) { return (point){x / b, y / b}; }
  db det(point b) { return x * b.y - y * b.x; }
} a[N], b[N];
struct vec { point p; db t; } va[N], v[N], vb[N], vc[N];
db PtoS(point P, point A, point B) {
  if(lt((P - A) * (B - A), 0) || lt((P - B) * (A - B), 0))
    return min((A - P).norm(), (B - P).norm());
  return fabs((B - A).det(P - A) / (B - A).norm());
}
// db PtoS(point P, point A, point B) {
  // printf("(%.1f, %.1f) to (%.1f, %.1f) and (%.1f, %.1f) = %.1f\n", P.x, P.y, A.x, A.y, B.x, B.y, PtoSS(P, A, B));
  // return PtoSS(P, A, B);
// }
bool check(db mid) {
  int z = 0; db s = 0;
  rep(i, 1, n - 1) v[i] = va[i];
  point st = b[1];
  rep(i, 1, m - 1) {
    if(lt(s + vb[i].t, mid)) {
      s += vb[i].t;
      st += vb[i].p * vb[i].t;
    } else if(lt(s, mid)) {
      // puts(">"); cerr << "s = " << s << endl;
      st += vb[i].p * (mid - s);
      vc[++ z] = vec{vb[i].p, vb[i].t + s - mid};
      s = mid;
    } else {
      vc[++ z] = vb[i];
    }
  }
  // rep(i, 1, z) printf("%d: v = (%.1f, %.1f), t = %.1f\n", i, vc[i].p.x, vc[i].p.y, vc[i].t);
  int pc = 1, pa = 1;
  db tc = 0, ta = 0;
  while(pc <= z && pa <= n - 1) {
    if(vc[pc].t < v[pa].t) {
      // puts("B");
      if(leq(PtoS(a[1], st, st + (vc[pc].p - v[pa].p) * vc[pc].t), mid))
        return 1;
      st += (vc[pc].p - v[pa].p) * vc[pc].t;
      v[pa].t -= vc[pc++].t;
    } else {
      // puts("A");
      if(leq(PtoS(a[1], st, st + (vc[pc].p - v[pa].p) * v[pa].t), mid))
        return 1;
      st += (vc[pc].p - v[pa].p) * v[pa].t;
      vc[pc].t -= v[pa++].t;
    }
  }
  return 0;
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) a[i].in_int();
  rep(i, 1, n - 1) {
    va[i].t = (a[i + 1] - a[i]).norm();
    va[i].p = (a[i + 1] - a[i]).e();
  }
  scanf("%d", &m);
  rep(i, 1, m) b[i].in_int();
  db l = 0, r = 0;
  rep(i, 1, m - 1) {
    vb[i].t = (b[i + 1] - b[i]).norm();
    vb[i].p = (b[i + 1] - b[i]).e();
    r += vb[i].t;
  }
  // cerr << "r = " << r << endl;
  // cerr << check(2) << endl;
  // return 0;
  bool tag = 0;
  while(r - l > 1e-6) {
    db mid = (l + r) / 2;
    if(check(mid)) tag = 1, r = mid;
    else l = mid;
  }
  if(!tag) puts("impossible");
  else printf("%.6Lf\n", (l + r) / 2);
  return 0;
}