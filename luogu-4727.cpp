#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 64, p = 997;
int n, pw[N * N], g[N][N], fac[N], fav[N], inv[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % p)
      if(b & 1) ans = (ll) ans * a % p;
   return ans;
}
int b[N] = {1}, ans;
void dfs(int u, int sum) {
   if(sum == n) {
      int tot = 1; -- u;
      rep(i, 1, u) tot = tot * inv[b[i]] % p;
      int sz = 0;
      rep(i, 1, u) {
         sz ++;
         if(i == u || b[i] != b[i + 1]) {
            tot = (ll) tot * fav[sz] % p;
            sz = 0;
         }
      }
      rep(i, 1, u) {
         sz += b[i] / 2;
         rep(j, i + 1, u) {
            sz += g[b[i]][b[j]];
         }
      }
      ans = (ans + pw[sz] * tot) % p;
      return ;
   }
   rep(i, b[u - 1], n - sum) {
      b[u] = i; dfs(u + 1, sum + i);
   }
}
int main() {
   scanf("%d", &n);
   pw[0] = 1;
   rep(i, 1, n * n) pw[i] = (pw[i - 1] + pw[i - 1]) % p;
   fac[0] = 1;
   rep(i, 1, n) fac[i] = fac[i - 1] * i % p;
   fav[n] = qpow(fac[n], p - 2);
   per(i, n, 1) fav[i - 1] = fav[i] * i % p;
   rep(i, 1, n) g[i][0] = g[0][i] = i;
   rep(i, 1, n) rep(j, 1, n) g[i][j] = i >= j ? g[i - j][j] : g[i][j - i];
   inv[1] = 1;
   rep(i, 2, n) inv[i] = (p - p / i) * inv[p % i] % p;
   dfs(1, 0);
   printf("%d\n", ans);
   return 0;
}