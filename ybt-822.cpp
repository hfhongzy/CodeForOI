#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1e3 + 5;
const db eps = 1e-4;
int sign(db x) { return x < -eps ? -1 : x > eps; }
struct P {
  db x, y;
  P operator + (P b) { return {x + b.x, y + b.y}; }
  P operator - (P b) { return {x - b.x, y - b.y}; }
  bool operator == (P b) { return !sign(x - b.x) && !sign(y - b.y); }
  P operator * (db b) { return {x * b, y * b}; }
  P operator / (db b) { return {x / b, y / b}; }
  db operator * (P b) const { return x * b.x + y * b.y; }
  db det(P b) { return x * b.y - y * b.x; }
  db len() { return sqrt(x * x + y * y); }
  void out() {
    printf("%.1f %.1f\n", x, y);
  }
};
struct node { db x, y, z; } a[N], b[N];
int n;
bool G[N][N];
bool on2D(P a, P b, P c) {
  return sign((b - a).det(c - a)) == 0;
}
bool get(P a, P b, P c, P d, P &res) {
  P d1 = b - a, d2 = d - c;
  if(!sign(d1.det(d2))) {
    return 0;
  }
  res = a + d1 * (d2.det(a - c) / d1.det(d2));
  // a.out(); b.out(); c.out(); d.out();
  // res.out();
  if(sign(d2.det(res - c))) return 0;
  return 1;
}
bool pd(node u1, node v1, node u2, node v2) {
  if(on2D({u1.x, u1.y}, {v1.x, v1.y}, {u2.x, u2.y})) {
    swap(u1.y, u1.z); swap(u2.y, u2.z); swap(v1.y, v1.z); swap(v2.y, v2.z);
  }
  P c;
  if(!get({u1.x, u1.y}, {v1.x, v1.y}, {u2.x, u2.y}, {v2.x, v2.y}, c)) return 0;
  db h1 = u1.z + (v1.z - u1.z) * (c.x - u1.x) / (v1.x - u1.x);
  db h2 = u2.z + (v2.z - u2.z) * (c.x - u2.x) / (v2.x - u2.x);
  // printf("%.1f & %.1f\n", h1, h2);
  return !sign(h1 - h2);
}
int main() {
  freopen("gentech.in", "r", stdin);
  freopen("gentech.out", "w", stdout);
  scanf("%d", &n);
  vector<int> p(n);
  rep(i, 0, n - 1) {
    scanf("%lf%lf%lf%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z, &b[i].x, &b[i].y, &b[i].z);
  }
  rep(i, 0, n - 1) rep(j, i + 1, n - 1) {
    G[i][j] = G[j][i] = pd(a[i], b[i], a[j], b[j]);
    // if(G[i][j]) printf("%d<-->%d\n", i, j);
  }
  rep(i, 0, n - 1) p[i] = i;
  mt19937 mt(time(0));
  int ans = 1;
  int lim = n <= 80 ? 8888 : 1e8 / n / n + 1;
  for(int t = 1; t <= lim; t ++) {
    random_shuffle(p.begin(), p.end(), [&](int x) { return mt() % x; });
    vector<int> g;
    rep(i, 0, n - 1) {
      int u = p[i];
      bool mk = 1;
      for(int j : g) if(!G[u][j]) { mk = 0; break; }
      if(mk) g.pb(u);
      if(g.size() + n - 1 - i <= ans) break ;
    }
    ans = max(ans, (int)g.size());
  }
  printf("%d\n", ans);
  return 0;
}
