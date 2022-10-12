#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
template<typename T> inline void chkmin(T &a, const T &b) { if(a > b) a = b; }
template<typename T> inline void chkmax(T &a, const T &b) { if(a < b) a = b; }
using namespace std;
const int N = 1e5 + 10, M = 401;
int n, m, q, s, c[N], sz[N], inc[N], deg[N], ans, size;
int b, seq[M], id[N], e[M][N], tmp[M];
bool on[N];
vector<int> G[N];
int main() {
   //freopen("ex_light1.in", "r", stdin);
   //freopen("qwq.out", "w", stdout);
   scanf("%d%d%d", &n, &m, &q);
   for(s = 1; s * s <= n; s ++) ;
   rep(i, 1, n) scanf("%d", c + i), sz[c[i]] ++;
   rep(i, 2, n) if(c[i - 1] == c[i]) inc[c[i]] ++;
   rep(i, 1, n) if(c[i - 1] != c[i]) {
      deg[c[i - 1]] ++, deg[c[i]] ++;
      G[c[i - 1]].pb(c[i]);
      G[c[i]].pb(c[i - 1]);
   }
   rep(i, 1, m) if(deg[i] > s) {
      seq[++ b] = i; id[i] = b;
      rep(j, 1, n) if(c[j] == i) {
         if(j > 1 && c[j - 1] != i) e[b][c[j - 1]] ++;
         if(j < n && c[j + 1] != i) e[b][c[j + 1]] ++;
      }
   }
   int x;
   rep(i, 1, q) {
      scanf("%d", &x);
      int res = 0;
      if(deg[x] <= s) {
         for(int j = 0; j < (int) G[x].size(); j ++) {
            int v = G[x][j];
            if(on[v]) {
               res ++;
            }
         }
         
      } else {
         res = tmp[id[x]];
      }
      if(on[x]) {
         ans -= res + inc[x]; on[x] = 0; size -= sz[x];
         rep(j, 1, b) tmp[j] -= e[j][x];
      } else {
         ans += res + inc[x]; on[x] = 1; size += sz[x];
         rep(j, 1, b) tmp[j] += e[j][x];
      }
      printf("%d\n", size - ans);
   }
   return 0;
}