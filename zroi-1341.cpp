#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)

#define fs first
#define sc second
#define pb push_back
#define lw lower_bound

using namespace std;
using pii = pair<int, int>;

const int N = 2e5 + 10;
const int M = 6e5 + 10;

int n, m, ans[M];
struct Edge { int v, id; };
vector<Edge> G[N];

vector<int> vec[N], qs[N], up[N], dw[N];
int sz[N], w[N], size, rt;
bool vis[N];
void findrt(int u, int fa = 0) {
  sz[u] = 1; w[u] = 0;
  for(auto &e : G[u]) if(e.v != fa && !vis[e.v]) {
    findrt(e.v, u); sz[u] += sz[e.v]; w[u] = max(w[u], sz[e.v]);
  }
  w[u] = max(w[u], size - sz[u]);
  if(!rt || w[u] < w[rt]) rt = u;
}
namespace ns{

int c[M];
vector<int> vp;
void add(int x, int y) {
  vp.pb(x);
  for(; x <= m; x += x & (-x)) c[x] += y;
}
int qry(int x) {
  int ans = 0;
  for(; x >= 1; x &= x - 1) ans += c[x];
  return ans;
}
void clr() {
  if(int(vp.size()) * 16 > m) {
    fill(c, c + m + 1, 0);
  } else {
    for(int x : vp)
      for(; x <= m; x += x & (-x))
        c[x] = 0;
  }
  vp.clear();
}

}
int pid[N], p[N];
struct node {
  int t1, c, u;
  bool operator < (const node &b) const {
    return t1 < b.t1 || (t1 == b.t1 && c < b.c);
  }
};
vector<pii> ask;
vector<node> to;
void dfs(int u, int fa = 0) {
  p[u] = fa; up[u].clear(); dw[u].clear();
  vector<int> &v0 = vec[pid[u]];
  if(u != rt) {
    if(fa == rt) {
      rep(i, 0, int(v0.size()) - 1) {
        int &x = v0[i];
        up[u].pb(x), dw[u].pb(x), to.pb({x, i, u});
      }
    } else {
      auto &pre = vec[pid[fa]];
      rep(i, 0, int(v0.size()) - 1) {
        int &x = v0[i];
        auto it = lw(pre.begin(), pre.end(), x);
        up[u].pb(it == pre.end() ? m + 1 : up[fa][int(it - pre.begin())]);
        if(it == pre.begin()) dw[u].pb(-1), to.pb({-1, i, u});
        else {
          int t = dw[fa][int(it - pre.begin() - 1)];
          dw[u].pb(t);
          to.pb({t, i, u});
        }
      }
    }
    if(v0.size())
      ns::add(*v0.begin(), 1);
    if(up[u].size()) {
      for(int &x : qs[u]) if(up[u][0] <= x) ask.pb({up[u][0], x});
    }
  } else {
    ns::add(1, 1);
    for(int &x : qs[u]) ask.pb({1, x});
  }
  for(auto &e : G[u]) if(e.v != fa && !vis[e.v]) {
    pid[e.v] = e.id; dfs(e.v, u);
  }
}
void calc(int ty) {
  sort(ask.begin(), ask.end());
  sort(to.begin(), to.end());
  int z = 0;
  for(auto q : ask) {
    while(z < int(to.size()) && to[z].t1 < q.fs) {
      int u = to[z].u;
      ns::add(vec[pid[u]][to[z].c], -1);
      if(to[z].c + 1 < int(up[u].size()))
        ns::add(vec[pid[u]][to[z].c + 1], 1);
      z ++;
    }
    ans[q.sc] += ty * ns::qry(q.sc);
  }
  ns::clr();
}
void solve(int u) {
  vis[u] = 1; rt = u;
  ask.clear(); to.clear(); dfs(u); calc(1);
  for(auto &e : G[u]) if(!vis[e.v]) {
    ask.clear(); to.clear(); dfs(e.v, u); calc(-1);
  }
  for(auto &e : G[u]) if(!vis[e.v]) {
    rt = 0; size = sz[e.v]; findrt(e.v); solve(rt);
  }
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v, z, op;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb({v, i});
    G[v].pb({u, i});
  }
  rep(i, 1, m) {
    scanf("%d%d", &op, &z);
    if(op == 1) qs[z].pb(i);
    if(op == 2) ans[i] = -1, vec[z].pb(i);
  }
  size = n; rt = 0; findrt(1); solve(rt);
  rep(i, 1, m) if(~ans[i])
    printf("%d\n", ans[i]);
  return 0;
}