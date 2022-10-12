#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 18;
const int mod = 998244353;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int n, q, x, ans[1 << N | 4], c[1 << N | 4];
vector<int> G[N];
void fmt(int *a) {
  for(int i = 0; i < n; i ++)
    for(int j = 0; j < (1 << n); j ++)
      if(j >> i & 1) a[j] = add(a[j], a[j ^ (1 << i)]);
}
int st, a[N], b[N];
void dfs(int u, int fa = -1) {
  if(st >> u & 1) { a[u] = b[u] = 0; return ; }
  ll sa = 0, sb = 0, d = int(G[u].size());
  for(int v : G[u]) if(v ^ fa) {
    dfs(v, u); sa += a[v]; sb += b[v];
  }
  if(sa >= mod) sa %= mod;
  if(sb >= mod) sb %= mod;
  int t = qpow(d + mod - sa, mod - 2);
  a[u] = t; b[u] = (sb + d) * t % mod;
}
int main() {
  scanf("%d%d%d", &n, &q, &x); -- x;
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v); -- u, -- v;
    G[u].pb(v); G[v].pb(u);
  }
  for(st = 1; st < (1 << n); st ++) {
    c[st] = c[st & (st - 1)] ^ 1; dfs(x);
    ans[st] = c[st] ? b[x] : (!b[x] ? 0 : mod - b[x]);
  }
  fmt(ans);
  rep(i, 1, q) {
    int x, y, z = 0;
    scanf("%d", &x);
    while(x --) scanf("%d", &y), z ^= 1 << (y - 1);
    printf("%d\n", ans[z]);
  }
  return 0;
}