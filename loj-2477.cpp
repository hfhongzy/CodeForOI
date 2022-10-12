#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 210;
int C, n, m, b[N], a[N][N], s[N], ans1[N], ans2[N];
vector<int> A[N][N];
set<int> lnk[N];
bool vis[N];
bool dfs(int u, bool mdf) {
   int l = 1, r = m;
   if(ans1[u]) l = r = ans1[u];
   rep(i, l, r) {
      rep(j, 0, (int) A[u][i].size() - 1) {
         int v = A[u][i][j];
         if(vis[v]) continue ;
         vis[v] = 1;
         if(lnk[v].size() < b[v]) {
            if(mdf) {
               lnk[v].insert(u);
               ans1[u] = i;
            }
            return 1;
         }
         for(set<int>::iterator it = lnk[v].begin(); it != lnk[v].end(); it ++) {
            if(dfs(*it, mdf)) {
               if(mdf) {
                  lnk[v].erase(it);
                  lnk[v].insert(u);
                  ans1[u] = i;
               }
               return 1;
            }
         }
      }
   }
   return 0;
}
int main() {
   // freopen("input", "r", stdin);
   // freopen("output", "w", stdout);
   int test; scanf("%d%d", &test, &C);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, m) scanf("%d", b + i);
      rep(i, 1, n) rep(j, 1, m) scanf("%d", &a[i][j]);
      rep(i, 1, n) scanf("%d", s + i);
      rep(i, 1, n) {
         rep(j, 1, m) A[i][j].clear();
         rep(j, 1, m) if(a[i][j]) A[i][a[i][j]].push_back(j);
      }
      rep(i, 1, n) ans1[i] = ans2[i] = 0;
      rep(i, 1, m) lnk[i].clear();
      rep(i, 1, n) {
         rep(j, i, n) {
            fill(vis + 1, vis + m + 1, 0);
            int t = m; m = s[j];
            if(dfs(j, 0)) ans2[j] = i;
            m = t;
         }
         fill(vis + 1, vis + m + 1, 0);
         if(!dfs(i, 1)) ans1[i] = m + 1;
      }
      rep(i, 1, n) printf("%d%c", ans1[i], " \n"[i == n]);
      rep(i, 1, n) printf("%d%c", i - ans2[i], " \n"[i == n]);
   }
   return 0;
}