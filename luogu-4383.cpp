#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 3e5 + 12;
const ll INF = 1e12;
struct Edge { int v, w; };
struct node {
   ll v; int p;
   bool operator < (node b) const { return v < b.v || (v == b.v && p > b.p); }
   node operator + (node b) { return node {v + b.v, p + b.p}; }
} dp[N][3], f[N], t[3];
int n, k;
vector<Edge> G[N];
ll v;
void dfs(int u, int fa = 0) {
   dp[u][0] = {0, 0}; dp[u][1] = {-v, 1}; dp[u][2] = {-v, 1};
   for(auto e : G[u]) if(e.v ^ fa) {
      dfs(e.v, u);
      t[0] = dp[u][0] + f[e.v];
      t[1] = max(dp[u][1] + f[e.v], dp[u][0] + dp[e.v][1] + node{e.w, 0});
      t[2] = max(dp[u][2] + f[e.v], dp[u][1] + dp[e.v][1] + node{e.w + v, -1});
      copy(t, t + 3, dp[u]);
   }
   f[u] = max(max(dp[u][0], dp[u][1]), dp[u][2]);
}
int main() {
   scanf("%d%d", &n, &k); ++ k;
   int x, y, z;
   rep(i, 1, n - 1) {
      scanf("%d%d%d", &x, &y, &z);
      G[x].pb({y, z}); G[y].pb({x, z});
   }
   ll l = -INF, r = INF, ans = 0;
   while(l <= r) {
      ll mid = (l + r) >> 1; v = mid; dfs(1);
      if(f[1].p <= k) {
         r = mid - 1;
         ans = f[1].v + k * mid;
      } else {
         l = mid + 1;
      }
   }
   printf("%lld\n", ans);
   return 0;
}