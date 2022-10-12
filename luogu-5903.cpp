#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef unsigned ui;
ui s;
inline ui get(ui x) {
   x ^= x << 13;
   x ^= x >> 17;
   x ^= x << 5;
   return s = x; 
}
const int N = 5e5 + 5;
int n, q, rt, f[N][20], d[N], dd[N], son[N], top[N], lg[N];
vector<int> G[N], up[N], dn[N];
void dfs(int u) {
   for(int i = 0; f[u][i]; i ++) {
      f[u][i + 1] = f[f[u][i]][i];
   }
   d[u] = dd[u] = d[f[u][0]] + 1;
   for(int v : G[u]) {
      dfs(v);
      if(dd[v] > dd[u]) {
         dd[u] = dd[v];
         son[u] = v;
      }
   }
}
void dfs2(int u, int t) {
   top[u] = t;
   if(u == t) {
      int v = u;
      rep(i, 0, dd[u] - d[u]) up[u].pb(v), v = f[v][0];
      v = u;
      rep(i, 0, dd[u] - d[u]) dn[u].pb(v), v = son[v];
   }
   if(!son[u]) return ;
   dfs2(son[u], t);
   for(int v : G[u]) if(!top[v]) dfs2(v, v);
}
int kthfa(int u, int k) {
   if(!k) return u;
   u = f[u][lg[k]]; k ^= 1 << lg[k];
   k -= d[u] - d[top[u]]; u = top[u];
   return k >= 0 ? up[u][k] : dn[u][-k];
}
int main() {
   scanf("%d%d%u", &n, &q, &s);
   rep(i, 1, n) {
      scanf("%d", f[i]);
      if(!f[i][0]) {
         rt = i;
      } else {
         G[*f[i]].pb(i);
      }
   }
   rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
   dfs(rt); dfs2(rt, rt);
   int lans = 0; ll ans = 0;
   rep(i, 1, q) {
      int u = (get(s) ^ lans) % n + 1;
      int k = (get(s) ^ lans) % d[u];
      ans ^= 1ll * i * (lans = kthfa(u, k));
   }
   printf("%lld\n", ans);
   return 0;
}