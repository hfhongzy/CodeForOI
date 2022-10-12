#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 2e5 + 10;
const int M = 5e5 + 10;
const int mod = 998244353;

int test, n, m, d[N], eu[M], ev[M], tag[N], c[N];
vector<int> F[N], G[N];
bool cmp(int x, int y) {
  return d[x] > d[y] || (d[x] == d[y] && x > y);
}
int C3() {
  fill(tag + 1, tag + n + 1, 0);
  int ans = 0;
  rep(u, 1, n) {
    for(int v : G[u]) tag[v] = u;
    for(int v : G[u]) for(int w : G[v]) ans += tag[w] == u;
  }
  return ans;
}
ll C4() {
  fill(tag + 1, tag + n + 1, 0);
  ll ans = 0;
  rep(u, 1, n) {
    for(int v : G[u]) for(int w : F[v]) if(cmp(u, w)) {
      if(tag[w] != u) {
        tag[w] = u; c[w] = 0;
      }
      ans += c[w] ++;
    }
  }
  return ans;
}
int main() {
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) { d[i] = 0; G[i].clear(); F[i].clear(); }
    rep(i, 1, m) {
      int u, v;
      scanf("%d%d", &u, &v);
      eu[i] = u; ev[i] = v;
      d[u] ++; d[v] ++;
      F[u].pb(v); F[v].pb(u);
    }
    rep(i, 1, m) {
      if(cmp(eu[i], ev[i])) {
        G[eu[i]].pb(ev[i]);
      } else {
        G[ev[i]].pb(eu[i]);
      }
    }
    ll ans = m * (n + m - 3ll) + 3 * C3() + C4();
    // cerr << "c4 = " << C4() << endl;
    rep(i, 1, n) ans += d[i] * (d[i] - 1ll) / 2;
    printf("%lld\n", ans % mod);
  }
  return 0;
}