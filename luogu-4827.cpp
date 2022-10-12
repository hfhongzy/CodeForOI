#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)

const int mod = 10007;
const int N = 5e4 + 10;
const int K = 155;

int n, k, S[K][K], fac[K], f[N][K], g[N][K];
vector<int> G[N];
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
void dfs1(int u, int fa = 0) {
   f[u][0] = 1;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v == fa) continue ;
      dfs1(v, u);
      rep(j, 0, k) {
         upd(f[u][j], f[v][j]);
         if(j) upd(f[u][j], f[v][j - 1]);
      }
   }
}
void dfs2(int u, int fa = 0) {
   static int h[K];
   if(fa) {
      rep(i, 0, k) h[i] = (f[fa][i] + mod - f[u][i] + (i ? mod - f[u][i - 1] : 0)) % mod;
      rep(i, 0, k) {
         g[u][i] = (g[fa][i] + h[i]) % mod;
         if(i) upd(g[u][i], (g[fa][i - 1] + h[i - 1]) % mod);
      }
   }
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v == fa) continue ;
      dfs2(v, u);
   }
}

int main() {
   scanf("%d%d", &n, &k);
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs1(1); dfs2(1);
   S[0][0] = 1;
   rep(i, 1, k) rep(j, 1, i) {
      S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
   }
   fac[0] = 1;
   rep(i, 1, k) fac[i] = fac[i - 1] * i % mod;
   rep(i, 1, n) {
      int res = 0;
      rep(j, 0, k) {
         res += fac[j] * S[k][j] % mod * (f[i][j] + g[i][j]) % mod;
      }
      printf("%d\n", res % mod);
   }
   return 0;
}