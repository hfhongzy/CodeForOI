#include <functional>
#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
#define pii pair<int, int>
using namespace std;
const int N = 1e5 + 10;
int n, m, ans = -1, d[N];
vector<int> x[N];
vector<pii> y[N], G[N];
pii out[N];
bool ins[N], vis[N];
void dfs(int u) {
   vis[u] = ins[u] = 1; //printf("%d!\n", u);
   for(auto e: G[u]) {
      if(!vis[e.fs]) {
         d[e.fs] = d[u] + e.sc;
         dfs(e.fs);
         if(~ ans) return ;
      } else if(ins[u]) {
         ans = d[u] - d[e.fs] + e.sc;
         break ;
      }
   }
   ins[u] = 0;
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= m; i ++) {
      x[i].resize(n + 1);
      for(int j = 1; j <= n; j ++) {
         scanf("%d", &x[i][j]);
         if(x[i][j]) y[j].emplace_back(x[i][j], i);
      }
   }
   for(int i = 1; i <= n; i ++) {
      sort(y[i].begin(), y[i].end(), greater< pair<int, int> >());
      for(int j = 1; j < (int) y[i].size(); j ++) {
         G[y[i][j - 1].sc].emplace_back(y[i][j].sc, y[i][j - 1].fs - y[i][j].fs);
      }
   }
   for(int i = 1; i <= m && -1 == ans; i ++)
      if(!vis[i]) dfs(i);
   res :
   printf("%d\n", ans);
   return 0;
}