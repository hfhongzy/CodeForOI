#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int id, ch[N][26], lnk[N], len[N];
void init() { id = 0; fill(ch[0], ch[0] + 26, -1); lnk[0] = -1; }
int extend(int c, int la) {
  int u = ++ id, p = la;
  len[u] = len[la] + 1; fill(ch[u], ch[u] + 26, -1);
  for(; ~p && !~ch[p][c]; p = lnk[p]) ch[p][c] = u;
  if(!~p) lnk[u] = 0;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id;
      len[q0] = len[p] + 1; copy(ch[q], ch[q] + 26, ch[q0]);
      lnk[q0] = lnk[q]; lnk[q] = lnk[u] = q0;
      for(; ~p && ch[p][c] == q; p = lnk[p]) ch[p][c] = q0;
    }
  }
  return u;
}
struct edge { int v, w; };
vector<edge> G[N];
int op[N], siz[N], posl[N], posr[N], top, last[N];
bool vis[N];
char s[N * 4];
ll ans;
void bfs() {
  queue<int> q; q.push(1); last[1] = 0; vis[1] = 1; init();
  while(q.size()) {
    int u = q.front(); q.pop();
    for(edge &e : G[u]) if(!vis[e.v]) {
      last[e.v] = extend(e.w, last[u]);
      vis[e.v] = 1;
      q.push(e.v);
    }
  }
}
vector<int> adj[N];
int dl[N], dr[N], idx;
void dfs(int u) {
  dl[u] = ++ idx;
  for(int v : adj[u]) {
    dfs(v);
  }
  dr[u] = idx;
}
struct fenwick {
  int a[N];
  void add(int u) {
    for(; u <= idx; u += u & (-u))
      ++ a[u];
  }
  int qry(int u) {
    int z = 0;
    for(; u; u &= u - 1)
      z += a[u];
    return z;
  }
} bit;
void activate(int u) {
  static bool vis[N];
  if(u < 1 || vis[u]) return ;
  vis[u] = 1; ans += len[u] - len[lnk[u]];
  activate(lnk[u]);
}
int main() {
  char c[8]; int n0, m, sz, u, v;
  scanf("%*d%d", &n0);
  n0 = max(n0, 1);
  rep(i, 1, n0 - 1) {
    scanf("%d%d%s", &u, &v, c);
    G[u].pb({v, *c - 'a'}); G[v].pb({u, *c - 'a'});
  }
  siz[0] = n0;
  scanf("%d", &m);
  rep(i, 1, m) {
    scanf("%d", op + i);
    siz[i] = siz[i - 1];
    if(op[i] == 2) {
      scanf("%d%d", &u, &sz);
      siz[i] += sz - 1;
      rep(j, 1, sz - 1) {
        scanf("%d%d%s", &u, &v, c);
        G[u].pb({v, *c - 'a'}); G[v].pb({u, *c - 'a'});
      }
    }
    if(op[i] == 3) {
      scanf("%s", s + top);
      posl[i] = top;
      top += strlen(s + top);
      posr[i] = top;
    }
  }
  bfs();
  rep(i, 1, id) adj[lnk[i]].pb(i);
  // return 0;
  dfs(0);
  int cur = 0;
  rep(i, 1, m) {
    while(cur < siz[i]) {
      ++ cur;
      u = last[cur];
      if(u) {
        bit.add(dl[u]);
        activate(u);
      }
    }
    if(op[i] == 1) {
      printf("%lld\n", ans);
    }
    if(op[i] == 3) {
      u = 0;
      for(int j = posl[i]; j < posr[i]; j ++) {
        u = ch[u][s[j] - 'a'];
        if(!~u) break ;
      }
      printf("%d\n", ~u ? bit.qry(dr[u]) - bit.qry(dl[u] - 1) : 0);
    }
  }
  return 0;
} 