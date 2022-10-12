#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 1e5 + 10;
const int M = N * 18;

int n, m, id, sg[N], rt[N], ch[M][2], sz[M], tag[M], d[M];
vector<int> G[N];
bool vis[N];
int newnode(int dep) {
  ++ id; ch[id][0] = ch[id][1] = sz[id] = tag[id] = 0; d[id] = dep;
  return id;
}
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
  if(!rt) rt = newnode(16);
  int u = rt;
  vector<int> s; s.pb(u);
  per(i, 15, 0) {
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
  int ans = 0;
  per(i, 15, 0) {
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
  vis[u] = 1;
  int z = 0;
  for(int v : G[u]) if(v != fa) {
    dfs(v, u); z ^= sg[v];
  }
  for(int v : G[u]) if(v != fa) {
    tag[rt[v]] ^= sg[v] ^ z;
    rt[u] = comb(rt[v], rt[u]);
  }
  insert(rt[u], z);
  sg[u] = query(rt[u]);
}
int main() {
  int test; scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) {
      vis[i] = rt[i] = 0; vector<int>().swap(G[i]);
    }
    int u, v;
    rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
    }
    int ans = 0;
    rep(i, 1, n) if(!vis[i]) {
      id = 0; dfs(i); ans ^= sg[i];
    }
    puts(ans ? "Alice" : "Bob");
  }
  return 0;
}