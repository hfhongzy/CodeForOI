#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;
const int inv100 = 828542813;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
struct mat {
  int a[2][2];
  mat operator * (const mat &b) {
    mat ans;
    #define C(i, j) ans.a[i][j] = ((ll)a[i][0] * b.a[0][j] + (ll)a[i][1] * b.a[1][j]) % mod
    C(0, 0); C(0, 1); C(1, 0); C(1, 1);
    #undef C
    return ans;
  }
};
int n, x[N], v[N], p[N], q[N];
int calc(int u, int s, int t) {
  if(!s && !t) return v[u] >= v[u + 1] ? -1 : v[u + 1] - v[u];
  if(!s && t) return -1;
  if(s && !t) return v[u] + v[u + 1];
  return v[u] <= v[u + 1] ? -1 : v[u] - v[u + 1];
}
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
mat w[N * 4], s[N];
void build(int u, int l, int r) {
  if(l == r) {
    rep(i, 0, 1) rep(j, 0, 1)
      w[u].a[i][j] = j ? p[l] : q[l];
    s[l] = w[u];
    return ;
  }
  int mid = (l + r) >> 1;
  build(ls); build(rs);
  w[u] = w[u << 1] * w[u << 1 | 1];
}
namespace Q { int u; mat w; }
void modify(int u, int l, int r) {
  if(l == r) { w[u] = Q::w; return ; }
  int mid = (l + r) >> 1;
  Q::u <= mid ? modify(ls) : modify(rs);
  w[u] = w[u << 1] * w[u << 1 | 1];
}

#undef ls
#undef rs
struct node {
  int u, x, v, s, t;
  bool operator < (const node &b) const {
    return (ll)x * b.v < (ll)b.x * v;
  }
};
vector<node> crash;
int main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    scanf("%d%d%d", x + i, v + i, p + i);
    p[i] = (ll)p[i] * inv100 % mod;
    q[i] = mod + 1 - p[i];
    // LOG("p%d = %d\n", i, p[i]);
  }
  build(1, 1, n);
  rep(i, 1, n - 1) {
    rep(s, 0, 1) rep(t, 0, 1) {
      int v0 = calc(i, s, t);
      if(!~v0) continue ;
      // cerr << "v0 = " << v0 << endl;
      crash.pb({i, x[i + 1] - x[i], v0, s, t});
    }
  }
  sort(crash.begin(), crash.end());
  int res = 0;
  for(node &cur : crash) {
    int u = cur.u + 1;
    Q::u = u;
    mat tmp = s[u];
    rep(s, 0, 1) rep(t, 0, 1)
      Q::w.a[s][t] = s == cur.s && t == cur.t ? (t ? p[u] : q[u]) : 0;
    modify(1, 1, n);
    res = (res + (w[1].a[0][0] + w[1].a[0][1]) * (ll)cur.x % mod * qpow(cur.v, mod - 2)) % mod;
    Q::w = tmp; Q::w.a[cur.s][cur.t] = 0;
    s[u] = Q::w; modify(1, 1, n);
  }
  printf("%d\n", res);
  return 0;
}