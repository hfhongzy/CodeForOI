#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)

const int mod = 1e9 + 7;
const int N = 1e5 + 10;
const int K = 205;

int n, k, S[K][K], fac[K], f[N][K], ans[N], sz[N];
vector<int> G[N];
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
void dfs(int u, int fa = 0) {
   f[u][0] = 2; //u可以选或不选
   sz[u] = 1;
   rep(e, 0, (int) G[u].size() - 1) {
      int v = G[u][e];
      if(v == fa) continue ;
      dfs(v, u);
      static int t[K]; // t[i]表示在v中有选点的情况下，u为根连通块i条边染色的方案数
      rep(i, 0, k) t[i] = 0;
      per(x, min(sz[u] - 1, k), 0) per(y, min(sz[v] - 1, k - x), 0) {
         int val = 1ll * f[u][x] * f[v][y] % mod;
         upd(t[x + y], val); //u-v 边不染色
         upd(t[x + y + 1], val); // u-v 边染色
      }
      rep(i, 0, k) upd(f[u][i], t[i]); // 不在v中选点方案是f[u][i],在v中选点方案是t[i]
      rep(i, 0, k) {
         upd(ans[i], mod - f[v][i]);
         upd(ans[i + 1], mod - f[v][i]); // 只有v子树有选点, u不选的方案应从答案中减去
      }
      sz[u] += sz[v];
   }
   upd(f[u][0], mod - 1); //没选点不行
   rep(i, 1, k) upd(ans[i], f[u][i]); //在生成树的根处累计答案
}
int main() {
   scanf("%d%d", &n, &k);
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   S[0][0] = 1;
   rep(i, 1, k) rep(j, 1, i) {
      S[i][j] = (S[i - 1][j - 1] + 1ll * j * S[i - 1][j]) % mod;
   }
   fac[0] = 1;
   rep(i, 1, k) fac[i] = 1ll * fac[i - 1] * i % mod;
   dfs(1);
   int res = 0;
   rep(i, 1, k) {
      upd(res, 1ll * fac[i] * S[k][i] % mod * ans[i] % mod);
   }
   printf("%d\n", res);
   return 0;
}