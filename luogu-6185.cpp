#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
#define pb push_back
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, a[N], b[N], col[N], f[N];
ll sa[N], sb[N], wa[3], wb[3];
vector<pii> e1;
vector<int> G[N];
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
void unite(int u, int v) { f[find(u)] = find(v); }
bool dfs(int u) {
   wa[col[u]] += sa[u]; wb[col[u]] += sb[u];
   bool tag = 1;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(!col[v]) {
         col[v] = 3 - col[u];
         if(!dfs(v)) tag = 0;
      } else if(col[v] == col[u]) {
         tag = 0;
      }
   }
   return tag;
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, n) f[i] = i, G[i].clear(), sa[i] = sb[i] = col[i] = 0;
      e1.clear();
      rep(i, 1, n) scanf("%d", a + i);
      rep(i, 1, n) scanf("%d", b + i);
      rep(i, 1, m) {
         int op, x, y;
         scanf("%d%d%d", &op, &x, &y);
         if(op == 1) e1.pb(pii(x, y));
         else unite(x, y);
      }
      rep(i, 1, n) sa[find(i)] += a[i], sb[find(i)] += b[i];
      rep(i, 0, (int) e1.size() - 1) {
         int x = find(e1[i].fs), y = find(e1[i].sc);
         G[x].pb(y);
         if(y != x) G[y].pb(x);
      }
      bool tag = 1;
      rep(i, 1, n) if(f[i] == i) {
         if(col[i]) continue ;
         wa[1] = wa[2] = wb[1] = wb[2] = 0;
         col[i] = 1;
         if(dfs(i)) {
            if(wb[1] - wa[1] != wb[2] - wa[2]) {
               tag = 0; break ;
            }
         } else {
            if((wa[1] + wa[2] - wb[1] - wb[2]) % 2 != 0) {
               tag = 0; break ;
            }
         }
      }
      puts(tag ? "YES" : "NO");
   }
   return 0;
}