#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 110;
const int M = 2e5 + 10;
const int mod = 1e6 + 3;
int n, a[N][N], deg[N], in[N], fac[M];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
      if(b & 1) ans = (ll)ans * a % mod;
   return ans;
}
int gauss() {
   int ans = 1, sgn = 1;
   rep(i, 2, n) {
      int k = 0;
      rep(j, i, n) if(a[j][i]) { k = j; break ; }
      if(k != i) {
         sgn = -sgn;
         rep(j, i, n) swap(a[i][j], a[k][j]);
      }
      int inv = qpow(a[i][i], mod - 2);
      ans = (ll)ans * a[i][i] % mod;
      rep(j, i + 1, n) {
         int t = mod - 1ll * a[j][i] * inv % mod;
         rep(k, i, n) {
            a[j][k] = (a[j][k] + (ll)t * a[i][k]) % mod;
         }
      }
   }
   return sgn > 0 ? ans : (mod - ans) % mod;
}
int main() {
   fac[0] = 1;
   rep(i, 1, M - 1) fac[i] = (ll)fac[i - 1] * i % mod;
   int test;
   scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      rep(i, 1, n) in[i] = 0;
      rep(i, 1, n) rep(j, 1, n) a[i][j] = 0;
      rep(i, 1, n) {
         scanf("%d", deg + i);
         rep(j, 1, deg[i]) {
            int x; scanf("%d", &x); in[x] ++;
            if((-- a[i][x]) < 0) a[i][x] += mod;
            a[x][x] ++;
         }
      }
      if(n == 1) { printf("%d\n", fac[deg[1]]); continue ; }
      bool mark = 1;
      rep(i, 1, n) if(in[i] != deg[i] || !in[i]) { mark = 0; break ; }
      if(!mark) { puts("0"); continue ; }
      int ans = gauss();
      rep(i, 1, n) ans = (ll)ans * fac[deg[i] - 1] % mod;
      ans = (ll)ans * deg[1] % mod;
      printf("%d\n", ans);
   }
   
   return 0;
}