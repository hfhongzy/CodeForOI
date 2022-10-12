#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
struct edge { int u, v, w, id; } s[N], e[N];
int n, m, q, S, ans[N];
struct node { int op, u, w, id; } a[N], tmp[N];
int sz, f[N], cnt[N], fir[N], st[N][2], top;
int find(int u) { while(u != f[u]) u = f[u]; return u; }
void unite(int u, int v) {
  u = find(u); v = find(v);
  if(u == v) return ;
  if(cnt[u] < cnt[v]) swap(u, v);
  cnt[u] += cnt[v]; f[v] = u;
  top ++; st[top][0] = u; st[top][1] = v;
}
void cancel() {
  int u = st[top][0], v = st[top][1]; top --;
  cnt[u] -= cnt[v]; f[v] = v;
}
void solve(int t) {
  fill(fir + 1, fir + m + 1, 0);
  rep(i, 1, sz) if(a[i].op == 1 && !fir[a[i].u]) fir[a[i].u] = a[i].id;
  copy(a + 1, a + sz + 1, tmp + 1);
  sort(a + 1, a + sz + 1, [&](node x, node y) {
    return x.w != y.w ? x.w > y.w : x.op < y.op;
  });
  copy(s + 1, s + m + 1, e + 1);
  sort(e + 1, e + m + 1, [&](edge x, edge y) {
    return x.w > y.w;
  });
  rep(i, 1, n) { f[i] = i; cnt[i] = 1; }
  top = 0;
  int ep = 0;
  rep(i, 1, sz) {
    if(a[i].op == 1)
      continue ;
    while(ep < m && e[ep + 1].w >= a[i].w) {
      ep ++;
      if(!fir[e[ep].id])
        unite(e[ep].u, e[ep].v);
    }
    int cur = top;
    static int vis[N], tim;
    ++ tim;
    per(j, sz, 1) {
      if(tmp[j].op != 1) continue ;
      if(tmp[j].id > a[i].id) {
        if(a[i].id < fir[tmp[j].u] && s[tmp[j].u].w >= a[i].w) {
          unite(s[tmp[j].u].u, s[tmp[j].u].v);
        }
        continue ;
      }
      if(vis[tmp[j].u] == tim) continue ;
      vis[tmp[j].u] = tim;
      if(tmp[j].w >= a[i].w) {
        unite(s[tmp[j].u].u, s[tmp[j].u].v);
      }
    }
    ans[a[i].id] = cnt[find(a[i].u)];
    while(top > cur) cancel();
  }
  rep(i, 1, sz) if(tmp[i].op == 1) s[tmp[i].u].w = tmp[i].w;
  sz = 0;
}
int main() {
  scanf("%d%d", &n, &m);
  int op, u, v, w;
  rep(i, 1, m) {
    scanf("%d%d%d", &u, &v, &w);
    s[i] = {u, v, w, i};
  }
  scanf("%d", &q);
  S = 1024;
  rep(i, 1, q) {
    scanf("%d%d%d", &op, &u, &w);
    a[++ sz] = {op, u, w, i};
    if(op == 1) ans[i] = -1;
    if(i == q || sz == S) {
      solve(a[1].id);
    }
  }
  rep(i, 1, q) if(~ans[i]) printf("%d\n", ans[i]);
  return 0;
}