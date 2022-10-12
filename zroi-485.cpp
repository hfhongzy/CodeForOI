#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
const int mod = 998244353;
const int N = 2e5 + 10;
struct Edge { int v, w; };
int n, k, a[N], ans[N], fac[N], fav[N], sz[N], f[N], rt, size;
vector<Edge> G[N];
bool vis[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
void findrt(int u, int fa = 0) {
   sz[u] = 1; f[u] = 0;
   for(auto &e : G[u]) if(e.v != fa && !vis[e.v]) {
      findrt(e.v, u); sz[u] += sz[e.v];
      f[u] = max(f[u], sz[e.v]);
   }
   f[u] = max(f[u], size - sz[u]);
   if(!rt || f[rt] > f[u]) rt = u;
}
ll dis[N], seq[N];
int m, son[N];
void dfs(int u, int fa = 0) {
   seq[++ m] = dis[u]; son[m] = u;
   for(auto &e : G[u]) if(e.v != fa && !vis[e.v]) {
      dis[e.v] = dis[u] + e.w;
      dfs(e.v, u);
   }
}
void calc(int u, int w, int f) {
   dis[u] = w; seq[m = 1] = w; son[m] = u;
   for(auto &e : G[u]) if(!vis[e.v]) {
      dis[e.v] = dis[u] + e.w; dfs(e.v, u);
   }
   sort(seq + 1, seq + m + 1);
   rep(i, 1, m) {
      int u = son[i];
      ans[u] += f * (upper_bound(seq + 1, seq + m + 1, a[u] - dis[u]) - seq - 1);
   }
}
void solve(int u) {
   vis[u] = 1; m = 0; calc(u, 0, 1);
   for(auto &e : G[u]) if(!vis[e.v]) {
      calc(e.v, e.w, -1);
   }
   for(auto &e : G[u]) if(!vis[e.v]) {
      size = sz[e.v]; rt = 0; findrt(e.v); solve(rt);
   }
}
int main() {
   scanf("%d%d", &n, &k); binom(n);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 1, n - 1) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back({v, w});
      G[v].push_back({u, w});
   }
   size = n; rt = 0; findrt(1); solve(rt);
   int ans = 0;
   rep(i, 1, n) (ans += C(::ans[i], k)) %= mod;
   printf("%d\n", ans);
   return 0;   
}