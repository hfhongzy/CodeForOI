#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
const int N = 2010;
int n, m, q;
struct Edge {
   int v, w;
};
vector<Edge> G[N];
bool vis[N], ans, tag;
int cur, k[N], b[N], rt; //k cur + b
void dfs(int u, int fa = 0) {
   vis[u] = 1;
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(e.v == fa) continue ;
      if(vis[e.v]) {
         if(k[e.v] + k[u] == 0) {
            if(b[e.v] + b[u] != e.w) {
               tag = 1; return ;
            }
         } else {
            if((- b[u] - b[e.v]) % (k[e.v] + k[u])) {
               tag = 1; return ;
            }
            int t = (- b[u] - b[e.v]) / (k[e.v] + k[u]);
            if(ans && t != rt) {
               tag = 1; return ;
            }
            rt = t; ans = 1;
         }
         continue ;
      }
      k[e.v] = - k[u]; b[e.v] = e.w - b[u];
      dfs(e.v, u);
      if(tag) return ;
   }
}
int main() {
   int T; scanf("%d", &T);
   while(T --) {
      scanf("%d%d%d", &n, &m, &q);
      rep(i, 1, n + m) {
         G[i].clear(); vis[i] = 0;
      }
      rep(i, 1, q) {
         int u, v, c;
         scanf("%d%d%d", &u, &v, &c);
         v += n;
         G[u].pb((Edge) {v, c});
         G[v].pb((Edge) {u, c});
      }
      tag = ans = 0;
      rep(i, 1, n + m) if(!vis[i]) {
         cur = i; k[i] = 1; b[i] = 0; dfs(i);
         if(tag) break ;
      }
      puts(tag ? "No" : "Yes");
   }
   return 0;
}