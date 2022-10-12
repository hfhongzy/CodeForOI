#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int P = 1e6 + 3e5 + 10;
const int N = 1e5 + 10;
const int mod = 998244853;

int p[P], c;
void sieve(int n) {
   static bool tag[P];
   rep(i, 2, n) {
      if(!tag[i]) p[++ c] = i;
      rep(j, 1, c) {
         if(i * p[j] > n) break ;
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
struct tree {

vector<int> G[N];
int n, sz[N], h[N], f[N], d[N], F[N];
void init(int _n) {
   n = _n;
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
      d[u] ++; d[v] ++;
   }
}
void calc(int u, int fa = 0) {
   h[u] = 1; sz[u] = 1; F[u] = fa;
   for(int v : G[u]) if(v ^ fa) {
      calc(v, u);
      h[u] = (h[u] + (ll) h[v] * p[sz[v]]) % mod;
      sz[u] += sz[v];
   }
}
void dfs(int u, int fa = 0) {
   if(fa) f[u] = (h[u] + (f[fa] - (ll) p[sz[u]] * h[u] % mod + mod) * p[n - sz[u]]) % mod;
   else f[u] = h[u];
   for(int v : G[u]) if(v ^ fa) dfs(v, u);
}

} a, b;
int main() {
   sieve(P - 10);
   int n; scanf("%d", &n);
   a.init(n); b.init(n + 1);
   a.calc(1); a.dfs(1); b.calc(1); b.dfs(1);
   sort(a.f + 1, a.f + n + 1);
   rep(i, 1, n + 1) if(b.d[i] == 1) {
      int t = !b.F[i] ? b.h[b.G[1][0]] : (b.f[b.F[i]] + mod - 2) % mod;
      if(*lower_bound(a.f + 1, a.f + n + 1, t) == t) {
         printf("%d\n", i);
         break ;
      }
   }
   return 0;
}