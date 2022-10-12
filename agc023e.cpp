#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int n, a[N], c[N];
struct BIT {
  vector<int> c, op;
  int n, s;
  BIT(int sz) { s = 0; c.resize(1 + (n = sz)); }
  void clean() {
    for(int x : op)
      for(; x <= n; x += x & (-x))
        c[x] = 0;
    op.clear(); s = 0;
  }
  void upd(int x, int y) {
    s = add(s, y); op.pb(x);
    for(; x <= n; x += x & (-x))
      c[x] = add(c[x], y);
  }
  int qry(int x) {
    ll ans = 0;
    for(; x >= 1; x &= x - 1) ans += c[x];
    return ans % mod;
  }
};
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i), c[a[i]] ++;
  per(i, n, 1) c[i] += c[i + 1];
  int S = 1;
  rep(i, 1, n) S = (ll)S * (c[i] - n + i) % mod;
  if(!S) return puts("0"), 0;
  static int p[N];
  rep(i, 1, n) p[i] = i;
  sort(p + 1, p + n + 1, [&](int x, int y) {
    return a[x] < a[y];
  });
  BIT bit_v(n), bit_c(n);
  int pd = 1, z = 0, ans = 0;
  rep(i, 1, n) {
    int u = p[i];
    while(z < a[u]) {
      z ++;
      pd = (ll)pd * (c[z] - n + z - 1ll) % mod * qpow(c[z] - n + z, mod - 2) % mod;
      if(!pd) {
        bit_v.clean();
        pd = 1;
      }
    }
    int q = bit_v.qry(u);
    ans = (ans + (ll)(2 * q - bit_v.s) * pd % mod * S % mod * inv2) % mod;
    ans = (ans + (ll)(bit_c.s - bit_c.qry(u)) * S) % mod;
    bit_c.upd(u, 1);
    bit_v.upd(u, pd > 1 ? qpow(pd, mod - 2) : 1);
  }
  if(ans < 0) ans += mod;
  printf("%d\n", ans);
  return 0;
}