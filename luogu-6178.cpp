#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 310;
int n, m, op, a[N][N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int gauss() {
   int ans = 1;
   rep(i, 2, n) {
      int k = 0;
      rep(j, i, n) if(a[j][i]) { k = j; break ; }
      if(k != i) rep(j, i, n) swap(a[i][j], a[k][j]);
      int inv = qpow(a[i][i], mod - 2);
      ans = 1ll * ans * a[i][i] % mod;
      rep(j, i + 1, n) {
         int t = mod - 1ll * a[j][i] * inv % mod;
         rep(k, i, n) {
            a[j][k] = (a[j][k] + 1ll * t * a[i][k]) % mod;
         }
      }
   }
   return ans;
}
int main() {
   scanf("%d%d%d", &n, &m, &op);
   int u, v, w;
   rep(i, 1, m) {
      scanf("%d%d%d", &u, &v, &w);
      if(op == 0) {
         if((a[u][u] += w) >= mod) a[u][u] -= mod;
         if((a[v][v] += w) >= mod) a[v][v] -= mod;
         if((a[u][v] -= w) < 0) a[u][v] += mod;
         if((a[v][u] -= w) < 0) a[v][u] += mod;
      } else {
         if((a[v][v] += w) >= mod) a[v][v] -= mod;
         if((a[u][v] -= w) < 0) a[u][v] += mod;
      }
   }
   printf("%d\n", gauss());
   return 0;
}