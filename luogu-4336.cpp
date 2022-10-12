#include <bits/stdc++.h>
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef double db;

const int N = 18;
const int mod = 1e9 + 7;

int n, a[N][N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int gauss() {
   rep(i, 2, n) rep(j, 2, n) if(a[i][j] < 0) a[i][j] += mod;
   int ans = 1;
   rep(i, 2, n) {
      int k = i;
      rep(j, i, n) if(a[j][i]) k = j, j = n;
      if(k != i) {
         ans = mod - ans;
         rep(j, i, n) swap(a[i][j], a[k][j]);
      }
      if(!a[i][i]) return 0;
      ans = 1ll * ans * a[i][i] % mod;
      int inv = qpow(a[i][i], mod - 2);
      rep(j, i + 1, n) {
         int z = 1ll * inv * a[j][i] % mod;
         for(int k = n; k >= i; k --) {
            a[j][k] = (a[j][k] - 1ll * a[i][k] * z % mod + mod) % mod;
         }
      }
   }
   return ans;
}
vector<pii> edge[N];
int main() {
   scanf("%d", &n);
   int u, v;
   rep(i, 1, n - 1) {
      int s; scanf("%d", &s);
      rep(j, 1, s) {
         scanf("%d%d", &u, &v);
         edge[i].emplace_back(u, v);
      }
   }
   int ans = 0;
   for(int i = 0; i < (1 << (n - 1)); i ++) {
      rep(x, 1, n) rep(y, 1, n) a[x][y] = 0;
      int c = 0;
      for(int j = 0; j < n - 1; j ++) if(!(i >> j & 1)) {
         c ^= 1;
         for(auto p : edge[j + 1]) {
            a[p.sc][p.sc] --; a[p.fs][p.fs] --;
            a[p.sc][p.fs] ++; a[p.fs][p.sc] ++;
         }
      }
      if(!c) (ans += gauss()) %= mod;
      else (ans += mod - gauss()) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}