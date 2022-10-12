#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2005;
const ll base = 1e17;
const int L = 32;
const int mod = 998244353;
struct _int {
  ll a[L];
  int n;
  void operator = (ll x) {
    n = 1; a[0] = x;
  }
  bool zero() { return n == 1 && a[0] == 0; }
  bool operator < (_int b) const {
    if(n != b.n) return n < b.n;
    per(i, n - 1, 0) if(a[i] != b.a[i]) return a[i] < b.a[i];
    return 0;
  }
  _int operator + (_int b) {
    _int ans; ans.n = max(n, b.n);
    rep(i, 0, ans.n) ans.a[i] = 0;
    rep(i, 0, ans.n - 1) {
      ans.a[i] += (i < n ? a[i] : 0) + (i < b.n ? b.a[i] : 0);
      ans.a[i + 1] += ans.a[i] / base;
      ans.a[i] %= base;
    }
    if(ans.a[ans.n]) ans.n ++;
    return ans;
  }
  int get() {
    const int bs = base % mod;
    int res = 0, pw = 1;
    rep(i, 0, n - 1) {
      res = (res + (a[i] % mod) * pw) % mod;
      pw = (ll)pw * bs % mod;
    }
    return res;
  }
};
int n, m, q, deg[N], seq[N], s, pos[N];
struct node {
  int u, v;
};
vector<int> G[N];
vector<node> V[N];
bool ban[N];
void build() {
  rep(i, 1, n) deg[i] = 0, V[i].clear();
  rep(i, 1, n) for(int v : G[i]) deg[v] ++;
  queue<int> tp;
  rep(i, 1, n) if(!deg[i]) tp.push(i);
  s = 0;
  while(tp.size()) {
    int u = tp.front(); tp.pop(); seq[++ s] = u; pos[u] = s;
    for(int v : G[u]) if(!--deg[v]) {
      tp.push(v);
    }
  }
}
struct tup {
  int x, y, z;
};
vector<tup> vec;
_int dp[N];
void solve() {
  rep(i, 1, n) dp[i] = 0;
  rep(i, 1, n) {
    int u = seq[i];
    if(ban[u]) { dp[u] = 0; continue ; }
    if(u <= m) dp[u] = 1;
    if(dp[u].zero()) continue ;
    for(auto &x : V[u]) if(!ban[x.u] && !dp[x.u].zero()) {
      if(dp[x.v].zero()) dp[x.v] = dp[x.u] + dp[u];
      else dp[x.v] = min(dp[x.v], dp[x.u] + dp[u]);
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  rep(i, 1, n) seq[i] = i;
  int op, x, y, z;
  while(q --) {
    scanf("%d%d", &op, &x);
    if(op == 1) {
      scanf("%d", &y);
      solve();
      int ans = 0;
      if(dp[x].zero()) {
        ans = -1;
      } else {
        ban[y] = 1; solve(); ban[y] = 0;
        ans = dp[x].zero() ? 1 : 0;
      }
      printf("%d\n", ans);
    }
    if(op == 2) {
      solve();
      printf("%d\n", dp[x].zero() ? -1 : dp[x].get());
    }
    if(op == 3) {
      scanf("%d%d", &y, &z);
      G[x].pb(z); G[y].pb(z);
      build();
      vec.pb({x, y, z});
      for(auto u : vec) {
        if(pos[u.x] < pos[u.y]) swap(u.x, u.y);
        V[u.x].pb({u.y, u.z});
      }
    }
  }     
  return 0;
}