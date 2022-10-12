#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int n, m, k, inv6, pw[N], d[N], uu[N], vv[N], vis[N];
vector<int> G[N];
int solve1() {
   return 1ll * m * pw[n - 2] % mod;
}
int C2(int n) { return n * (n - 1ll) / 2 % mod; }
int C3(int n) {
   return n * (n - 1ll) % mod * (n - 2) % mod * inv6 % mod;
}
int solve2() {
   int all = C2(m), x = 0, ans = 0;
   rep(i, 1, n) {
      x = (x + C2(d[i])) % mod;
   } 
   if(n >= 3) ans = (ll) x * pw[n - 3] % mod;
   if(n >= 4) ans = (ans + (ll) (all - x + mod) * pw[n - 4]) % mod;
   return ans;
}
int solve3() {
   int all = C3(m), x = 0, y = 0, z = 0, t2 = 0, t3 = 0;
   rep(i, 1, m) {
      x = (x + (d[uu[i]] - 1ll) * (d[vv[i]] - 1ll)) % mod;
   }
   rep(i, 1, n) {
      for(int v : G[i]) {
         vis[v] = i;
      }
      for(int v : G[i]) for(int w : G[v]) {
         y += (vis[w] == i);
      }
   }
   x = (x - 3ll * y + 3ll * mod) % mod;
   rep(i, 1, n) z = (z + C3(d[i])) % mod;
   rep(i, 1, n) {
      t2 = (t2 + C2(d[i]) * (m - 2ll)) % mod;
   }
   t2 = (t2 - 2ll * x - 3ll * y - 3ll * z + 8ll * mod) % mod;
   t3 = (all + 4ll * mod - x - y - z - t2) % mod;
   int ans = 0;
   if(n >= 4) ans = (ans + (ll) pw[n - 4] * x) % mod;
   if(n >= 3) ans = (ans + (ll) pw[n - 3] * y) % mod;
   if(n >= 4) ans = (ans + (ll) pw[n - 4] * z) % mod;
   if(n >= 5) ans = (ans + (ll) pw[n - 5] * t2) % mod;
   if(n >= 6) ans = (ans + (ll) pw[n - 6] * t3) % mod;
   return ans;
}
int main() {
   scanf("%d%d%d", &n, &m, &k);
   pw[0] = 1; inv6 = qpow(6, mod - 2);
   rep(i, 1, n) pw[i] = (pw[i - 1] + pw[i - 1]) % mod;
   rep(i, 1, m) {
      scanf("%d%d", uu + i, vv + i);
      d[uu[i]] ++; d[vv[i]] ++;
      if(uu[i] > vv[i]) swap(uu[i], vv[i]);
   }
   rep(i, 1, m) {
      if(d[vv[i]] < d[uu[i]]) {
         G[vv[i]].pb(uu[i]);
      } else {
         G[uu[i]].pb(vv[i]);
      }
   }
   int ans = 0;
   if(k == 1) ans = solve1();
   if(k == 2) ans = (solve1() + 2ll * solve2()) % mod;
   if(k == 3) ans = (solve1() + 6ll * solve2() + 6ll * solve3()) % mod;
   printf("%d\n", ans);
   return 0;
}

/*
4 5 2
1 2
2 3
3 4
4 1
2 4
*/