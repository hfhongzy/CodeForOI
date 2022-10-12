#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef unsigned short ush;

template<class T>
bool chkmin(T &x, const T &y) {
  return x > y ? (x = y, 1) : 0;
}

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int K = 1005;
const ll INF = 1e17;

int n, m, k, d[N], p[N], pid[N], uu[M], vv[M], ww[M], col[N];
bool vis[M], cov[M];
ll dp[K], la[K];
ush g[N][K];
struct Edge {
  int v, id;
};
vector<Edge> G[N];
vector<int> e[N];
struct node {
  int id, w;
  bool operator < (const node &b) const {
    return w < b.w;
  }
};
vector<vector<node>> s;
void dfs(int u, int fid = 0) {
  for(auto &e : G[u]) if(e.id != fid) {
    if(!d[e.v]) {
      d[e.v] = d[u] + 1;
      p[e.v] = u;
      pid[e.v] = e.id;
      dfs(e.v, e.id);
    } else if(d[e.v] < d[u]) {
      vector<node> cur;
      cur.pb({e.id, ww[e.id]}); cov[e.id] = 1;
      for(int t = u; t != e.v; t = p[t])
        cur.pb({pid[t], ww[pid[t]]}), cov[pid[t]] = 1;
      sort(cur.begin(), cur.end());
      s.pb(cur);
    }
  }
}
void paint(int u, int c) {
  col[u] = c;
  for(int v : e[u]) if(!col[v]) paint(v, c);
}
int main() {
  int test;
  scanf("%d", &test);
  rep(T, 1, test) {
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    rep(i, 1, n) G[i].clear(), d[i] = 0;
    rep(i, 1, m) {
      vis[i] = cov[i] = 0;
      scanf("%d%d%d", &u, &v, &w);
      uu[i] = u; vv[i] = v; ww[i] = w;
      G[u].pb({v, i});
      G[v].pb({u, i});
    }
    s.clear();
    int bag = k;
    rep(i, 1, n) if(!d[i]) { bag --; d[i] = 1; dfs(i); }
    ll res = 0;
    if(bag > 0) {
      vector<node> tree;
      rep(i, 1, m) if(!cov[i]) tree.pb({i, ww[i]});
      sort(tree.begin(), tree.end());
      vector<ll> sum(int(tree.size()) + 1);
      sum[0] = 0;
      rep(i, 0, int(tree.size()) - 1)
        sum[i + 1] = sum[i] + tree[i].w;
      dp[0] = 0;
      rep(i, 1, bag) dp[i] = INF;
      g[0][0] = 0;
      for(int i = 0; i < int(s.size()); i ++) {
        auto &cur = s[i];
        copy(dp, dp + bag + 1, la);
        rep(z, 0, bag) g[i + 1][z] = 0;
        ll sum = 0;
        for(int j = 0; j < min(k, int(cur.size())); j ++) {
          sum += cur[j].w;
          //sum(j+1) size = j
          rep(z, j, bag)
            if(chkmin(dp[z], la[z - j] + sum))
              g[i + 1][z] = ush(j) + 1;
        }
      }
      int a = 0; res = INF;
      rep(i, 0, bag)
        if(bag - i < int(sum.size()) && chkmin(res, dp[i] + sum[bag - i]))
          a = i;
      for(int i = 0; i < bag - a; i ++)
        vis[tree[i].id] = 1;
        int z = a;
        per(i, int(s.size()) - 1, 0) {
          auto &cur = s[i];
          int _z = g[i + 1][z];
          for(int j = 0; j < _z; j ++)
            vis[cur[j].id] = 1;
          if(_z >= 1) z -= _z - 1;
        }
    }
    printf("Case %d: %lld\n", T, res);
    
    rep(i, 1, n) e[i].clear(), col[i] = 0;
    rep(i, 1, m) if(!vis[i]) {
      e[uu[i]].pb(vv[i]);
      e[vv[i]].pb(uu[i]);
    }
    int c = 0;
    rep(i, 1, n) if(!col[i]) paint(i, c = c == k ? 1 : c + 1);
    rep(i, 1, n) printf("%d%c", col[i], " \n"[i == n]);
  }
  return 0;
}