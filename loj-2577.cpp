#include <algorithm>
#include <cstdio>
#include <vector>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, q, val[N];
int sz[N], son[N], d[N], dfn[N], pos[N], fa[N], top[N], idx;
vector<int> G[N];
void dfs(int u, int fa = 0) {
   sz[u] = 1; ::fa[u] = fa; d[u] = d[fa] + 1;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v != fa) {
         dfs(v, u); sz[u] += sz[v];
         if(sz[v] > sz[son[u]])
            son[u] = v;
      }
   }
}
void dfs2(int u, int t) {
   top[u] = t; dfn[u] = ++ idx; pos[idx] = u;
   if(!son[u]) return ;
   dfs2(son[u], t);
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(!dfn[v]) dfs2(v, v);
   }
}
int ch[N * 40][2], siz[N * 40], id, rt[N];
void ins(int &u, int val, int d) {
   u = ++ id; siz[u] = 1;
   if(d == 0) return ;
   ins(ch[u][val >> (d - 1) & 1], val, d - 1);
}
void update(int p, int &u, int val, int d) {
   u = ++ id; siz[u] = siz[p] + 1;
   if(d == 0) return ;
   if(val >> (d - 1) & 1) {
      ch[u][0] = ch[p][0];
      update(ch[p][1], ch[u][1], val, d - 1);
   } else {
      ch[u][1] = ch[p][1];
      update(ch[p][0], ch[u][0], val, d - 1);
   }
}
void build() {
   ins(rt[0], 31, 0);
   rep(i, 1, n) {
      update(rt[i - 1], rt[i], val[pos[i]], 31);
   }
}
int query(int l, int r, int val) {
   int u = rt[l - 1], v = rt[r], ans = 0;
   per(i, 30, 0) {
      int d = val >> i & 1;
      if(siz[ch[v][d ^ 1]] - siz[ch[u][d ^ 1]] >= 1) {
         ans ^= 1 << i; d ^= 1;
      }
      u = ch[u][d]; v = ch[v][d];
   }
   return ans;
}
int tqry(int u, int v, int w) {
   int ans = 0;
   while(top[u] ^ top[v]) {
      if(d[top[u]] < d[top[v]]) swap(u, v);
      ans = max(ans, query(dfn[top[u]], dfn[u], w));
      u = fa[top[u]];
   }
   if(dfn[u] > dfn[v]) swap(u, v);
   ans = max(ans, query(dfn[u], dfn[v], w));
   return ans;
}
int main() {
   scanf("%d%d", &n, &q);
   rep(i, 1, n) scanf("%d", val + i);
   rep(i, 1, n - 1) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[v].push_back(u);
      G[u].push_back(v);
   }
   dfs(1); dfs2(1, 1); build();
   rep(i, 1, q) {
      int op, x, y, z;
      scanf("%d%d%d", &op, &x, &y);
      if(op == 1) {
         printf("%d\n", query(dfn[x], dfn[x] + sz[x] - 1, y));
      }
      if(op == 2) {
         scanf("%d", &z);
         printf("%d\n", tqry(x, y, z));
      }
   }
   return 0;
}