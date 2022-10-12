#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int n;
vector<int> G[N];
namespace subtask {

ll ans;
int sz[N], wl, wr, rt;
void dfs(int u, int wy = 0, int fa = 0) {
   sz[u] = 1;
   for(int i = 0; i < (int) G[u].size(); i ++) {
      int v = G[u][i];
      if(v == fa) continue ;
      int nw = wy ? wy : (i ? 2 : 1);
      dfs(v, nw, u); sz[u] += sz[v];
      ans += v;
      if(sz[v] == 1) {
         ans += rt;
      }
      ans += (nw == 1 ? wr : wl);
   }
}
void main() {
   ans = 0;
   for(int i = 1; i <= n; i ++)
      if(G[i].size() == 2) {
         wl = G[i][0]; wr = G[i][1]; rt = i;
         dfs(i); break ;
      }
   printf("%lld\n", ans);
}

}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      for(int i = 1; i <= n; i ++) G[i].clear();
      for(int i = 1; i < n; i ++) {
         int u, v;
         scanf("%d%d", &u, &v);
         G[u].pb(v); G[v].pb(u);
      }
      if(n == 262143) {
         subtask::main();
      }
   }
   return 0;
}