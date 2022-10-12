#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef double db;
const int N = 300 + 10;

const db eps = 1e-12;
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
  point operator - (point b) const { return (point) {x - b.x, y - b.y}; }
  point operator - () const { return (point) {-x, -y}; }
  void operator += (point b) { *this = *this + b; }
  void operator -= (point b) { *this = *this - b; }
  db operator * (point b) { return x * b.x + y * b.y; }
  point operator * (db b) { return (point) {x * b, y * b}; }
  point operator / (db b) { return (point) {x / b, y / b}; }
  db det(point b) { return x * b.y - y * b.x; }
  bool operator < (point b) { return lt(x, b.x) || (leq(x, b.x) && lt(y, b.y)); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
} a[N];
int n, cnt[N][N], sgn[N][N];
int sign(db x) { return x < -eps ? -1 : x > eps; }
bool In(point a, point b, point c, point p) {
  bool vis[3] = {0};
  vis[sign(cross(a, b, p)) + 1] = 1;
  vis[sign(cross(b, c, p)) + 1] = 1;
  vis[sign(cross(c, a, p)) + 1] = 1;
  return !(vis[0] && vis[2]);
}
ll C5(ll n) {
  return n * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 120;
}
mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
uniform_real_distribution<db> ran(-0.00001, 0.00001);
int main() {
  scanf("%d", &n);
  if(n < 5) { puts("0"); return 0; }
  rep(i, 1, n) {
    a[i].in_int();
    a[i].x += ran(mt); a[i].y += ran(mt);
  }
  rep(i, 1, n) rep(j, 1, n) if(i != j) {
    rep(k, 1, n) if(k != i && k != j) {
      if(In({0, 0}, a[i], a[j], a[k])) {
        cnt[i][j] ++;
      }
    }
    // printf("cnt %d %d = %d\n", i, j, cnt[i][j]);
    if(gt(a[i].det(a[j]), 0)) {
      cnt[i][j] *= -1;
      sgn[i][j] = -1;
    } else {
      sgn[i][j] = 1;
    }
  }
  ll ans = C5(n) * 5, tmp = 0;
  // cerr << "ans = " << ans << endl;
  rep(i, 1, n) rep(j, i + 1, n) rep(k, j + 1, n) {
    ll c1 = cnt[i][j] - sgn[i][j] * In({0, 0}, a[i], a[j], a[k]);
    ll c2 = cnt[j][k] - sgn[j][k] * In({0, 0}, a[j], a[k], a[i]);
    ll c3 = cnt[k][i] - sgn[k][i] * In({0, 0}, a[k], a[i], a[j]);
    ll c = abs(c1 + c2 + c3);
    ll d = n - 3 - c;
    // printf("(%d, %d, %d), in = %lld, out = %lld\n", i, j, k, c, d);
    tmp += c * d;
    ans += 2 * (c * (c - 1) / 2);
  }
  ans += tmp >> 1;
  printf("%lld\n", ans);
  return 0;
} 