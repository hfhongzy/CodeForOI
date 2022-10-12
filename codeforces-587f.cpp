#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct queries {
  int r, k, id, coef;
  bool operator < (const queries &b) const {
    return r < b.r;
  }
};
vector<queries> v1[N], v2; 
int n, q, len[N], pos[N];
int id = 1, ch[N][26], fa[N], fail[N];
vector<int> G[N];
ll ans[N];
int insert(char *s) {
  int u = 1;
  for(; *s; s ++) {
    int &v = ch[u][*s - 'a'];
    if(!v) {
      v = ++ id; fa[v] = u;
    }
    u = v;
  }
  return u;
}
void build() {
  queue<int> q; int v; fail[1] = 1;
  rep(i, 0, 25) if(v = ch[1][i], v) {
    q.push(v); fail[v] = 1;
  } else ch[1][i] = 1;
  while(q.size()) {
    int u = q.front(); q.pop();
    rep(i, 0, 25) if(v = ch[u][i], v) {
      q.push(v); fail[v] = ch[fail[u]][i];
    } else ch[u][i] = ch[fail[u]][i];
  }
  rep(i, 2, id) G[fail[i]].pb(i);
}
int dl[N], dr[N], idx, w[N];
void dfs0(int u) {
  dl[u] = ++ idx;
  for(int v : G[u]) dfs0(v);
  dr[u] = idx;
}
void dfs(int u) {
  for(int v : G[u]) {
    dfs(v); w[u] += w[v];
  }
}
int bit[N];
void add(int u, int v) {
  for(; u <= id; u += u & (-u))
    bit[u] += v;
}
int qry(int u) {
  int z = 0;
  for(; u; u &= u - 1)
    z += bit[u];
  return z;
}
int main() {
  scanf("%d%d", &n, &q);
  int m = 0;
  rep(i, 1, n) {
    static char s[N];
    scanf("%s", s);
    pos[i] = insert(s);
    len[i] = strlen(s);
    m += len[i];
  }
  build(); dfs0(1);
  const int S = max(0, (int)(m / sqrt(q * log2(m))));
  int l, r, k;
  rep(i, 1, q) {
    scanf("%d%d%d", &l, &r, &k);
    if(len[k] > S) {
      v1[k].pb({r, k, i, 1});
      if(l > 1) v1[k].pb({l - 1, k, i, -1});
    } else {
      v2.pb({r, k, i, 1});
      if(l > 1) v2.pb({l - 1, k, i, -1});
    }
  }
  sort(v2.begin(), v2.end());
  unsigned p = 0;
  rep(i, 1, n) {
    add(dl[pos[i]], 1); add(dr[pos[i]] + 1, -1);
    if(len[i] > S) {
      sort(v1[i].begin(), v1[i].end());
      fill(w, w + id + 1, 0);
      for(int v = pos[i]; v > 1; v = fa[v]) w[v] = 1;
      dfs(1);
      int r = 0;
      ll cur = 0;
      for(auto x : v1[i]) {
        while(r < x.r) {
          cur += w[pos[++ r]];
        }
        ans[x.id] += x.coef * cur;
      }
    }
    while(p < v2.size() && v2[p].r <= i) {
      ll cur = 0;
      for(int v = pos[v2[p].k]; v > 1; v = fa[v])
        cur += qry(dl[v]);
      ans[v2[p].id] += v2[p].coef * cur;
      p ++;
    }
  }
  rep(i, 1, q) printf("%lld\n", ans[i]);
  return 0;
} 