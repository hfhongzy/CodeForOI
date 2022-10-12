#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j, _ = k; i <= _; ++ i)
#define per(i, j, k) for(int i = j, _ = k; i >= _; -- i)
using namespace std;
const int N = 2510, mod = 998244353;
inline void upd(int &x, const int &y) { (x += y) >= mod ? x -= mod : 0; }
int sum, sum2, c0, c1, d0, d1, k, n, c, bel[N], sz[N], ban[N], csz2[N], csz[N];
int g1[N], g2[N], dp[N][N], t1[N][N], t2[N][N], l1[N][N], l2[N][N];
vector<int> ci[N], ci2[N];
int G1(int l, int r) { return l > r ? 0 : (l == 0 ? g1[r] : (g1[r] - g1[l - 1] + mod) % mod); }
int G2(int l, int r) { return l > r ? 0 : (l == 0 ? g2[r] : (g2[r] - g2[l - 1] + mod) % mod); }
void Main() {
   scanf("%d%d%d%d%d%d", &n, &c, &c0, &c1, &d0, &d1);
   sum = sum2 = 0;
   rep(i, 1, c) ci[i].clear(), ci2[i].clear(), csz2[i] = csz[i] = 0;
   rep(i, 1, n) scanf("%d%d", bel + i, sz + i), sum += sz[i], csz[bel[i]] += sz[i];
   scanf("%d", &k);
   rep(i, 1, n) ban[i] = -1;
   rep(i, 1, k) {
      int j; scanf("%d", &j);
      scanf("%d", ban + j); csz2[bel[j]] += sz[j];
      if(ban[j] == 1) ban[j] = 2;
      else if(ban[j] == 2) ban[j] = 1;
   }
   rep(i, 1, n)
      if(~ ban[i]) ci2[bel[i]].pb(i), sum2 += sz[i];
      else ci[bel[i]].pb(i);

   rep(i, 0, c0) g1[i] = 0;
   rep(i, 0, d0) g2[i] = 0;
   g1[0] = g2[0] = 1;
   rep(i, 1, c) if(ci[i].size()) {
      int s = 0;
      rep(j, 0, (int) ci[i].size() - 1) {
         int u = ci[i][j]; s += sz[u];
         per(k, d0, sz[u])
            upd(g2[k], g2[k - sz[u]]);
      }
      if(csz2[i]) continue ;
      per(k, c0, s) upd(g1[k], g1[k - s]);
   }
   rep(x, 0, c0) rep(y, 0, d0) dp[x][y] = 0;
   dp[0][0] = 1; int up = 0, up2 = 0;
   rep(i, 1, c) if(ci2[i].size()) {
      up += csz[i]; up2 += csz2[i];
      rep(x, 0, min(c0, up)) rep(y, 0, min(c1, up2)) t1[x][y] = t2[x][y] = dp[x][y];
      rep(j, 0, (int) ci2[i].size() - 1) {
         int u = ci2[i][j];
         rep(x, 0, min(c0, up)) rep(y, 0, min(d0, up2)) l1[x][y] = t1[x][y], l2[x][y] = t2[x][y];
         rep(x, 0, min(c0, up)) rep(y, 0, min(d0, up2)) {
            t1[x][y] = t2[x][y] = 0;
            if(ban[u] != 0 && min(x, y) >= sz[u]) upd(t1[x][y], l1[x - sz[u]][y - sz[u]]);
            if(ban[u] != 2 && x >= sz[u]) upd(t1[x][y], l1[x - sz[u]][y]);
            if(ban[u] != 1 && y >= sz[u]) upd(t2[x][y], l2[x][y - sz[u]]);
            if(ban[u] != 3) upd(t2[x][y], l2[x][y]);
         }
      }
      int o = csz[i] - csz2[i];
      rep(x, 0, min(c0, up)) rep(y, 0, min(d0, up2)) {
         dp[x][y] = ((x >= o ? t1[x - o][y] : 0) + t2[x][y]) % mod;
      }
   }
   rep(i, 1, c0) upd(g1[i], g1[i - 1]);
   rep(i, 1, d0) upd(g2[i], g2[i - 1]);
   int ans = 0;
   rep(x, 0, c0) rep(y, 0, d0) if(dp[x][y]) {
      upd(ans, 1ll * G1(max(0, sum - c1 - x), c0 - x) * G2(max(0, sum - d1 - y), d0 - y) % mod * dp[x][y] % mod);
   }
   printf("%d\n", ans);
}
int main() {
   int test; scanf("%d", &test);
   while(test --) Main();
   return 0;
}