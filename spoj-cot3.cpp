#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 1e5 + 10;
const int M = N * 20;

int n, id, sg[N], rt[N], ch[M][2], sz[M], tag[M], d[M];
vector<int> G[N];
bool vis[N];
int newnode(int dep) { ++ id; d[id] = dep; return id; }
void down(int u) {
  if(tag[u]) {
    int &ls = ch[u][0], &rs = ch[u][1];
    if(tag[u] >> (d[u] - 1) & 1) {
      swap(ls, rs);
      tag[u] ^= 1 << (d[u] - 1);
    }
    tag[ls] ^= tag[u];
    tag[rs] ^= tag[u];
    tag[u] = 0;
  }
}
void insert(int &rt, int x) {
  if(!rt) rt = newnode(17);
  int u = rt;
  vector<int> s; s.pb(u);
  per(i, 16, 0) {
    down(u);
    int &v = ch[u][x >> i & 1];
    if(!v) v = newnode(i);
    u = v; s.pb(u);
  }
  if(sz[* --s.end()]) return ;
  for(int x : s) sz[x] ++;
}
int comb(int u, int v) {
  if(!u || !v) return u | v;
  down(u); down(v);
  ch[u][0] = comb(ch[u][0], ch[v][0]);
  ch[u][1] = comb(ch[u][1], ch[v][1]);
  sz[u] = d[u] ? sz[ch[u][0]] + sz[ch[u][1]] : 1;
  return u;
}
int query(int u) {
  if(!u) return 0;
  int ans = 0;
  per(i, 16, 0) {
    down(u);
    if(sz[ch[u][0]] == (1 << i)) {
      u = ch[u][1];
      ans ^= 1 << i;
    } else {
      u = ch[u][0];
    }
    if(!u) break ;
  }
  return ans;
}
void dfs(int u, int fa = 0) {
  int z = 0;
  for(int v : G[u]) if(v != fa) {
    dfs(v, u); z ^= sg[v];
  }
  for(int v : G[u]) if(v != fa) {
    tag[rt[v]] ^= sg[v] ^ z;
    rt[u] = comb(rt[v], rt[u]);
  }
  if(!vis[u]) insert(rt[u], z);
  sg[u] = query(rt[u]);
}
bool ok[N];
void dfs2(int u, int val = 0, int fa = 0) {
  for(int v : G[u]) if(v != fa) val ^= sg[v];
  if(!vis[u] && !val) {
    ok[u] = 1;
  }
  for(int v : G[u]) if(v != fa) {
    dfs2(v, val ^ sg[v], u);
  }
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    int x; scanf("%d", &x); vis[i] = x;
  }
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  if(!sg[1]) return puts("-1"), 0;
  dfs2(1);
  rep(i, 1, n) if(ok[i]) printf("%d ", i);
  puts("");
  return 0;
}