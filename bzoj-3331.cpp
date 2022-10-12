#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <random>
#include <queue>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back

typedef double db;
typedef long long ll;
typedef long double ldb;
typedef unsigned uint;
typedef unsigned long long ull;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

struct Tree {

int n, n0, d[N], cnt[N], sz[N], son[N], fa[N], top[N];
vector<int> G[N]; 
void link(int u, int v) { G[u].pb(v); G[v].pb(u); }
void dfs(int u, int p = 0) {
   sz[u] = 1; fa[u] = p; d[u] = d[p] + 1;
   for(int v : G[u]) if(v ^ p) {
      dfs(v, u); sz[u] += sz[v];
      if(sz[v] > sz[son[u]]) son[u] = v;
   }
}
void dfs2(int u, int t) {
   top[u] = t;
   if(!son[u]) return ;
   dfs2(son[u], t);
   for(int v : G[u]) {
      if(v != fa[u] && v != son[u]) {
         dfs2(v, v);
      }
   }
}
int query(int u, int v) {
   int ans = 1e9 + 10;
   while(top[u] ^ top[v]) {
      if(d[top[u]] < d[top[v]]) swap(u, v);
      u = fa[top[u]];
   }
   if(d[u] > d[v]) swap(u, v);
   return u;
}
void q(int u, int v) {
   int x = query(u, v);
   cnt[u] ++; cnt[v] ++; cnt[x] --; cnt[fa[x]] --;
}
int cov[N];
int solve(int u) {
   int ans = cnt[u];
   for(int v : G[u]) if(v ^ fa[u]) {
      ans += solve(v);
   }
   return cov[u] = ans;
}

} tr;

int n, m, q, id, dfn[N], low[N], idx, st[N], top;
vector<int> G[N];
void tarjan(int u) {
   low[u] = dfn[u] = ++ idx; st[++ top] = u; //printf("!%d\n", u);
   for(int v : G[u]) {
      if(!dfn[v]) {
         tarjan(v); low[u] = min(low[u], low[v]);
         if(low[v] == dfn[u]) {
            id ++;
            while(st[top] != v) {
               tr.link(id, st[top --]);
            }
            tr.link(id, st[top --]);
            tr.link(id, u);
         }
      } else {
         low[u] = min(low[u], dfn[v]);
      }
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &q);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   id = n; tarjan(1); tr.n = id; tr.n0 = n;
   tr.dfs(1); tr.dfs2(1, 1);
   char op[20];
   rep(i, 1, q) {
      scanf("%d%d", &u, &v); tr.q(u, v);
   }
   tr.solve(1);
   rep(i, 1, n) printf("%d\n", tr.cov[i]);
   return 0;
}