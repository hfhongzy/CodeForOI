#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
template<typename T>
inline void chkmax(T &x, const T &y) {
   if(x < y) {
      x = y;
   }
}
const int N = 5e4 + 20;
int n, m, dp[N][2][2], f[N], d[N], low[N], up[N];
vector<int> G[N];
bool islow[N], istop[N];
void solve(int u, int fa = 0) {
   d[u] = d[fa] + 1; f[u] = fa;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(d[v] && v != fa) {
         islow[u] = 1; break ;
      }
   }
   dp[u][1][islow[u]] = 1;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v == fa) continue ;
      if(!d[v]) {
         solve(v, u); static int tmp[2][2];
         rep(j, 0, 1) rep(k, 0, 1) tmp[j][k] = 0;
         rep(j, 0, 1) rep(k, 0, 1) rep(x, 0, 1) rep(y, 0, 1) {
            if(j && x) continue ;
            if(j && up[v] == u && y) continue ;
            chkmax(tmp[j][k || (up[v] && up[u] == up[v] && y)], dp[u][j][k] + dp[v][x][y]);
         }
         rep(j, 0, 1) rep(k, 0, 1) dp[u][j][k] = tmp[j][k];
      } else if(d[v] < d[u]) {
         for(int x = u; x != v; x = f[x]) up[x] = v;
      }
   }
}
int main() {
   scanf("%d%d", &n, &m);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   int ans = 0;
   rep(i, 1, n) if(!d[i]) {
      solve(i);
      int x = 0;
      rep(j, 0, 1) rep(k, 0, 1)
         chkmax(x, dp[i][j][k]);
      ans += x;
   }
   printf("%d\n", ans);
   return 0;
}