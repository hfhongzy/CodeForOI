#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
#define pb push_back
using namespace std;
const int N = 5e4 + 10, INF = 2e9 + 20;
struct Edge { int v, w; };
vector<Edge> G[N], T[N];
vector<int> V[N];
int n, m, rt, q, p[N], pw[N];
bool cut[N], tag[N], ok;
struct Node {
   int u, d;
   bool operator < (const Node &b) const {
      return d > b.d;
   }
};
int f[N][16], dis[N], d[N], dfn[N], idx;
void Dijkstra(int *d) {
   fill(d + 1, d + n + 1, INF);
   priority_queue<Node> pq; pq.push((Node) {rt, d[rt] = 0});
   while(pq.size()) {
      int u = pq.top().u, du = pq.top().d; pq.pop();
      if(d[u] < du) continue ;
      for(int i = 0; i < (int) G[u].size(); i ++) {
         Edge &e = G[u][i];
         if(d[e.v] > d[u] + e.w) {
            p[e.v] = u; pw[e.v] = e.w;
            pq.push((Node) {e.v, d[e.v] = d[u] + e.w});
         } else if(d[e.v] == d[u] + e.w) {
            if(!p[e.v] || p[e.v] > u) {
               p[e.v] = u; pw[e.v] = e.w;
            }
         }
      }
   }
   rep(i, 1, n) if(i != rt) {
      T[p[i]].pb((Edge) {i, pw[i]});
   }
}
void dfs0(int u) {
   f[u][0] = p[u]; d[u] = d[p[u]] + 1; dfn[u] = ++ idx;
   rep(i, 1, 15) f[u][i] = f[f[u][i - 1]][i - 1];
   for(int i = 0; i < (int) T[u].size(); i ++) {
      Edge &e = T[u][i]; dfs0(e.v);
   }
}
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   per(i, 15, 0) if(c >> i & 1) u = f[u][i];
   if(u == v) return u;
   per(i, 15, 0) if(f[u][i] != f[v][i]) {
      u = f[u][i]; v = f[v][i];
   }
   return f[u][0];
}
int dp[N];
void dfs(int u) {
   dp[u] = 0;
   if(cut[u]) ok = 1;
   for(int i = 0; i < (int) V[u].size(); i ++) {
      int v = V[u][i], w = dis[v] - dis[u];
      dfs(v); dp[u] += cut[v] ? w : min(w, dp[v]);
   }
}
int seq[N], num, st[N], top;
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
int solve() {
   rep(i, 1, n) V[i].clear();
   st[top = 1] = rt;
   sort(seq + 1, seq + num + 1, cmp);
   rep(i, 1, num) {
      int u = seq[i];
      if(top > 1) {
         int x = lca(st[top], u);
         if(x != st[top]) {
            while(d[st[top - 1]] > d[x]) {
               V[st[top - 1]].pb(st[top]); top --;
            }
            if(st[top - 1] == x) {
               V[st[top - 1]].pb(st[top]); top --;
            } else {
               V[x].pb(st[top]); st[top] = x;
            }
         }
      }
      st[++ top] = u;
   }
   rep(i, 1, top - 1) V[st[i]].pb(st[i + 1]);
   ok = 0; dfs(rt);
   return ok ? dp[rt] : -1;
}
signed main() {
   scanf("%d%d%d%d", &n, &m, &rt, &q);
   rep(i, 1, m) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].pb((Edge) {v, w});
      G[v].pb((Edge) {u, w});
   }
   Dijkstra(dis); dfs0(rt);
   rep(i, 1, q) {
      int op, u;
      scanf("%d%d", &op, &num);
      if(op == 0) {
         rep(j, 1, num) { scanf("%d", &u); cut[u] ^= 1; }
      }
      if(op == 1) {
         rep(j, 1, num) scanf("%d", seq + j);
         printf("%d\n", solve());
      }
   }
   return 0;
}