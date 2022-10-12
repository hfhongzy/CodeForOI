#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
const int INF = 2e9;
int n, m, f[N], g[N], a[N], b[N], r[N], p[N];
int ord[N];
struct Edge {
  int v, r, p;
};
vector<Edge> G[N];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, m) scanf("%d%d%d%d", a + i, b + i, r + i, p + i), r[i] += p[i];
  rep(i, 1, m) G[a[i]].push_back((Edge){b[i], r[i], p[i]});
  rep(i, 1, m) ord[i] = i;
  // sort(ord + 1, ord + m + 1, [&](int x, int y) { return r[x] + p[x] < r[y] + p[y]; });
  rep(i, 1, n) f[i] = 0;
  int lim = n + 2;
  // queue<int> q;
  // rep(i, 1, n) q.push(i);
  rep(T, 1, lim) {
    fill(g, g + n + 1, INF);
    bool mark = 0;
    rep(t, 1, m) {
      int i = ord[t];
      if(f[b[i]] < INF) {
        g[a[i]] = min(g[a[i]], max(r[i], f[b[i]]) - p[i]);
        if(r[i] + p[i] > f[b[i]]) mark = 1;
      }
    }
    bool tag = 0;
    rep(i, 1, n) if(f[i] != g[i]) tag = 1, i = n;
    copy(g, g + n + 1, f);
    if(!tag) break ;
    if(!mark) break ;
  }
  // rep(i, 1, m) G[u[i]]
  rep(i, 1, n) printf("%d%c", f[i] >= INF ? -1 : f[i], " \n"[i == n]);
  return 0;
}